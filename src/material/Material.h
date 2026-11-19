#pragma once

#include "colour/Colour.h"

class Ray;

class Material {
public:
    virtual ~Material() = default;

    virtual Colour shade(const Ray& ray) const = 0;
};
