#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "raytracer/app.hpp"

TEST_CASE("Raytracer core greeting", "[core]") {
    SECTION("Returns the expected greeting message") {
        REQUIRE(raytracer::get_greeting() == "Hello, Raytracer!");
    }
}

TEST_CASE("Resolution calculations", "[core][math]") {
    SECTION("Calculates total pixels for given dimensions") {
        raytracer::Resolution hd{1920, 1080};
        REQUIRE(hd.total_pixels() == 2073600);

        raytracer::Resolution preview{640, 480};
        REQUIRE(preview.total_pixels() == 307200);
    }

    SECTION("Calculates aspect ratio accurately") {
        raytracer::Resolution hd{1920, 1080};
        REQUIRE_THAT(hd.aspect_ratio(), Catch::Matchers::WithinRel(16.0 / 9.0, 0.0001));
    }

    SECTION("Safely handles zero or negative height without division by zero") {
        raytracer::Resolution zero_res{1920, 0};
        REQUIRE(zero_res.aspect_ratio() == 0.0);

        raytracer::Resolution negative_res{1920, -10};
        REQUIRE(negative_res.aspect_ratio() == 0.0);
    }
}
