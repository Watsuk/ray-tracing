#include "geometry/Sphere.h"
#include "geometry/Ray.h"
#include "light/Light.h"
#include <cmath>
#include <algorithm>

Sphere::Sphere(const Vector& center, double radius, std::shared_ptr<Material> material)
    : _center(center), _radius(radius), _material(std::move(material)) {}

Sphere::Sphere(const Vector& center, double radius, const Material& material)
    : _center(center), _radius(radius), _material(material.clone()) {}

Sphere::Sphere(const Vector& center, double radius, const Colour& colour)
    : _center(center), _radius(radius), _material(std::make_shared<FlatShader>(colour)) {}

Vector Sphere::center() const {
    return _center;
}

double Sphere::radius() const {
    return _radius;
}

std::shared_ptr<Material> Sphere::material() const {
    return _material;
}

Colour Sphere::colour() const {
    if (_material) {
        Hit hitInfo(_center, Vector(0.0, 0.0, 1.0), _material);
        Light light(_center, Colour(1.0, 1.0, 1.0));
        return _material->shade(hitInfo, light);
    }
    return Colour(0.0, 0.0, 0.0);
}

std::optional<Hit> Sphere::hit(const Ray& ray) const {
    Vector D = ray.direction();
    Vector O = ray.origin();
    Vector C = _center;

    Vector L = O - C;

    double a = D.dot(D);
    double b = 2.0 * D.dot(L);
    double c = L.dot(L) - _radius * _radius;

    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) {
        return std::nullopt;
    }

    double root = std::sqrt(discriminant);
    double t1 = (-b - root) / (2.0 * a);
    double t2 = (-b + root) / (2.0 * a);

    // Ignore t <= 0 and choose the closest one with t > 0
    double t = -1.0;
    if (t1 > 0.0 && t2 > 0.0) {
        t = std::min(t1, t2);
    } else if (t1 > 0.0) {
        t = t1;
    } else if (t2 > 0.0) {
        t = t2;
    } else {
        return std::nullopt;
    }

    Vector hitPoint = ray.at(t);
    Vector normal = (hitPoint - _center).normalize();

    return Hit(t, hitPoint, normal, _material);
}

std::optional<Hit> Sphere::hit(Ray& ray) {
    return hit(static_cast<const Ray&>(ray));
}

bool Sphere::isHitBy(const Ray& ray) const {
    return hit(ray).has_value();
}
