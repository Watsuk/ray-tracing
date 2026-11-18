#include <catch2/catch_test_macros.hpp>
#include "Ray.h"

TEST_CASE("Ray construction and getters", "[math][ray][construction]") {
    SECTION("Initializes ray with origin and direction vectors") {
        Vector origin(1.0, 2.0, 3.0);
        Vector direction(0.0, 1.0, 0.0);
        Ray ray(origin, direction);

        REQUIRE(ray.origin().x() == 1.0);
        REQUIRE(ray.origin().y() == 2.0);
        REQUIRE(ray.origin().z() == 3.0);

        REQUIRE(ray.direction().x() == 0.0);
        REQUIRE(ray.direction().y() == 1.0);
        REQUIRE(ray.direction().z() == 0.0);
    }

    SECTION("Handles zero origin and negative direction") {
        Vector origin(0.0, 0.0, 0.0);
        Vector direction(-1.0, -2.0, -3.0);
        Ray ray(origin, direction);

        REQUIRE(ray.origin().x() == 0.0);
        REQUIRE(ray.origin().y() == 0.0);
        REQUIRE(ray.origin().z() == 0.0);

        REQUIRE(ray.direction().x() == -1.0);
        REQUIRE(ray.direction().y() == -2.0);
        REQUIRE(ray.direction().z() == -3.0);
    }
}
