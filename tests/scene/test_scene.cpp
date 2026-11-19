#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <memory>
#include "scene/scene.h"
#include "geometry/Sphere.h"
#include "geometry/plane.h"
#include "geometry/Ray.h"
#include "colour/Colour.h"
#include "material/Material.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("Scene nearestHit returns nearest shape intersection", "[scene]") {
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    SECTION("the sphere, then a blue plane through (0, 0, 2) with normal (0, 0, -1): hit is plane's at t = 3") {
        Scene scene(Vector(0.0, 0.0, -1.0));
        scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, Material(Colour(1.0, 0.0, 0.0))));
        scene.add(std::make_unique<Plane>(Vector(0.0, 0.0, 2.0), Vector(0.0, 0.0, -1.0), Material(Colour(0.0, 0.0, 1.0))));

        auto hit = scene.nearestHit(ray);
        REQUIRE(hit.has_value());
        REQUIRE_THAT(hit->t, WithinAbs(3.0, tolerance));
        REQUIRE(hit->material != nullptr);
        REQUIRE(hit->material->colour() == Colour(0.0, 0.0, 1.0));
    }

    SECTION("the sphere, then a blue plane through (0, 0, 20) with normal (0, 0, -1): hit is sphere's at t = 5") {
        Scene scene(Vector(0.0, 0.0, -1.0));
        scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, Material(Colour(1.0, 0.0, 0.0))));
        scene.add(std::make_unique<Plane>(Vector(0.0, 0.0, 20.0), Vector(0.0, 0.0, -1.0), Material(Colour(0.0, 0.0, 1.0))));

        auto hit = scene.nearestHit(ray);
        REQUIRE(hit.has_value());
        REQUIRE_THAT(hit->t, WithinAbs(5.0, tolerance));
        REQUIRE(hit->material != nullptr);
        REQUIRE(hit->material->colour() == Colour(1.0, 0.0, 0.0));
    }

    SECTION("only a sphere with centre (6, 0, 9): nothing") {
        Scene scene(Vector(0.0, 0.0, -1.0));
        scene.add(std::make_unique<Sphere>(Vector(6.0, 0.0, 9.0), 5.0, Material(Colour(1.0, 0.0, 0.0))));

        auto hit = scene.nearestHit(ray);
        REQUIRE_FALSE(hit.has_value());
    }
}
