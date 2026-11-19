#pragma once

#include "material/Material.h"
#include "colour/Colour.h"

struct Hit;
using HitInfo = Hit;
using Hinfo = Hit;
class Light;
class Ray;

class LambertShader : public Material {
private:
    Colour _colour;

public:
    LambertShader();
    explicit LambertShader(const Colour& colour);

    Colour shade(const Hit& hit, const Light& light) const override;
    Colour shade(const Ray& ray, const Hit& hit, const Light& light) const override;

    const Colour& colour() const;
    void setColour(const Colour& colour);
};
