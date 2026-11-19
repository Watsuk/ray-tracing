#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "render/trace.h"
#include "scene/scene.h"
#include "geometry/Sphere.h"
#include "material/Material.h"

TEST_CASE("Trace ray against scene", "[render][trace]") {
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    SECTION("Hits sphere with centre (0, 0, 9), gives red (1, 0, 0)") {
        Scene scene(Vector(0.0, 0.0, -1.0));
        scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, Material(Colour(1.0, 0.0, 0.0))));
        REQUIRE(trace(ray, scene) == Colour(1.0, 0.0, 0.0));
    }

    SECTION("Misses sphere with centre (6, 0, 9), gives black (0, 0, 0)") {
        Scene scene(Vector(0.0, 0.0, -1.0));
        scene.add(std::make_unique<Sphere>(Vector(6.0, 0.0, 9.0), 5.0, Material(Colour(1.0, 0.0, 0.0))));
        REQUIRE(trace(ray, scene) == Colour(0.0, 0.0, 0.0));
    }
}
