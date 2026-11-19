#include "colour/Colour.h"

Colour::Colour(double r, double g, double b)
    : _r(r), _g(g), _b(b) {}

double Colour::r() const {
    return _r;
}

double Colour::g() const {
    return _g;
}

double Colour::b() const {
    return _b;
}

Colour Colour::operator*(double scalar) const {
    return Colour(_r * scalar, _g * scalar, _b * scalar);
}

Colour Colour::operator*(const Colour& other) const {
    return Colour(_r * other._r, _g * other._g, _b * other._b);
}

Colour operator*(double scalar, const Colour& c) {
    return c * scalar;
}
