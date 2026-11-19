#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "render/Camera.h"
#include "geometry/Sphere.h"
#include "scene/scene.h"
#include "material/Material.h"
#include "test_helpers.h"

TEST_CASE("Camera rayThroughCenter", "[render][camera]") {
    Camera camera(Vector(0.0, 0.0, -1.0));
    Ray ray = camera.rayThroughCenter();
    requireVectorsEqual(ray.origin(), Vector(0.0, 0.0, -1.0));
    requireVectorsEqual(ray.direction(), Vector(0.0, 0.0, 1.0));
}

TEST_CASE("Camera rayThroughPixel", "[render][camera]") {
    const double screenWidth = 5.0;
    Camera camera(Vector(0.0, 0.0, -1.0), screenWidth);
    const int imageWidth = 5;
    const int imageHeight = 3;

    SECTION("pixel (2, 1) in the center has direction (0, 0, 1)") {
        Ray ray = camera.rayThroughPixel(2, 1, imageWidth, imageHeight);
        requireVectorsEqual(ray.origin(), Vector(0.0, 0.0, -1.0));
        requireVectorsEqual(ray.direction(), Vector(0.0, 0.0, 1.0));
    }

    SECTION("pixel (4, 0) top right has direction (2, 1, 1)") {
        Ray ray = camera.rayThroughPixel(4, 0, imageWidth, imageHeight);
        requireVectorsEqual(ray.origin(), Vector(0.0, 0.0, -1.0));
        requireVectorsEqual(ray.direction(), Vector(2.0, 1.0, 1.0));
    }

    SECTION("pixel (0, 2) bottom left has direction (-2, -1, 1)") {
        Ray ray = camera.rayThroughPixel(0, 2, imageWidth, imageHeight);
        requireVectorsEqual(ray.origin(), Vector(0.0, 0.0, -1.0));
        requireVectorsEqual(ray.direction(), Vector(-2.0, -1.0, 1.0));
    }

    SECTION("different pixel size: pixelSize = 2.0 with screenWidth = 10.0") {
        Camera cameraLarge(Vector(0.0, 0.0, -1.0), 10.0);

        // Center pixel (2, 1) still has direction (0, 0, 1)
        Ray centerRay = cameraLarge.rayThroughPixel(2, 1, imageWidth, imageHeight);
        requireVectorsEqual(centerRay.direction(), Vector(0.0, 0.0, 1.0));

        // Top right pixel (4, 0) scales by 2.0: offset (2, 1) -> (4, 2, 1)
        Ray topRightRay = cameraLarge.rayThroughPixel(4, 0, imageWidth, imageHeight);
        requireVectorsEqual(topRightRay.direction(), Vector(4.0, 2.0, 1.0));

        // Bottom left pixel (0, 2) scales by 2.0: offset (-2, -1) -> (-4, -2, 1)
        Ray bottomLeftRay = cameraLarge.rayThroughPixel(0, 2, imageWidth, imageHeight);
        requireVectorsEqual(bottomLeftRay.direction(), Vector(-4.0, -2.0, 1.0));
    }
}

TEST_CASE("Camera render function", "[render][camera]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 5.0);

    SECTION("renders image with correct dimensions and colours") {
        Scene scene(Vector(0.0, 0.0, -1.0));
        scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, Material(Colour(1.0, 0.0, 0.0))));

        Image img = camera.render(scene, 5, 3);
        REQUIRE(img.width() == 5);
        REQUIRE(img.height() == 3);

        // Center pixel (2, 1) hits the red sphere
        REQUIRE(img.pixel(2, 1) == Colour(1.0, 0.0, 0.0));

        // Top right (4, 0) and bottom left (0, 2) miss the sphere and are black
        REQUIRE(img.pixel(4, 0) == Colour(0.0, 0.0, 0.0));
        REQUIRE(img.pixel(0, 2) == Colour(0.0, 0.0, 0.0));
    }

    SECTION("renders into an existing image buffer") {
        Scene scene(Vector(0.0, 0.0, -1.0));
        scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, Material(Colour(1.0, 0.0, 0.0))));

        Image img(5, 3);
        camera.render(img, scene);

        REQUIRE(img.pixel(2, 1) == Colour(1.0, 0.0, 0.0));
        REQUIRE(img.pixel(4, 0) == Colour(0.0, 0.0, 0.0));
    }
}
