#include <catch2/catch_test_macros.hpp>
#include "geometry/Sphere.h"
#include "geometry/Ray.h"
#include "colour/Colour.h"

TEST_CASE("Sphere ray intersection and colour", "[geometry][sphere]") {
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    SECTION("Ray hits sphere with centre (0, 0, 9)") {
        Sphere sphere(Vector(0.0, 0.0, 9.0), 5.0, Colour(1.0, 0.0, 0.0));
        REQUIRE(sphere.isHitBy(ray));
        REQUIRE(sphere.colour() == Colour(1.0, 0.0, 0.0));
    }

    SECTION("Ray hits off-centre sphere with centre (3, 0, 9)") {
        Sphere sphere(Vector(3.0, 0.0, 9.0), 5.0, Colour(0.0, 1.0, 0.0));
        REQUIRE(sphere.isHitBy(ray));
    }

    SECTION("Ray misses sphere with centre (6, 0, 9)") {
        Sphere sphere(Vector(6.0, 0.0, 9.0), 5.0, Colour(0.0, 0.0, 1.0));
        REQUIRE_FALSE(sphere.isHitBy(ray));
    }

    SECTION("Ray misses sphere behind camera with centre (0, 0, -11)") {
        Sphere sphere(Vector(0.0, 0.0, -11.0), 5.0, Colour(1.0, 0.0, 0.0));
        REQUIRE_FALSE(sphere.isHitBy(ray));
    }
}
