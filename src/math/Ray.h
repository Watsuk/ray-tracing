#pragma once

#include "Vector.h"

class Ray {
private:
    Vector _origin;
    Vector _direction;

public:
    Ray(const Vector& origin, const Vector& direction);

    Vector origin() const;
    Vector direction() const;
};
