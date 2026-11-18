#include <iostream>
#include "raytracer/app.hpp"
#include "math/Vector.h"
#include "geometry/Ray.h"
#include "geometry/Sphere.h"
#include "render/Camera.h"
#include "colour/Colour.h"

int main() {
    std::cout << raytracer::get_greeting() << "\n";

    Camera camera(Vector(0, 0, -1));
    Ray ray = camera.rayThroughCenter();
    Sphere sphere(Vector(0, 0, 9), 5);

    Colour colour(0, 0, 0);

    bool hit = sphere.hit(ray);
    if (hit) {
        colour = Colour(1, 0, 0);
    }

    std::cout << "Colour: (" <<colour.r() << ", " <<colour.g() << ", " <<colour.b() << ")/n";

    return 0;
}
