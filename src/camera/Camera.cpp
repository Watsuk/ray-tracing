#include "Camera.h"
#include "ray/Ray.h"

Camera::Camera(const Vector& origin)
    : _origin(origin), _direction(0.0, 0.0, 1.0) {}

Camera::Camera(const Vector& origin, const Vector& direction)
    : _origin(origin), _direction(direction) {}

Vector Camera::origin() const {
    return _origin;
}

Vector Camera::direction() const {
    return _direction;
}

Ray Camera::rayThroughCenter() {
    Vector direction(0, 0, 1);
    return Ray(_origin, direction);
}