#include <catch2/catch_test_macros.hpp>
#include "geometry/Sphere.h"

TEST_CASE("Sphere construction and getters", "[geometry][sphere][construction]") {
    SECTION("Initializes sphere with center vector and radius") {
        Vector center(0.0, 0.0, 5.0);
        Sphere sphere(center, 2.5);

        REQUIRE(sphere.center().x() == 0.0);
        REQUIRE(sphere.center().y() == 0.0);
        REQUIRE(sphere.center().z() == 5.0);

        REQUIRE(sphere.radius() == 2.5);
    }

    SECTION("Handles sphere at origin with unit radius") {
        Vector center(0.0, 0.0, 0.0);
        Sphere sphere(center, 1.0);

        REQUIRE(sphere.center().x() == 0.0);
        REQUIRE(sphere.center().y() == 0.0);
        REQUIRE(sphere.center().z() == 0.0);

        REQUIRE(sphere.radius() == 1.0);
    }
}
