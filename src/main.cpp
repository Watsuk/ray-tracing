#include <iostream>
#include <memory>
#include "raytracer/app.hpp"
#include "math/Vector.h"
#include "geometry/Ray.h"
#include "geometry/Sphere.h"
#include "geometry/plane.h"
#include "render/Camera.h"
#include "colour/Colour.h"
#include "render/trace.h"
#include "render/Image.h"
#include "io/PngSaver.h"
#include "scene/scene.h"
#include "material/Material.h"

int main() {
    std::cout << raytracer::get_greeting() << "\n";

    Camera camera(Vector(0, 0, -1), 5.0);

    Scene scene(Vector(-1, 1, -1));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, Material(Colour(0, 1, 0))));
    scene.add(std::make_unique<Plane>(Vector(0, -5, 0), Vector(0, 1, 0), Material(Colour(0.8, 0.8, 0.8))));

    const unsigned int width = 800;
    const unsigned int height = 800;

    Image image = camera.render(scene, width, height);

    PngSaver saver("image.png");
    saver.save(image);

    std::cout << "Rendered and saved " << width << "x" << height << " image to image.png\n";

    return 0;
}
