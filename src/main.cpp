#include <iostream>
#include "raytracer/app.hpp"

int main() {
    std::cout << raytracer::get_greeting() << "\n";

    raytracer::Resolution preview{1280, 720};
    std::cout << "Bootstrap demo: Canvas initialized at " 
              << preview.width << "x" << preview.height << " ("
              << preview.total_pixels() << " pixels, aspect ratio: "
              << preview.aspect_ratio() << ")\n";

    return 0;
}
