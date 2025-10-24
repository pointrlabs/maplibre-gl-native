#include <exception>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

#include <zlib.h>

#include <QGuiApplication>
#include <QMapLibreGL/Map>
#include <QMapLibreGL/Settings>
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QBuffer>
#include <QByteArray>
#include <QIODevice>
#include <QImage>
#include <QSize>
#include <QString>
#include <QEventLoop>
#include <QTimer>
#include <QObject>

#include "maprenderer.h"
#include "spng.h"

namespace PTR {

MapRenderer::MapRenderer(const std::string &style,
                         const std::optional<uint32_t> &width,
                         const std::optional<uint32_t> &height,
                         const std::optional<float> &ratio,
                         const std::optional<double> &longitude,
                         const std::optional<double> &latitude,
                         const std::optional<double> &zoom,
                         const std::optional<std::string> &token,
                         const std::optional<std::string> &provider) {
    // Initialize Qt application if not already done
    if (!QGuiApplication::instance()) {
        static int argc = 1;
        static char* argv[] = {const_cast<char*>("map-renderer"), nullptr};
        _app = std::make_unique<QGuiApplication>(argc, argv);
    }
    
    // Note: We can't use mbgl::util::RunLoop directly with qmaplibregl
    // The Qt backend manages its own run loop
    
    // Note: We can't use mbgl::Log directly with qmaplibregl
    // Logging is handled by Qt's logging system
    
    // Validate parameters
    if (width.has_value()) {
        validateDimension(width.value(), "width");
    }
    if (height.has_value()) {
        validateDimension(height.value(), "height");
    }
    if (ratio.has_value()) {
        validatePixelRatio(ratio.value());
    }
    if (zoom.has_value()) {
        validateZoom(zoom.value());
    }
    
    // Store dimensions and pixel ratio
    _width = width.value_or(1024);
    _height = height.value_or(1024);
    _pixelRatio = ratio.value_or(1.0f);
    
    // Create OpenGL context for headless rendering
    _context = std::make_unique<QOpenGLContext>();
    _context->create();
    
    _surface = std::make_unique<QOffscreenSurface>();
    _surface->create();
    
    // Activate context
    _context->makeCurrent(_surface.get());
    
    // Create Qt settings
    QMapLibreGL::Settings settings;
    if (token.has_value()) {
        settings.setApiKey(QString::fromStdString(token.value()));
    }
    
    // Set provider-specific settings
    if (provider.has_value() && !provider.value().empty()) {
        if (provider.value().find("mapbox") != -1) {
            settings.setApiBaseUrl("https://api.mapbox.com");
        } else if (provider.value().find("maptiler") != -1) {
            settings.setApiBaseUrl("https://api.maptiler.com");
        } else if (provider.value().find("maplibre") != -1) {
            settings.setApiBaseUrl("https://api.maplibre.org");
        } else {
            throw std::invalid_argument("invalid provider: " + provider.value());
        }
    }
    
    // Create QMapLibreGL::Map
    _map = std::make_unique<QMapLibreGL::Map>(
        nullptr, // No renderer backend - will use headless
        settings,
        QSize(_width, _height),
        _pixelRatio
    );
    
    // Initialize renderer for offscreen rendering
    _map->createRenderer();
    
    // Load style
    if (style.find("{") == 0) {
        // Assume content is json
        _map->setStyleJson(QString::fromStdString(style));
    } else if (style.find("://") != -1) {
        // Otherwise must be URL-like reference
        _map->setStyleUrl(QString::fromStdString(style));
    } else {
        throw std::invalid_argument("style is not valid");
    }
    
    // Set initial camera position  
    _map->setCoordinate(QMapLibreGL::Coordinate(latitude.value_or(0), longitude.value_or(0)));
    _map->setZoom(zoom.value_or(0));
    _map->setBearing(0);
    _map->setPitch(0);
    
    // Wait for map to finish loading
    // Qt's event loop handles async operations (network requests, tile loading)
    QEventLoop eventLoop;

    // Quit event loop when map finishes loading (success or failure)
    QObject::connect(_map.get(), &QMapLibreGL::Map::mapChanged, [&eventLoop](QMapLibreGL::Map::MapChange change) {
        if (change == QMapLibreGL::Map::MapChangeDidFinishLoadingMap ||
            change == QMapLibreGL::Map::MapChangeDidFailLoadingMap) {
            eventLoop.quit();
        }
    });

    // Render during loading to process tiles
    // QMapLibreGL requires active rendering to process downloaded tile data
    QObject::connect(_map.get(), &QMapLibreGL::Map::needsRendering, [this]() {
        _context->makeCurrent(_surface.get());

        QSize renderSize(_width * _pixelRatio, _height * _pixelRatio);
        QOpenGLFramebufferObject fbo(renderSize, QOpenGLFramebufferObject::CombinedDepthStencil);

        if (fbo.isValid()) {
            fbo.bind();
            _context->functions()->glViewport(0, 0, renderSize.width(), renderSize.height());
            _map->setFramebufferObject(fbo.handle(), renderSize);
            _map->render();
            fbo.release();
        }
    });

    // Run event loop until map loads
    eventLoop.exec();
}

MapRenderer::~MapRenderer() {
    if (_map) {
        release();
    }
}

void MapRenderer::addImage(const std::string &name,
                           const std::string &image,
                           uint32_t width,
                           uint32_t height,
                           float ratio,
                           bool make_sdf) {
    if (width > 1024 || height > 1024) {
        throw std::invalid_argument("width and height must be less than 1024");
    }

    if (image.length() != width * height * 4) {
        throw std::invalid_argument("length of image bytes must be width * height * 4");
    }

    // Create QImage from raw data
    QImage qimage(reinterpret_cast<const uchar*>(image.c_str()), width, height, QImage::Format_RGBA8888);
    
    // Add image to map (QMapLibreGL::Map::addImage only takes name and image)
    _map->addImage(QString::fromStdString(name), qimage);
}

const double MapRenderer::getBearing() {
    return std::abs(_map->bearing());
}

const std::pair<double, double> MapRenderer::getCenter() {
    QMapLibreGL::Coordinate center = _map->coordinate();
    return std::pair<double, double>(center.second, center.first); // longitude, latitude
}

const double MapRenderer::getPitch() {
    return _map->pitch();
}

const std::pair<uint32_t, uint32_t> MapRenderer::getSize() {
    return std::pair<uint32_t, uint32_t>(_width, _height);
}

const double MapRenderer::getZoom() {
    return _map->zoom();
}

const std::pair<mbgl::LatLng, mbgl::LatLng> MapRenderer::getBoundingBox() {
    auto size = getSize();
    auto southWest = _map->coordinateForPixel({0, static_cast<double>(size.second)});
    auto northEast = _map->coordinateForPixel({static_cast<double>(size.first), 0});
    return {mbgl::LatLng{southWest.first, southWest.second}, mbgl::LatLng{northEast.first, northEast.second}};
}

void MapRenderer::setBearing(const double &bearing) {
    validateBearing(bearing);
    _map->setBearing(bearing);
}

void MapRenderer::setCenter(const double &longitude, const double &latitude) {
    _map->setCoordinate(QMapLibreGL::Coordinate(latitude, longitude));
}

void MapRenderer::setBounds(const double &west,
                            const double &south,
                            const double &east,
                            const double &north,
                            const double &padding) {
    // QMapLibreGL doesn't have setBounds, use coordinateZoomForBounds instead
    QMapLibreGL::Coordinate sw(south, west);
    QMapLibreGL::Coordinate ne(north, east);
    auto coordinateZoom = _map->coordinateZoomForBounds(sw, ne);
    _map->setCoordinateZoom(coordinateZoom.first, coordinateZoom.second);
}

void MapRenderer::setPitch(const double &pitch) {
    validatePitch(pitch);
    _map->setPitch(pitch);
}

void MapRenderer::setSize(const uint32_t &width, const uint32_t &height) {
    validateDimension(width, "width");
    validateDimension(height, "height");
    _width = width;
    _height = height;
    
    // QOffscreenSurface doesn't have setSize - it auto-sizes
    
    // Resize map
    _map->resize(QSize(width, height));
}

void MapRenderer::setZoom(const double &zoom) {
    validateZoom(zoom);
    _map->setZoom(zoom);
}

QImage MapRenderer::render() {
    // Ensure context is current
    if (!_context->makeCurrent(_surface.get())) {
        throw std::runtime_error("Failed to make OpenGL context current");
    }

    // Process any pending Qt events
    if (_app) {
        _app->processEvents();
    }

    // Create framebuffer for offscreen rendering
    QSize renderSize(_width * _pixelRatio, _height * _pixelRatio);
    QOpenGLFramebufferObject fbo(renderSize, QOpenGLFramebufferObject::CombinedDepthStencil);

    if (!fbo.isValid()) {
        throw std::runtime_error("Failed to create OpenGL framebuffer object");
    }

    // Set up rendering
    fbo.bind();
    _context->functions()->glViewport(0, 0, renderSize.width(), renderSize.height());

    // Configure map for framebuffer rendering
    _map->resize(QSize(_width, _height));
    _map->setFramebufferObject(fbo.handle(), renderSize);

    // Render the map
    _map->render();

    // Extract rendered image
    QImage image = fbo.toImage();
    fbo.release();

    // Convert to RGBA format
    return image.convertToFormat(QImage::Format_RGBA8888);
}

const std::string MapRenderer::renderPNG() {
    QImage rgbaImage = render();
    
    // Use existing spng encoding logic
    struct spng_ihdr ihdr = {0};
    ihdr.width = rgbaImage.width();
    ihdr.height = rgbaImage.height();
    ihdr.bit_depth = 8;
    ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR_ALPHA;

    spng_ctx *ctx = spng_ctx_new(SPNG_CTX_ENCODER);
    spng_set_ihdr(ctx, &ihdr);
    spng_set_option(ctx, SPNG_ENCODE_TO_BUFFER, 1);
    spng_set_option(ctx, SPNG_FILTER_CHOICE, SPNG_FILTER_CHOICE_NONE);
    spng_set_option(ctx, SPNG_IMG_COMPRESSION_LEVEL, 3);

    int ret = spng_encode_image(
        ctx, static_cast<const void *>(rgbaImage.bits()), rgbaImage.sizeInBytes(), SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE);

    if (ret) {
        spng_ctx_free(ctx);
        throw std::runtime_error("could not encode image, error: " + std::string(spng_strerror(ret)));
    }

    size_t png_size;
    auto buf = static_cast<unsigned char *>(spng_get_png_buffer(ctx, &png_size, &ret));

    if (buf == NULL) {
        spng_ctx_free(ctx);
        throw std::runtime_error("could not get encoded image, error: " + std::string(spng_strerror(ret)));
    }

    std::string out = std::string(buf, buf + png_size);

    free(buf);
    spng_ctx_free(ctx);

    return out;
}

const std::unique_ptr<uint8_t[]> MapRenderer::renderBuffer() {
    QImage rgbaImage = render();

    // Copy image data to buffer
    size_t dataSize = rgbaImage.sizeInBytes();
    auto buffer = std::make_unique<uint8_t[]>(dataSize);
    std::memcpy(buffer.get(), rgbaImage.bits(), dataSize);

    return buffer;
}

void MapRenderer::validateBearing(const double &bearing) {
    if (bearing < 0) {
        throw std::domain_error("bearing must be at least 0");
    }
    if (bearing > 360) {
        throw std::domain_error("bearing must be no greater than 360");
    }
}

void MapRenderer::validateDimension(const uint32_t &value, const std::string dimType) {
    if (value <= 0) {
        throw std::domain_error(dimType + " must be greater than 0");
    }
}

void MapRenderer::validatePitch(const double &pitch) {
    if (pitch < 0) {
        throw std::domain_error("pitch must be at least 0");
    }
    // Match Mapbox GL JS
    if (pitch > 85) {
        throw std::domain_error("pitch must be no greater than 85");
    }
}

void MapRenderer::validatePixelRatio(const float &ratio) {
    if (ratio <= 0) {
        throw std::domain_error("ratio must be greater than 0");
    }
    // arbitrary cutoff
    if (ratio > 8) {
        throw std::domain_error("ratio must be no greater than 8");
    }
}

void MapRenderer::validateZoom(const double &zoom) {
    if (zoom < 0) {
        throw std::domain_error("zoom must be greater than 0");
    }
    // Match Mapbox GL JS max zoom
    if (zoom > 24) {
        throw std::domain_error("zoom must be no greater than 24");
    }
}

void MapRenderer::release() {
    if (!_map) {
        return;
    }
    
    // Ensure context is current for cleanup
    if (_context && _context->isValid()) {
        _context->makeCurrent(_surface.get());
        
        // Destroy renderer before destroying map
        _map->destroyRenderer();
    }
    
    _map.reset();
    
    if (_context) {
        _context->doneCurrent();
        _context.reset();
    }
    _surface.reset();
    _app.reset();
}

}  // namespace PTR
