#include "material/FlatShader.h"

FlatShader::FlatShader()
    : _colour(1.0, 0.0, 0.0) {}

FlatShader::FlatShader(const Colour& colour)
    : _colour(colour) {}

Colour FlatShader::shade(const HitInfo& /*hitInfo*/, const Light& /*light*/) const {
    return _colour;
}

Colour FlatShader::shade(const Ray& /*ray*/, const HitInfo& /*hitInfo*/, const Light& /*light*/) const {
    return _colour;
}

Colour FlatShader::shade(const Ray& /*ray*/) const {
    return _colour;
}

Colour FlatShader::shade() const {
    return _colour;
}

const Colour& FlatShader::colour() const {
    return _colour;
}

void FlatShader::setColour(const Colour& colour) {
    _colour = colour;
}
