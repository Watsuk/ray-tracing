#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "geometry/Sphere.h"
#include "geometry/Ray.h"
#include "colour/Colour.h"
#include "geometry/HitInfo.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("Sphere ray intersection and colour", "[geometry][sphere]") {
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    SECTION("Ray hits sphere with centre (0, 0, 9)") {
        Sphere sphere(Vector(0.0, 0.0, 9.0), 5.0, Colour(1.0, 0.0, 0.0));
        REQUIRE(sphere.isHitBy(ray));
        REQUIRE(sphere.colour() == Colour(1.0, 0.0, 0.0));
    }

    SECTION("Ray hits off-centre sphere with centre (3, 0, 9)") {
        Sphere sphere(Vector(3.0, 0.0, 9.0), 5.0, Colour(0.0, 1.0, 0.0));
        REQUIRE(sphere.isHitBy(ray));
    }

    SECTION("Ray misses sphere with centre (6, 0, 9)") {
        Sphere sphere(Vector(6.0, 0.0, 9.0), 5.0, Colour(0.0, 0.0, 1.0));
        REQUIRE_FALSE(sphere.isHitBy(ray));
    }

    SECTION("Ray misses sphere behind camera with centre (0, 0, -11)") {
        Sphere sphere(Vector(0.0, 0.0, -11.0), 5.0, Colour(1.0, 0.0, 0.0));
        REQUIRE_FALSE(sphere.isHitBy(ray));
    }
}

TEST_CASE("Sphere hit returns HitInfo / Hinfo", "[geometry][sphere][hit]") {
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    SECTION("Hits sphere: returns valid HitInfo with point, normal, material") {
        Sphere sphere(Vector(0.0, 0.0, 9.0), 5.0, Colour(1.0, 0.0, 0.0));
        auto hitInfo = sphere.hit(ray);

        REQUIRE(hitInfo != nullptr);
        REQUIRE(hitInfo->t > 0.0);
        requireVectorsEqual(hitInfo->point, Vector(0.0, 0.0, 4.0));
        requireVectorsEqual(hitInfo->normal, Vector(0.0, 0.0, -1.0));
        REQUIRE(hitInfo->material != nullptr);
        REQUIRE(hitInfo->material->shade(ray) == Colour(1.0, 0.0, 0.0));

        // Verify Hinfo alias
        std::optional<Hinfo> hinfo = hitInfo;
        REQUIRE(hinfo != nullptr);
    }

    SECTION("Misses sphere: returns null") {
        Sphere sphere(Vector(6.0, 0.0, 9.0), 5.0, Colour(0.0, 1.0, 0.0));
        auto hitInfo = sphere.hit(ray);

        REQUIRE(hitInfo == nullptr);
    }

    SECTION("Sphere behind camera: returns null") {
        Sphere sphere(Vector(0.0, 0.0, -11.0), 5.0, Colour(0.0, 0.0, 1.0));
        auto hitInfo = sphere.hit(ray);

        REQUIRE(hitInfo == nullptr);
    }

    SECTION("Ray inside sphere around eye with centre (0, 0, 1) and radius 5: hits at t = 7, point (0, 0, 6), normal (0, 0, 1)") {
        Sphere sphere(Vector(0.0, 0.0, 1.0), 5.0, Colour(1.0, 0.0, 0.0));
        auto hitInfo = sphere.hit(ray);
        REQUIRE(hitInfo != nullptr);
        REQUIRE_THAT(hitInfo->t, WithinAbs(7.0, tolerance));
        requireVectorsEqual(hitInfo->point, Vector(0.0, 0.0, 6.0));
        requireVectorsEqual(hitInfo->normal, Vector(0.0, 0.0, 1.0));
    }

    SECTION("Polymorphism: Shape reference calls Sphere::hit") {
        Sphere sphere(Vector(0.0, 0.0, 9.0), 5.0, Colour(1.0, 0.0, 0.0));
        const Shape& shape = sphere;
        std::optional<Hit> hit = shape.hit(ray);
        REQUIRE(hit.has_value());
        REQUIRE(hit->t > 0.0);
        requireVectorsEqual(hit->point, Vector(0.0, 0.0, 4.0));
        requireVectorsEqual(hit->normal, Vector(0.0, 0.0, -1.0));
    }
}
