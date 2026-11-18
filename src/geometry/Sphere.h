#pragma once

#include "math/Vector.h"
#include "geometry/Ray.h"
#include "colour/Colour.h"

class Sphere {
private:
    Vector _center;
    double _radius;
    Colour _colour;

public:
    Sphere(const Vector& center, double radius, const Colour& colour = Colour(1.0, 0.0, 0.0));

    Vector center() const;
    double radius() const;
    Colour colour() const;

    bool isHitBy(const Ray& ray) const;
    bool hit(Ray& ray);
};
