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
    test_greeting.cpp
)

target_link_libraries(raytracer_tests PRIVATE
    raytracer_core
    Catch2::Catch2WithMain
)

# Integrate with CTest
include(CTest)
include(Catch)
catch_discover_tests(raytracer_tests)
