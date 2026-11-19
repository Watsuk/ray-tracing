#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <memory>
#include <cmath>
#include "material/Material.h"
#include "material/FlatShader.h"
#include "material/LambertShader.h"
#include "geometry/Sphere.h"
#include "geometry/Ray.h"
#include "geometry/HitInfo.h"
#include "light/Light.h"
#include "render/trace.h"
#include "render/Camera.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

// Custom test material to prove the Strategy pattern is extensible
class CustomGreenMaterial : public Material {
public:
    Colour shade(const HitInfo& /*hitInfo*/, const Light& /*light*/) const override {
        return Colour(0.0, 1.0, 0.0);
    }
};

TEST_CASE("Material and FlatShader basic tests", "[material]") {
    Ray dummyRay(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));
    HitInfo dummyHit(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), nullptr);
    Light dummyLight(Vector(0.0, 0.0, -1.0), Colour(1.0, 1.0, 1.0));

    SECTION("FlatShader returns assigned colour from shade()") {
        FlatShader shader(Colour(0.2, 0.4, 0.6));
        REQUIRE(shader.shade(dummyHit, dummyLight) == Colour(0.2, 0.4, 0.6));
        REQUIRE(shader.shade(dummyRay) == Colour(0.2, 0.4, 0.6));
    }

    SECTION("FlatShader polymorphism through Material pointer") {
        std::shared_ptr<Material> mat = std::make_shared<FlatShader>(Colour(1.0, 0.5, 0.0));
        REQUIRE(mat->shade(dummyHit, dummyLight) == Colour(1.0, 0.5, 0.0));
    }
}

TEST_CASE("LambertShader shading technique", "[material][lambert]") {
    SECTION("Direct illumination along surface normal gives full colour") {
        LambertShader shader(Colour(1.0, 0.5, 0.2));
        HitInfo hit(Vector(0.0, 0.0, 4.0), Vector(0.0, 0.0, -1.0), nullptr);
        Light light(Vector(0.0, 0.0, -1.0), Colour(1.0, 1.0, 1.0));

        // Light direction is (0, 0, -1) - (0, 0, 4) = (0, 0, -5) -> normalized (0, 0, -1)
        // dot(N, L) = (-1) * (-1) = 1.0
        Colour result = shader.shade(hit, light);
        REQUIRE_THAT(result.r(), WithinAbs(1.0, tolerance));
        REQUIRE_THAT(result.g(), WithinAbs(0.5, tolerance));
        REQUIRE_THAT(result.b(), WithinAbs(0.2, tolerance));
    }

    SECTION("Angled illumination scales colour by dot product") {
        LambertShader shader(Colour(1.0, 1.0, 1.0));
        // Normal pointing up in Y
        HitInfo hit(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), nullptr);
        // Light at 60 degrees to normal (cos(60 deg) = 0.5)
        // Direction (0, 1, sqrt(3)) has length 2, normalized Y is 0.5
        Light light(Vector(0.0, 1.0, std::sqrt(3.0)), Colour(1.0, 1.0, 1.0));

        Colour result = shader.shade(hit, light);
        REQUIRE_THAT(result.r(), WithinAbs(0.5, tolerance));
        REQUIRE_THAT(result.g(), WithinAbs(0.5, tolerance));
        REQUIRE_THAT(result.b(), WithinAbs(0.5, tolerance));
    }

    SECTION("Light behind surface (dot < 0) is clamped to zero / black") {
        LambertShader shader(Colour(1.0, 1.0, 1.0));
        HitInfo hit(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), nullptr);
        // Light is behind surface normal: at (0, 0, 5)
        Light light(Vector(0.0, 0.0, 5.0), Colour(1.0, 1.0, 1.0));

        Colour result = shader.shade(hit, light);
        REQUIRE(result == Colour(0.0, 0.0, 0.0));
    }

    SECTION("Perpendicular light gives zero / black") {
        LambertShader shader(Colour(0.8, 0.8, 0.8));
        HitInfo hit(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), nullptr);
        Light light(Vector(5.0, 0.0, 0.0), Colour(1.0, 1.0, 1.0));

        Colour result = shader.shade(hit, light);
        REQUIRE(result == Colour(0.0, 0.0, 0.0));
    }

    SECTION("Coloured light modulates surface colour") {
        LambertShader shader(Colour(1.0, 1.0, 1.0));
        HitInfo hit(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), nullptr);
        Light redLight(Vector(0.0, 0.0, -5.0), Colour(1.0, 0.0, 0.0));

        Colour result = shader.shade(hit, redLight);
        REQUIRE(result == Colour(1.0, 0.0, 0.0));
    }
}

TEST_CASE("Sphere accepts and stores Material", "[geometry][sphere][material]") {
    HitInfo dummyHit(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), nullptr);
    Light dummyLight(Vector(0.0, 0.0, -1.0), Colour(1.0, 1.0, 1.0));

    SECTION("Sphere stores Material and returns it through material()") {
        auto flat = std::make_shared<FlatShader>(Colour(0.8, 0.1, 0.2));
        Sphere sphere(Vector(0.0, 0.0, 5.0), 2.0, flat);

        REQUIRE(sphere.material() == flat);
        REQUIRE(sphere.material()->shade(dummyHit, dummyLight) == Colour(0.8, 0.1, 0.2));
    }

    SECTION("trace calls sphere's material's shade function") {
        Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

        // Sphere with CustomGreenMaterial
        auto greenMat = std::make_shared<CustomGreenMaterial>();
        Sphere sphere(Vector(0.0, 0.0, 9.0), 5.0, greenMat);

        Colour result = trace(ray, sphere);
        REQUIRE(result == Colour(0.0, 1.0, 0.0));
    }

    SECTION("Camera render with LambertShader and Light produces shaded pixels") {
        Camera camera(Vector(0.0, 0.0, -1.0), 5.0);
        auto lambert = std::make_shared<LambertShader>(Colour(1.0, 0.0, 0.0));
        Sphere sphere(Vector(0.0, 0.0, 9.0), 5.0, lambert);
        Light light(Vector(0.0, 0.0, -1.0), Colour(1.0, 1.0, 1.0));

        Image img = camera.render(sphere, light, 5, 3);
        // Center pixel hits right at (0, 0, 4) with direct normal -> should be red (1, 0, 0)
        REQUIRE(img.pixel(2, 1) == Colour(1.0, 0.0, 0.0));
        // Miss pixels remain black
        REQUIRE(img.pixel(4, 0) == Colour(0.0, 0.0, 0.0));
    }
}
