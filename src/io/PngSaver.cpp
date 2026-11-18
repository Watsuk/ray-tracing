#include "io/PngSaver.h"
#include "lodepng.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <iostream>

PngSaver::PngSaver()
    : _filepath("output.png") {}

PngSaver::PngSaver(const std::string& filepath)
    : _filepath(filepath) {}

const std::string& PngSaver::filepath() const {
    return _filepath;
}

void PngSaver::setFilepath(const std::string& filepath) {
    _filepath = filepath;
}

void PngSaver::save(Image& image) {
    save(image, _filepath);
}

void PngSaver::save(Image& image, const std::string& filepath) {
    unsigned int width = image.width();
    unsigned int height = image.height();

    std::vector<unsigned char> raw_pixels;
    raw_pixels.reserve(static_cast<size_t>(width) * height * 4);

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            Colour c = image.pixel(x, y);

            unsigned char r = static_cast<unsigned char>(std::clamp(std::round(c.r() * 255.0), 0.0, 255.0));
            unsigned char g = static_cast<unsigned char>(std::clamp(std::round(c.g() * 255.0), 0.0, 255.0));
            unsigned char b = static_cast<unsigned char>(std::clamp(std::round(c.b() * 255.0), 0.0, 255.0));
            unsigned char a = 255;

            raw_pixels.push_back(r);
            raw_pixels.push_back(g);
            raw_pixels.push_back(b);
            raw_pixels.push_back(a);
        }
    }

    unsigned int error = lodepng::encode(filepath, raw_pixels, width, height, LCT_RGBA, 8);
    if (error) {
        std::cerr << "LodePNG error " << error << ": " << lodepng_error_text(error) << "\n";
    }
}
