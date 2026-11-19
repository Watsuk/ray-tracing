#pragma once

#include <memory>
#include "colour/Colour.h"

struct Hit;
using HitInfo = Hit;
using Hinfo = Hit;
class Light;
class Ray;

class Material {
protected:
    Colour _colour{0.0, 0.0, 0.0};

public:
    Material() = default;
    explicit Material(const Colour& colour) : _colour(colour) {}
    Material(const Material&) = default;
    Material& operator=(const Material&) = default;
    virtual ~Material() = default;

    virtual const Colour& colour() const { return _colour; }

    virtual Colour shade(const Hit& hit, const Light& light) const {
        (void)hit;
        (void)light;
        return _colour;
    }
    virtual Colour shade(const Ray& ray, const Hit& hit, const Light& light) const {
        (void)ray;
        return shade(hit, light);
    }
    virtual Colour shade(const Ray& ray) const {
        (void)ray;
        return _colour;
    }

    virtual std::shared_ptr<Material> clone() const {
        return std::make_shared<Material>(*this);
    }
};
