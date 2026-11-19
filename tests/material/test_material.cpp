#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "material/Material.h"
#include "material/FlatShader.h"
#include "geometry/Sphere.h"
#include "geometry/Ray.h"
#include "render/trace.h"

// Custom test material to prove the Strategy pattern is extensible
class CustomGreenMaterial : public Material {
public:
    Colour shade(const Ray& /*ray*/) const override {
        return Colour(0.0, 1.0, 0.0);
    }
};

TEST_CASE("Material and FlatShader basic tests", "[material]") {
    Ray dummyRay(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    SECTION("FlatShader returns assigned colour from shade()") {
        FlatShader shader(Colour(0.2, 0.4, 0.6));
        REQUIRE(shader.shade(dummyRay) == Colour(0.2, 0.4, 0.6));
    }

    SECTION("FlatShader polymorphism through Material pointer") {
        std::shared_ptr<Material> mat = std::make_shared<FlatShader>(Colour(1.0, 0.5, 0.0));
        REQUIRE(mat->shade(dummyRay) == Colour(1.0, 0.5, 0.0));
    }
}

TEST_CASE("Sphere accepts and stores Material", "[geometry][sphere][material]") {
    Ray dummyRay(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    SECTION("Sphere stores Material and returns it through material()") {
        auto flat = std::make_shared<FlatShader>(Colour(0.8, 0.1, 0.2));
        Sphere sphere(Vector(0.0, 0.0, 5.0), 2.0, flat);

        REQUIRE(sphere.material() == flat);
        REQUIRE(sphere.material()->shade(dummyRay) == Colour(0.8, 0.1, 0.2));
    }

    SECTION("trace calls sphere's material's shade function") {
        Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

        // Sphere with CustomGreenMaterial
        auto greenMat = std::make_shared<CustomGreenMaterial>();
        Sphere sphere(Vector(0.0, 0.0, 9.0), 5.0, greenMat);

        Colour result = trace(ray, sphere);
        REQUIRE(result == Colour(0.0, 1.0, 0.0));
    }
}
