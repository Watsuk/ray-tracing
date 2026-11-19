#include "material/LambertShader.h"
#include "geometry/HitInfo.h"
#include "light/Light.h"
#include <algorithm>

LambertShader::LambertShader()
    : _colour(1.0, 1.0, 1.0) {}

LambertShader::LambertShader(const Colour& colour)
    : _colour(colour) {}

Colour LambertShader::shade(const HitInfo& hitInfo, const Light& light) const {
    Vector lightDirection = (light.position() - hitInfo.point).normalize();
    double dot = hitInfo.normal.dot(lightDirection);
    if (dot < 0.0) {
        dot = 0.0;
    }
    return Colour(_colour.r() * light.colour().r() * dot,
                  _colour.g() * light.colour().g() * dot,
                  _colour.b() * light.colour().b() * dot);
}

Colour LambertShader::shade(const Ray& /*ray*/, const HitInfo& hitInfo, const Light& light) const {
    return shade(hitInfo, light);
}

const Colour& LambertShader::colour() const {
    return _colour;
}

void LambertShader::setColour(const Colour& colour) {
    _colour = colour;
}
