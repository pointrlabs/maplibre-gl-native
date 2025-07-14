# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Development Commands

### Building
- **Core build with CMake**: `cmake -S . -B build && cmake --build build`
- **Android**: `cd platform/android && BUILDTYPE=Debug make apackage` (or `BUILDTYPE=Release`)
- **iOS**: `cd platform/ios && make iproj` (opens Xcode), or `make xcframework BUILDTYPE=Release`
- **macOS**: `cd platform/ios && make xpackage`
- **Node.js**: `npm test` (runs various test suites)
- **Qt**: Follow platform-specific configuration scripts in `platform/qt/scripts/`

### Qt and Map Renderer Specific Commands
- **qmaplibregl configuration**: `cmake -S . -B build -GNinja -DMBGL_WITH_QT=ON -DMBGL_QT_LIBRARY_ONLY=ON -DMBGL_QT_WITH_INTERNAL_SQLITE=ON -DMBGL_QT_WITH_INTERNAL_ICU=ON -DMBGL_WITH_WERROR=OFF`
- **map-renderer configuration**: `cmake -S . -B build -GNinja -DMBGL_WITH_MAP_RENDERER=ON -DMBGL_WITH_WERROR=OFF`

### Testing
- **Unit tests**: `cmake --build build --target test`
- **Node.js tests**: `npm run test`, `npm run test-render`, `npm run test-expressions`
- **iOS tests**: `cd platform/ios && make ios-test`
- **Android tests**: Use Android Studio or `cd platform/android && ./gradlew test`

### Utilities
- **Render tests**: Build and run the `render-test` target
- **Benchmarks**: Build and run the `benchmark` target
- **Map renderer**: Build with `-DMBGL_WITH_MAP_RENDERER=ON`

## Architecture Overview

MapLibre GL Native is a cross-platform C++ library that renders interactive maps using OpenGL. Key architectural components:

### Core Structure
- **`src/mbgl/`**: Core C++ implementation organized by functionality
- **`include/mbgl/`**: Public API headers
- **`platform/`**: Platform-specific bindings (Android, iOS, macOS, Qt, Node.js)

### Key Components
1. **Map (`src/mbgl/map/`)**: Main map class, camera, transforms, and coordinate systems
2. **Style (`src/mbgl/style/`)**: Implementation of Mapbox Style Specification with runtime styling API
3. **Renderer (`src/mbgl/renderer/`)**: OpenGL rendering system, render passes, and buckets
4. **Tile System (`src/mbgl/tile/`)**: Vector, raster, and geometry tile handling
5. **Text (`src/mbgl/text/`)**: Glyph management, text shaping, and collision detection
6. **Storage (`src/mbgl/storage/`)**: File sources, caching, and offline functionality
7. **Layout (`src/mbgl/layout/`)**: Symbol placement and line/polygon tessellation

### Threading Model
- **Main thread**: Handles API calls, owns Style objects, renders map
- **Worker threads**: Process vector tiles, compute layouts (4 per Style)
- **FileSource thread**: Network requests and SQLite I/O

### Immutability Pattern
The codebase uses immutable objects for thread-safe data sharing:
- **Mutable**: `Layer`, `Source`, `Image`, `Light` (public API)
- **Immutable**: `Layer::Impl`, `Source::Impl`, etc. (internal implementation)
- Changes create new immutable copies, enabling efficient style diffing

## Platform-Specific Notes

### Android
- Uses JNI for Java↔C++ communication
- Build system: Gradle + CMake
- Main entry point: `platform/android/src/jni.cpp`

### iOS/macOS
- Objective-C++ bindings with `MGL` prefix
- Build system: Xcode + CMake
- Headers in `platform/ios/platform/darwin/include/`

### Qt
- `QMapLibreGL` classes provide Qt integration
- Supports both Qt5 and Qt6
- Uses Qt's OpenGL context management

### Node.js
- Headless rendering for server-side map generation
- V8 JavaScript bindings
- Exports in `platform/node/index.js`

## Build Configuration

### CMake Options
- `MBGL_WITH_OPENGL`: Build with OpenGL renderer (default: ON)
- `MBGL_WITH_QT`: Build Qt bindings
- `MBGL_WITH_COVERAGE`: Enable code coverage
- `MBGL_WITH_SANITIZER`: Use sanitizers (address/thread/undefined)
- `MBGL_WITH_MAP_RENDERER`: Build map renderer utility

### Dependencies
- Uses Mason package manager for C++ dependencies
- Vendor libraries in `vendor/` directory
- Major dependencies: Boost, RapidJSON, SQLite, Mapbox modules

## Code Style

### Important Files
- **CMakeLists.txt**: Main build configuration
- **package.json**: Node.js dependencies and scripts
- **platform/*/**: Platform-specific build files and source
- **src/mbgl/**: Core implementation following component structure
- **include/mbgl/**: Public API with namespaced headers

### Key Patterns
- Headers always included as `#include <mbgl/___/___.hpp>`
- Immutable objects for thread-safe sharing
- Factory pattern for style layers and sources
- RAII for resource management
- Expression system for data-driven styling

## Important Debugging/Development Notes

- The codebase is a fork of Mapbox GL Native from commit d60fd30
- Uses C++17 standard
- OpenGL ES 2.0 compatible
- Supports both vector and raster tile sources
- Runtime style modification through strongly-typed API
- Efficient style diffing for smooth transitions between different styles