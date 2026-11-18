#include <catch2/catch_test_macros.hpp>
#include "render/trace.h"

TEST_CASE("Trace ray against sphere", "[render][trace]") {
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    SECTION("Hits sphere with centre (0, 0, 9), gives red (1, 0, 0)") {
        Sphere sphere(Vector(0.0, 0.0, 9.0), 5.0, Colour(1.0, 0.0, 0.0));
        REQUIRE(trace(ray, sphere) == Colour(1.0, 0.0, 0.0));
    }

    SECTION("Misses sphere with centre (6, 0, 9), gives black (0, 0, 0)") {
        Sphere sphere(Vector(6.0, 0.0, 9.0), 5.0, Colour(1.0, 0.0, 0.0));
        REQUIRE(trace(ray, sphere) == Colour(0.0, 0.0, 0.0));
    }
}
