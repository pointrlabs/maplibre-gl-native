# Require Qt for map-renderer
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Network REQUIRED)

add_executable(map-renderer src/main.cpp src/maprenderer.cpp src/spng.c)

target_include_directories(map-renderer PUBLIC include)
target_include_directories(map-renderer PRIVATE vendor)
target_include_directories(map-renderer PRIVATE ${PROJECT_SOURCE_DIR}/platform/qt/include)

# Link against qmaplibregl instead of mbgl-core
target_link_libraries(map-renderer PRIVATE 
    Mapbox::Base 
    qmaplibregl
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    z  # For zlib (spng dependency)
)

# Enable Qt OpenGL backend
target_compile_definitions(map-renderer PRIVATE __QT__ MBGL_USE_GLES2)

install(TARGETS map-renderer DESTINATION "${CMAKE_INSTALL_BINDIR}")
