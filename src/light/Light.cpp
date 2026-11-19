#include "light/Light.h"

Light::Light()
    : _position(0.0, 0.0, 0.0), _colour(1.0, 1.0, 1.0) {}

Light::Light(const Vector& position, const Colour& colour)
    : _position(position), _colour(colour) {}

Vector Light::position() const {
    return _position;
}

Colour Light::colour() const {
    return _colour;
}
