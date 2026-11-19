#pragma once

#include "math/Vector.h"
#include "geometry/Ray.h"
#include "geometry/Sphere.h"
#include "render/Image.h"
#include "light/Light.h"
#include "scene/scene.h"

class Camera {
private:
    Vector _position;
    double _screenWidth;

public:
    Camera(const Vector& position, double screenWidth = 5.0);

    const Vector& position() const;
    double screenWidth() const;

    Ray rayThroughCenter() const;

    Ray rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const;

    Image render(const Scene& scene, int width, int height) const;
    Image render(const Scene& scene, unsigned int width, unsigned int height) const;
    void render(Image& image, const Scene& scene) const;

    Image render(const Sphere& sphere, unsigned int imageWidth, unsigned int imageHeight);
    Image render(const Sphere& sphere, const Light& light, unsigned int imageWidth, unsigned int imageHeight);
    void render(Image& image, const Sphere& sphere);
    void render(Image& image, const Sphere& sphere, const Light& light);
    void render(const Sphere& sphere, Image& image);
    void render(const Sphere& sphere, const Light& light, Image& image);
};
