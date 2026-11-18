#include <catch2/catch_test_macros.hpp>
#include "render/Camera.h"
#include "test_helpers.h"

TEST_CASE("Camera ray generation", "[render][camera]") {
    SECTION("Camera facing positive Z axis through screen centre (0, 0, 0)") {
        Camera camera(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 0.0));
        Ray ray = camera.ray();
        requireVectorsEqual(ray.origin(), Vector(0.0, 0.0, -1.0));
        requireVectorsEqual(ray.direction(), Vector(0.0, 0.0, 1.0));
    }

    SECTION("Camera with 3-4-5 direction") {
        Camera camera(Vector(1.0, 2.0, -1.0), Vector(4.0, 6.0, -1.0));
        Ray ray = camera.ray();
        requireVectorsEqual(ray.origin(), Vector(1.0, 2.0, -1.0));
        requireVectorsEqual(ray.direction(), Vector(3.0, 4.0, 0.0));
    }
}
