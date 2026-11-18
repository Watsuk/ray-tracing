#include "render/Camera.h"
#include "geometry/Ray.h"
#include "geometry/Sphere.h"
#include "render/Image.h"
#include "render/trace.h"

Camera::Camera(const Vector& position, double screenWidth)
    : _position(position), _screenWidth(screenWidth) {}

const Vector& Camera::position() const {
    return _position;
}

double Camera::screenWidth() const {
    return _screenWidth;
}

Ray Camera::rayThroughCenter() {
    Vector direction(0, 0, 1);
    return Ray(_position, direction);
}

Ray Camera::rayThroughPixel(int column, int row, int imageWidth, int imageHeight) {
    double pixelSize = _screenWidth / imageWidth;

    double x = ((column + 0.5) - (imageWidth / 2.0)) * pixelSize;
    double y = -((row + 0.5) - (imageHeight / 2.0)) * pixelSize;

    Vector pixelPosition(x, y, 0);
    Vector direction = pixelPosition - _position;

    return Ray(_position, direction);
}

void Camera::render(Image& image, const Sphere& sphere) {
    for (unsigned int row = 0; row < image.height(); ++row) {
        for (unsigned int column = 0; column < image.width(); ++column) {
            Ray ray = rayThroughPixel(static_cast<int>(column), static_cast<int>(row),
                                      static_cast<int>(image.width()), static_cast<int>(image.height()));
            Colour colour = trace(ray, sphere);
            image.setPixel(column, row, colour);
        }
    }
}

void Camera::render(const Sphere& sphere, Image& image) {
    render(image, sphere);
}

Image Camera::render(const Sphere& sphere, unsigned int imageWidth, unsigned int imageHeight) {
    Image image(imageWidth, imageHeight);
    render(image, sphere);
    return image;
}
