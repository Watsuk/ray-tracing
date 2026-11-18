#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <filesystem>
#include "io/ImageSaver.h"
#include "io/PngSaver.h"
#include "render/Image.h"
#include "lodepng.h"

TEST_CASE("ImageSaver and PngSaver interface", "[io][saver]") {
    SECTION("PngSaver implements ImageSaver interface") {
        std::unique_ptr<ImageSaver> saver = std::make_unique<PngSaver>();
        REQUIRE(saver != nullptr);

        Image image(2, 2);
        saver->save(image);
        std::filesystem::remove("output.png");
    }

    SECTION("PngSaver constructor and filepath getters") {
        PngSaver defaultSaver;
        REQUIRE(defaultSaver.filepath() == "output.png");

        PngSaver customSaver("custom.png");
        REQUIRE(customSaver.filepath() == "custom.png");
    }
}

TEST_CASE("PngSaver saves valid PNG with correct pixels", "[io][png]") {
    const std::string testFile = "test_saver_output.png";
    std::filesystem::remove(testFile);

    unsigned int width = 3;
    unsigned int height = 2;
    Image image(width, height);

    // Set pixel (1, 0) to red (1, 0, 0)
    image.setPixel(1, 0, Colour(1.0, 0.0, 0.0));
    // Set pixel (2, 1) to green (0, 1, 0)
    image.setPixel(2, 1, Colour(0.0, 1.0, 0.0));

    PngSaver saver;
    saver.save(image, testFile);

    REQUIRE(std::filesystem::exists(testFile));

    // Decode and verify with lodepng
    std::vector<unsigned char> decoded;
    unsigned int decodedWidth = 0;
    unsigned int decodedHeight = 0;
    unsigned int error = lodepng::decode(decoded, decodedWidth, decodedHeight, testFile);

    REQUIRE(error == 0);
    REQUIRE(decodedWidth == width);
    REQUIRE(decodedHeight == height);

    // Pixel at (1, 0): index = (0 * 3 + 1) * 4 = 4
    REQUIRE(decoded[4] == 255); // R
    REQUIRE(decoded[5] == 0);   // G
    REQUIRE(decoded[6] == 0);   // B
    REQUIRE(decoded[7] == 255); // A

    // Pixel at (2, 1): index = (1 * 3 + 2) * 4 = 20
    REQUIRE(decoded[20] == 0);   // R
    REQUIRE(decoded[21] == 255); // G
    REQUIRE(decoded[22] == 0);   // B
    REQUIRE(decoded[23] == 255); // A

    // Pixel at (0, 0): index = 0 (should be black)
    REQUIRE(decoded[0] == 0);
    REQUIRE(decoded[1] == 0);
    REQUIRE(decoded[2] == 0);
    REQUIRE(decoded[3] == 255);

    // Clean up
    std::filesystem::remove(testFile);
}
