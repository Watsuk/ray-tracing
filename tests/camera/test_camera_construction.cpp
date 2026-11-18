#include <catch2/catch_test_macros.hpp>
#include "render/Camera.h"

TEST_CASE("Camera construction and getters", "[camera][construction]") {
    SECTION("Constructor with origin defaults direction to positive Z-axis") {
        Vector origin(0.0, 1.0, -5.0);
        Camera camera(origin);

        REQUIRE(camera.origin().x() == 0.0);
        REQUIRE(camera.origin().y() == 1.0);
        REQUIRE(camera.origin().z() == -5.0);

        REQUIRE(camera.direction().x() == 0.0);
        REQUIRE(camera.direction().y() == 0.0);
        REQUIRE(camera.direction().z() == 1.0);
    }

    SECTION("Constructor with explicit origin and direction sets both") {
        Vector origin(2.0, 3.0, 4.0);
        Vector direction(1.0, 0.0, 0.0);
        Camera camera(origin, direction);

        REQUIRE(camera.origin().x() == 2.0);
        REQUIRE(camera.origin().y() == 3.0);
        REQUIRE(camera.origin().z() == 4.0);

        REQUIRE(camera.direction().x() == 1.0);
        REQUIRE(camera.direction().y() == 0.0);
        REQUIRE(camera.direction().z() == 0.0);
    }
}
