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

Ray Camera::rayThroughCenter() const {
    Vector direction(0, 0, 1);
    return Ray(_position, direction);
}

Ray Camera::rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const {
    double pixelSize = _screenWidth / imageWidth;

    double x = ((column + 0.5) - (imageWidth / 2.0)) * pixelSize;
    double y = -((row + 0.5) - (imageHeight / 2.0)) * pixelSize;

    Vector pixelPosition(x, y, 0);
    Vector direction = pixelPosition - _position;

    return Ray(_position, direction);
}

Image Camera::render(const Scene& scene, int width, int height) const {
    Image image(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
    render(image, scene);
    return image;
}

Image Camera::render(const Scene& scene, unsigned int width, unsigned int height) const {
    Image image(width, height);
    render(image, scene);
    return image;
}

void Camera::render(Image& image, const Scene& scene) const {
    int width = static_cast<int>(image.width());
    int height = static_cast<int>(image.height());
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            Ray ray = rayThroughPixel(column, row, width, height);
            image.setPixel(column, row, trace(ray, scene));
        }
    }
}

void Camera::render(Image& image, const Sphere& sphere, const Light& light) {
    for (unsigned int row = 0; row < image.height(); ++row) {
        for (unsigned int column = 0; column < image.width(); ++column) {
            Ray ray = rayThroughPixel(static_cast<int>(column), static_cast<int>(row),
                                      static_cast<int>(image.width()), static_cast<int>(image.height()));
            auto hitInfo = sphere.hit(ray);
            if (hitInfo != nullptr) {
                if (hitInfo->material) {
                    Colour colour = hitInfo->material->shade(*hitInfo, light);
                    image.setPixel(column, row, colour);
                }
            }
        }
    }
}

void Camera::render(Image& image, const Sphere& sphere) {
    Light defaultLight(_position, Colour(1.0, 1.0, 1.0));
    render(image, sphere, defaultLight);
}

void Camera::render(const Sphere& sphere, Image& image) {
    render(image, sphere);
}

void Camera::render(const Sphere& sphere, const Light& light, Image& image) {
    render(image, sphere, light);
}

Image Camera::render(const Sphere& sphere, unsigned int imageWidth, unsigned int imageHeight) {
    Image image(imageWidth, imageHeight);
    render(image, sphere);
    return image;
}

Image Camera::render(const Sphere& sphere, const Light& light, unsigned int imageWidth, unsigned int imageHeight) {
    Image image(imageWidth, imageHeight);
    render(image, sphere, light);
    return image;
}
