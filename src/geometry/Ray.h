#pragma once

#include "math/Vector.h"

class Ray {
private:
    Vector _origin;
    Vector _direction;

public:
    Ray(const Vector& origin, const Vector& direction);

    Vector origin() const;
    Vector direction() const;

    // Calculates the point along the ray at position t: origin + direction * t
    Vector at(double t) const;
};
