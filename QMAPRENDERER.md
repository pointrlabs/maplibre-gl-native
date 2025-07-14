# QMAPRENDERER.md

This file documents the conversion of the map-renderer target from platform-specific OpenGL to Qt OpenGL facilities, enabling it to depend solely on qmaplibregl.

## Current map-renderer Architecture

### OpenGL Dependencies
The map-renderer currently uses platform-specific headless OpenGL backends:
- **Linux**: EGL (`headless_backend_egl.cpp`) or GLX (`headless_backend_glx.cpp`)
- **macOS**: Core Graphics Layer (`headless_backend_cgl.mm`)
- **Function Loading**: Platform-specific OpenGL function resolution

### Key Components
- **Entry Point**: `map-renderer/src/main.cpp` - Command-line utility
- **Core Class**: `map-renderer/src/maprenderer.cpp` - `PTR::MapRenderer` class
- **Dependencies**: 
  - `mbgl::HeadlessFrontend` - Main rendering interface
  - `mbgl::gfx::HeadlessBackend` - Platform-specific backend factory
  - `mbgl-core` library with platform-specific OpenGL backends

### Build Configuration
```bash
# Current build command
cmake -S . -B build -GNinja -DMBGL_WITH_MAP_RENDERER=ON -DMBGL_WITH_WERROR=OFF
```

## Qt OpenGL Integration (qmaplibregl)

### Architecture
qmaplibregl provides a complete Qt-based OpenGL abstraction:
- **Context Management**: `QOpenGLContext` and `QOffscreenSurface`
- **Function Loading**: All OpenGL calls wrapped through Qt's `QOpenGLFunctions`
- **Headless Support**: `headless_backend_qt.cpp` for offscreen rendering
- **Thread Safety**: Proper synchronization between UI and render threads

### Key Files
- `platform/qt/src/mbgl/headless_backend_qt.cpp` - Qt headless backend
- `platform/qt/src/mbgl/gl_functions.cpp` - Qt OpenGL function wrapping
- `platform/qt/src/mbgl/map_renderer.cpp` - Qt-based map renderer

### Build Options
```bash
# Qt OpenGL configuration
cmake -S . -B build -GNinja -DMBGL_WITH_QT=ON -DMBGL_QT_LIBRARY_ONLY=ON -DMBGL_QT_WITH_HEADLESS=ON
```

## Conversion Strategy

### Goal
Convert map-renderer to use Qt OpenGL facilities exclusively, making it depend only on qmaplibregl library for deployment.

### Required Changes

#### 1. CMake Configuration
- Modify `map-renderer/CMakeLists.txt` to require Qt and qmaplibregl
- Replace `mbgl-core` dependency with qmaplibregl
- Enable Qt OpenGL backend selection

#### 2. Code Changes
- Update `MapRenderer` class to use Qt OpenGL context management
- Replace `mbgl::HeadlessFrontend` with Qt-based rendering
- Ensure proper Qt application initialization for headless context

#### 3. Dependencies
- Link against Qt OpenGL libraries instead of platform OpenGL
- Use Qt's OpenGL function resolution system
- Leverage existing Qt headless backend implementation

### Implementation Steps

1. **Analyze Current Dependencies**: ✓ Completed
   - Platform-specific backends: EGL/GLX/CGL
   - OpenGL function loading mechanisms
   - Build system integration

2. **Examine Qt Integration**: ✓ Completed  
   - Qt OpenGL context management
   - Headless rendering capabilities
   - Function abstraction layer

3. **Identify Replacement Code**: ✓ Completed
   - Files to replace: `headless_backend_*.cpp`, `gl_functions.cpp`
   - Qt alternatives: `headless_backend_qt.cpp`, Qt OpenGL functions

4. **Plan Conversion**: ✓ Completed
   - Use existing Qt infrastructure
   - Modify build configuration
   - Update map-renderer implementation

### Benefits of Qt Conversion

1. **Simplified Deployment**: Single qmaplibregl library dependency
2. **Cross-Platform**: Qt handles platform OpenGL differences
3. **Maintenance**: Leverages existing Qt OpenGL infrastructure
4. **Performance**: Qt's optimized OpenGL context management
5. **Compatibility**: Maintains headless rendering capabilities

### Platform-Specific Code to Replace

#### Files to Remove/Replace:
- `platform/linux/src/headless_backend_egl.cpp`
- `platform/linux/src/headless_backend_glx.cpp` 
- `platform/darwin/src/headless_backend_cgl.mm`
- `platform/linux/src/gl_functions.cpp`
- `platform/darwin/src/gl_functions.cpp`

#### Qt Alternatives Already Available:
- `platform/qt/src/mbgl/headless_backend_qt.cpp`
- `platform/qt/src/mbgl/gl_functions.cpp`
- Qt OpenGL context management system

### Testing Strategy

1. **Build Testing**: Ensure map-renderer builds with Qt dependencies only
2. **Functional Testing**: Verify PNG output matches current implementation
3. **Performance Testing**: Compare rendering performance with platform backends
4. **Deployment Testing**: Test with qmaplibregl-only installation

### Future Considerations

- Qt version compatibility (Qt5/Qt6)
- High-DPI rendering support
- Multi-threading considerations
- Memory management optimization

## Development Commands

### Current Commands
```bash
# Build current map-renderer
cmake -S . -B build -GNinja -DMBGL_WITH_MAP_RENDERER=ON
cmake --build build --target map-renderer

# Run map-renderer
./build/map-renderer --style style.json --output output.png
```

### Future Qt-based Commands
```bash
# Build Qt-based map-renderer
cmake -S . -B build -GNinja -DMBGL_WITH_QT=ON -DMBGL_QT_WITH_HEADLESS=ON -DMBGL_WITH_MAP_RENDERER=ON
cmake --build build --target map-renderer

# Deploy with qmaplibregl only
# Target: map-renderer executable + qmaplibregl library
```