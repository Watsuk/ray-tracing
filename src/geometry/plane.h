#pragma once

#include <memory>
#include <optional>
#include "math/Vector.h"
#include "geometry/Ray.h"
#include "geometry/shape.h"
#include "geometry/Hit.h"
#include "material/Material.h"

class Plane : public Shape {
private:
    Vector _point;
    Vector _normal;
    std::shared_ptr<Material> _material;

public:
    Plane(const Vector& point, const Vector& normal, const Material& material);

    std::optional<Hit> hit(const Ray& ray) const override;
};
