#include "render/Camera.h"
#include "geometry/Ray.h"

Camera::Camera(const Vector& eye, const Vector& screenCentre)
    : _eye(eye), _screenCentre(screenCentre) {}

Camera::Camera(const Vector& eye)
    : _eye(eye), _screenCentre(0.0, 0.0, 0.0) {}

Vector Camera::eye() const {
    return _eye;
}

Vector Camera::screenCentre() const {
    return _screenCentre;
}

Vector Camera::origin() const {
    return _eye;
}

Vector Camera::direction() const {
    return _screenCentre - _eye;
}

Ray Camera::ray() const {
    return Ray(_eye, _screenCentre - _eye);
}

Ray Camera::rayThroughCenter() const {
    return ray();
}
