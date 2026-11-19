#pragma once

#include "colour/Colour.h"

struct Hit;
using HitInfo = Hit;
using Hinfo = Hit;
class Light;
class Ray;

class Material {
public:
    virtual ~Material() = default;

    virtual Colour shade(const Hit& hit, const Light& light) const = 0;
    virtual Colour shade(const Ray& ray, const Hit& hit, const Light& light) const {
        (void)ray;
        return shade(hit, light);
    }
    virtual Colour shade(const Ray& ray) const {
        (void)ray;
        return Colour(0.0, 0.0, 0.0);
    }
};
