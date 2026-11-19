#pragma once

#include "material/Material.h"
#include "colour/Colour.h"

struct Hit;
using HitInfo = Hit;
using Hinfo = Hit;
class Light;
class Ray;

class FlatShader : public Material {
private:
    Colour _colour;

public:
    using Material::shade;

    FlatShader();
    explicit FlatShader(const Colour& colour);

    Colour shade(const Hit& hit, const Light& light) const override;
    Colour shade(const Ray& ray, const Hit& hit, const Light& light) const override;
    Colour shade(const Ray& ray) const override;
    Colour shade() const;

    const Colour& colour() const;
    void setColour(const Colour& colour);

    std::shared_ptr<Material> clone() const override {
        return std::make_shared<FlatShader>(*this);
    }
};
