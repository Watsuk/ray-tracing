#pragma once

#include <vector>
#include <memory>
#include <optional>
#include "math/Vector.h"
#include "geometry/shape.h"
#include "geometry/Hit.h"
#include "geometry/Ray.h"

class Scene {
private:
    Vector _toLight;
    std::vector<std::unique_ptr<Shape>> _shapes;

public:
    explicit Scene(const Vector& toLight);

    const Vector& toLight() const;
    void add(std::unique_ptr<Shape> shape);
    std::optional<Hit> nearestHit(const Ray& ray) const;
};
