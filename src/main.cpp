#include <iostream>
#include "raytracer/app.hpp"
#include "math/Vector.h"
#include "geometry/Ray.h"
#include "geometry/Sphere.h"
#include "render/Camera.h"
#include "colour/Colour.h"
#include "render/trace.h"

int main() {
    std::cout << raytracer::get_greeting() << "\n";

    Camera camera(Vector(0, 0, -1));
    Ray ray = camera.rayThroughCenter();
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    Colour pixel = trace(ray, sphere);

    std::cout << "Colour: (" << pixel.r() << ", " << pixel.g() << ", " << pixel.b() << ")\n";

    return 0;
}
