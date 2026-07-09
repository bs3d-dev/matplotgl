cmake_minimum_required(VERSION 3.16)

project(matplotgl VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/gui")

find_package(Qt6 COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets REQUIRED)
set(QT_VERSION_MAJOR 6)

find_package(Matplot++ REQUIRED)

set(MATPLOTGL_SOURCES
    src/axis_widget.cpp
    src/colorbar.cpp
    src/colormap.cpp
    src/glview.cpp
    src/legend_box.cpp
    src/matqt.cpp
    src/matqt_widget.cpp
    src/shader.cpp
    src/title_widget.cpp
)

set(MATPLOTGL_HEADERS
    include/axis_widget.h
    include/colorbar.h
    include/colormap.h
    include/glview.h
    include/legend_box.h
    include/matqt.h
    include/matqt_widget.h
    include/shader.h
    include/title_widget.h
    include/util.h
)

set(MATPLOTGL_UIS
    gui/matqt_widget.ui
)

add_library(matplotgl STATIC
    ${MATPLOTGL_SOURCES}
    ${MATPLOTGL_HEADERS}
    ${MATPLOTGL_UIS}
)

target_include_directories(matplotgl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/glm/include>
)

target_link_libraries(matplotgl
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::OpenGL
        Qt${QT_VERSION_MAJOR}::OpenGLWidgets
        Matplot++::matplot
)

if(WIN32)
    target_link_libraries(matplotgl PUBLIC opengl32)
endif()

install(TARGETS matplotgl
    EXPORT matplotglTargets
    ARCHIVE DESTINATION $<$<CONFIG:Debug>:debug/>${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION $<$<CONFIG:Debug>:debug/>${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

set(MATPLOTGL_CMAKE_CONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/matplotgl)

install(EXPORT matplotglTargets
    FILE matplotglTargets.cmake
    NAMESPACE matplotgl::
    DESTINATION ${MATPLOTGL_CMAKE_CONFIG_DIR}
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/matplotglConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/matplotglConfig.cmake"
    INSTALL_DESTINATION ${MATPLOTGL_CMAKE_CONFIG_DIR}
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/matplotglConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/matplotglConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/matplotglConfigVersion.cmake"
    DESTINATION ${MATPLOTGL_CMAKE_CONFIG_DIR}
)
