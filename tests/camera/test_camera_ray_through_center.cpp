#include <catch2/catch_test_macros.hpp>
#include "render/Camera.h"

TEST_CASE("Camera ray through center", "[camera][rayThroughCenter]") {
    SECTION("Generates ray starting from camera origin and facing positive Z") {
        Vector origin(1.0, 2.0, -3.0);
        Camera camera(origin);
        Ray ray = camera.rayThroughCenter();

        REQUIRE(ray.origin().x() == 1.0);
        REQUIRE(ray.origin().y() == 2.0);
        REQUIRE(ray.origin().z() == -3.0);

        REQUIRE(ray.direction().x() == 0.0);
        REQUIRE(ray.direction().y() == 0.0);
        REQUIRE(ray.direction().z() == 1.0);
    }
}
