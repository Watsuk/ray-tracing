#pragma once

#include "material/Material.h"
#include "colour/Colour.h"

class Ray;

class FlatShader : public Material {
private:
    Colour _colour;

public:
    FlatShader();
    explicit FlatShader(const Colour& colour);

    Colour shade(const Ray& ray) const override;

    const Colour& colour() const;
    void setColour(const Colour& colour);
};
