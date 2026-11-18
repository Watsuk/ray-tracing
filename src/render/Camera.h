#pragma once

#include "math/Vector.h"
#include "geometry/Ray.h"

class Camera {
private:
    Vector _eye;
    Vector _screenCentre;

public:
    Camera(const Vector& eye, const Vector& screenCentre);
    Camera(const Vector& eye);

    Vector eye() const;
    Vector screenCentre() const;
    Vector origin() const;
    Vector direction() const;

    Ray ray() const;
    Ray rayThroughCenter() const;
};
