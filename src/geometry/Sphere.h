#pragma once

#include <memory>
#include <optional>
#include "math/Vector.h"
#include "geometry/Ray.h"
#include "colour/Colour.h"
#include "material/Material.h"
#include "material/FlatShader.h"
#include "geometry/shape.h"

class Sphere : public Shape {
private:
    Vector _center;
    double _radius;
    std::shared_ptr<Material> _material;

public:
    Sphere(const Vector& center, double radius, std::shared_ptr<Material> material);
    Sphere(const Vector& center, double radius, const Material& material);
    Sphere(const Vector& center, double radius, const Colour& colour = Colour(1.0, 0.0, 0.0));

    Vector center() const;
    double radius() const;
    std::shared_ptr<Material> material() const;
    Colour colour() const;

    bool isHitBy(const Ray& ray) const;
    std::optional<Hit> hit(const Ray& ray) const override;
    std::optional<Hit> hit(Ray& ray);
};
