cmake_minimum_required(VERSION 3.22)

project(raytracer
    VERSION 0.1.0
    DESCRIPTION "A modern, maintainable C++ Raytracer"
    LANGUAGES CXX
)

# Standard C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for LSP (clangd, Zed, VSCode)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Consistent binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Compiler warnings interface library
add_library(project_warnings INTERFACE)
if(MSVC)
    target_compile_options(project_warnings INTERFACE /W4)
else()
    target_compile_options(project_warnings INTERFACE -Wall -Wextra -Wpedantic)
endif()

# Fetch and configure LodePNG (pinned version)
include(FetchContent)
FetchContent_Declare(
    lodepng
    GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
    GIT_TAG        7b2893e35891c0c85bee5595caafaf3c2044b409
)

FetchContent_GetProperties(lodepng)
if(NOT lodepng_POPULATED)
    FetchContent_Populate(lodepng)
    add_library(lodepng STATIC
        "${lodepng_SOURCE_DIR}/lodepng.cpp"
    )
    target_include_directories(lodepng SYSTEM PUBLIC
        "${lodepng_SOURCE_DIR}"
    )
endif()

# Core raytracer library (separates engine logic from CLI main for clean TDD)
add_library(raytracer_core
    src/app.cpp
    src/math/Vector.cpp
    src/geometry/Ray.cpp
    src/geometry/Sphere.cpp
    src/render/Camera.cpp
    src/colour/Colour.cpp
    src/render/trace.cpp
    src/render/Image.cpp
    src/io/PngSaver.cpp
    src/material/FlatShader.cpp
)

target_include_directories(raytracer_core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(raytracer_core PUBLIC
    project_warnings
    lodepng
)

# Main CLI executable
add_executable(raytracer
    src/main.cpp
)

target_link_libraries(raytracer PRIVATE
    raytracer_core
)

# Testing configuration
option(BUILD_TESTING "Build the test suite" ON)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
