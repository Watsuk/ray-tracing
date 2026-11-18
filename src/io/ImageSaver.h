#pragma once

#include <string>
#include "render/Image.h"

class ImageSaver {
public:
    virtual ~ImageSaver() = default;
    virtual void save(Image& image) = 0;
    virtual void save(Image& image, const std::string& filepath) {
        (void)filepath;
        save(image);
    }
};
