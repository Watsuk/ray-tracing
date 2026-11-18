#pragma once

#include "math/Vector.h"
#include "ray/Ray.h"

class Camera {
private:
    Vector _origin;
    Vector _direction;

public:
    Camera(const Vector& origin);
    Camera(const Vector& origin, const Vector& direction);

    Vector origin() const;
    Vector direction() const;

    Ray rayThroughCenter();
};
