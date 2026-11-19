cmake_minimum_required(VERSION 3.22)

include(FetchContent)

# Automatically fetch and compile Catch2 v3 for Test-Driven Development (TDD)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Unit test executable linking core library and Catch2 main runner
add_executable(raytracer_tests
    test_helpers.cpp
    test_greeting.cpp
    math/test_vector_construction.cpp
    math/test_vector_addition.cpp
    math/test_vector_subtraction.cpp
    math/test_vector_multiplication.cpp
    math/test_vector_dot.cpp
    math/test_vector_length.cpp
    math/test_vector_normalize.cpp
    colour/test_colour.cpp
    geometry/test_ray.cpp
    render/test_camera.cpp
    geometry/test_sphere.cpp
    render/test_trace.cpp
    render/test_image.cpp
    io/test_image_saver.cpp
    material/test_material.cpp
    light/test_light.cpp
)

target_include_directories(raytracer_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(raytracer_tests PRIVATE
    raytracer_core
    Catch2::Catch2WithMain
)

# Integrate with CTest
include(CTest)
include(Catch)
catch_discover_tests(raytracer_tests)
