#include "render/trace.h"
#include "material/Material.h"
#include "geometry/HitInfo.h"
#include "scene/scene.h"

Colour trace(const Ray& ray, const Scene& scene) {
    std::optional<Hit> hit = scene.nearestHit(ray);
    if (!hit) {
        return Colour(0, 0, 0);
    }
    return hit->material.shade(hit->normal, scene.toLight());
}

Colour trace(const Ray& ray, const Sphere& sphere, const Light& light) {
    auto hitInfo = sphere.hit(ray);
    if (hitInfo != nullptr) {
        if (hitInfo->material) {
            return hitInfo->material->shade(*hitInfo, light);
        }
        return sphere.colour();
    }
    return Colour(0.0, 0.0, 0.0);
}

Colour trace(const Ray& ray, const Sphere& sphere) {
    Light defaultLight(Vector(0.0, 0.0, -1.0), Colour(1.0, 1.0, 1.0));
    return trace(ray, sphere, defaultLight);
}
