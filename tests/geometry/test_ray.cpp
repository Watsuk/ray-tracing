#include <catch2/catch_test_macros.hpp>
#include "geometry/Ray.h"
#include "test_helpers.h"

TEST_CASE("Ray getters", "[geometry][ray]") {
    Ray ray(Vector(1.0, 2.0, 3.0), Vector(3.0, 4.0, 0.0));
    requireVectorsEqual(ray.origin(), Vector(1.0, 2.0, 3.0));
    requireVectorsEqual(ray.direction(), Vector(3.0, 4.0, 0.0));
}
