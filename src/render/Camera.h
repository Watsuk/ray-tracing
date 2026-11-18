#pragma once

#include "math/Vector.h"
#include "geometry/Ray.h"
#include "geometry/Sphere.h"
#include "render/Image.h"

class Camera {
private:
    Vector _position;
    double _screenWidth;

public:
    Camera(const Vector& position, double screenWidth = 5.0);

    const Vector& position() const;
    double screenWidth() const;

    Ray rayThroughCenter();

    Ray rayThroughPixel(int column, int row, int imageWidth, int imageHeight);

    Image render(const Sphere& sphere, unsigned int imageWidth, unsigned int imageHeight);
    void render(Image& image, const Sphere& sphere);
    void render(const Sphere& sphere, Image& image);
};
