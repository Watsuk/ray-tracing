#include <iostream>
#include "raytracer/app.hpp"
#include "math/Vector.h"
#include "ray/Ray.h"
#include "geometry/Sphere.h"

int main() {
    std::cout << raytracer::get_greeting() << "\n";

    Ray ray (Vector(0, 0, -1), Vector(0, 0, 1));

    Sphere sphere(Vector(0, 0, 9), 5);

    bool hit = sphere.hit(ray);
    if (hit) {
        std::cout << "Ray hit the sphere";
    } else {
        std::cout << "Ray missed the sphere";
    }

    return 0;
}
