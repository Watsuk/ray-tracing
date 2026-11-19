#include "render/trace.h"
#include "material/Material.h"

Colour trace(const Ray& ray, const Sphere& sphere) {
    if (sphere.isHitBy(ray)) {
        if (sphere.material()) {
            return sphere.material()->shade(ray);
        }
        return sphere.colour();
    }
    return Colour(0.0, 0.0, 0.0);
}
