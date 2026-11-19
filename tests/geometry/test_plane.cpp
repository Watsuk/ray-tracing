#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "geometry/plane.h"
#include "geometry/Ray.h"
#include "material/FlatShader.h"
#include "colour/Colour.h"
#include "light/Light.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("Plane ray intersection", "[geometry][plane]") {
    FlatShader green(Colour(0.0, 1.0, 0.0));

    SECTION("the floor: hits at t = 2, point (6, 0, 0), normal (0, 1, 0), green material") {
        Plane floor(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), green);
        Ray ray(Vector(0.0, 8.0, 0.0), Vector(3.0, -4.0, 0.0));

        auto hit = floor.hit(ray);
        REQUIRE(hit.has_value());
        REQUIRE_THAT(hit->t, WithinAbs(2.0, tolerance));
        requireVectorsEqual(hit->point, Vector(6.0, 0.0, 0.0));
        requireVectorsEqual(hit->normal, Vector(0.0, 1.0, 0.0));
        REQUIRE(hit->material != nullptr);
        Light dummyLight(Vector(0.0, 0.0, -1.0), Colour(1.0, 1.0, 1.0));
        REQUIRE(hit->material->shade(*hit, dummyLight) == Colour(0.0, 1.0, 0.0));
    }

    SECTION("the line 3x + 4y = 24: hits at t = 2, point (0, 6, 0), normal (0.6, 0.8, 0)") {
        Plane line(Vector(8.0, 0.0, 0.0), Vector(3.0, 4.0, 0.0), green);
        Ray ray(Vector(-8.0, 0.0, 0.0), Vector(4.0, 3.0, 0.0));

        auto hit = line.hit(ray);
        REQUIRE(hit.has_value());
        REQUIRE_THAT(hit->t, WithinAbs(2.0, tolerance));
        requireVectorsEqual(hit->point, Vector(0.0, 6.0, 0.0));
        requireVectorsEqual(hit->normal, Vector(0.6, 0.8, 0.0));
    }

    SECTION("the floor, with direction (5, 0, 0): parallel, returns nothing") {
        Plane floor(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), green);
        Ray ray(Vector(0.0, 8.0, 0.0), Vector(5.0, 0.0, 0.0));

        auto hit = floor.hit(ray);
        REQUIRE_FALSE(hit.has_value());
    }

    SECTION("the floor, with direction (3, 4, 0): behind, returns nothing") {
        Plane floor(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), green);
        Ray ray(Vector(0.0, 8.0, 0.0), Vector(3.0, 4.0, 0.0));

        auto hit = floor.hit(ray);
        REQUIRE_FALSE(hit.has_value());
    }
}
