#pragma once

#include <string>
#include "io/ImageSaver.h"

class PngSaver : public ImageSaver {
private:
    std::string _filepath;

public:
    PngSaver();
    explicit PngSaver(const std::string& filepath);

    using ImageSaver::save;
    void save(Image& image) override;
    void save(Image& image, const std::string& filepath) override;

    const std::string& filepath() const;
    void setFilepath(const std::string& filepath);
};
