#include <catch2/catch_test_macros.hpp>
#include "geometry/Sphere.h"
#include "geometry/Ray.h"

TEST_CASE("Sphere ray intersection hit", "[geometry][sphere][hit]") {
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0);

    SECTION("Ray pointing directly at sphere intersects") {
        Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));
        REQUIRE(sphere.hit(ray) == true);
    }

    SECTION("Ray pointing away from sphere does not intersect") {
        Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0));
        REQUIRE(sphere.hit(ray) == false);
    }

    SECTION("Ray pointing in opposite direction does not intersect") {
        Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0));
        REQUIRE(sphere.hit(ray) == false);
    }

    SECTION("Ray skimming tangent to sphere intersects") {
        Ray ray(Vector(1.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));
        REQUIRE(sphere.hit(ray) == true);
    }
}
