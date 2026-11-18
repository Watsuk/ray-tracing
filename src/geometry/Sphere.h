#pragma once

#include "math/Vector.h"
#include "geometry/Ray.h"

class Sphere {
private:
    Vector _center;
    double _radius;

public:
    Sphere(const Vector& center, double radius);

    Vector center() const;
    double radius() const;

    bool hit(Ray& ray);
};
