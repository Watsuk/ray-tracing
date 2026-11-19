#include <iostream>
#include "raytracer/app.hpp"
#include "math/Vector.h"
#include "geometry/Ray.h"
#include "geometry/Sphere.h"
#include "render/Camera.h"
#include "colour/Colour.h"
#include "render/trace.h"
#include "render/Image.h"
#include "io/PngSaver.h"

#include "material/LambertShader.h"
#include "light/Light.h"

int main() {
    std::cout << raytracer::get_greeting() << "\n";

    Camera camera(Vector(0, 0, -1), 5.0);
    auto lambert = std::make_shared<LambertShader>(Colour(0.2, 0.7, 0.3));
    Sphere sphere(Vector(0, 0, 9), 7.0, lambert);
    Light light(Vector(5, 5, -3), Colour(1.0, 1.0, 1.0));

    const unsigned int width = 800;
    const unsigned int height = 800;

    Image image = camera.render(sphere, light, width, height);

    PngSaver saver("output.png");
    saver.save(image);

    std::cout << "Rendered and saved " << width << "x" << height << " image to output.png\n";

    return 0;
}
