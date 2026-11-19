#pragma once

#include "math/Vector.h"
#include "colour/Colour.h"

class Light {
private:
    Vector _position;
    Colour _colour;

public:
    Light();
    Light(const Vector& position, const Colour& colour);

    Vector position() const;
    Colour colour() const;

    // Alternative getter naming conventions
    Vector getPosition() const { return position(); }
    Colour getColour() const { return colour(); }
};
