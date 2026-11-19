#include <catch2/catch_test_macros.hpp>
#include "geometry/Ray.h"
#include "test_helpers.h"

TEST_CASE("Ray getters", "[geometry][ray]") {
    Ray ray(Vector(1.0, 2.0, 3.0), Vector(3.0, 4.0, 0.0));
    requireVectorsEqual(ray.origin(), Vector(1.0, 2.0, 3.0));
    requireVectorsEqual(ray.direction(), Vector(3.0, 4.0, 0.0));
}

TEST_CASE("Ray at position t", "[geometry][ray]") {
    Ray ray(Vector(1.0, 2.0, 3.0), Vector(2.0, 0.0, -1.0));

    SECTION("at t = 0 returns origin") {
        requireVectorsEqual(ray.at(0.0), Vector(1.0, 2.0, 3.0));
    }

    SECTION("at t = 1 returns origin + direction") {
        requireVectorsEqual(ray.at(1.0), Vector(3.0, 2.0, 2.0));
    }

    SECTION("at t = 2.5 calculates correctly") {
        requireVectorsEqual(ray.at(2.5), Vector(6.0, 2.0, 0.5));
    }
}
