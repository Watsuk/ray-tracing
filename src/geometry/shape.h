#pragma once

#include <optional>
#include "geometry/Ray.h"
#include "geometry/Hit.h"

// Every shape gives its nearest hit in front of the ray's origin, with t > 0 and a unit normal, or nothing.
class Shape {
public:
    virtual ~Shape() = default;

    virtual std::optional<Hit> hit(const Ray& ray) const = 0;
};
