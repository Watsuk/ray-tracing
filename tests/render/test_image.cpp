#include <catch2/catch_test_macros.hpp>
#include "render/Image.h"
#include "colour/Colour.h"

TEST_CASE("Image construction and dimensions", "[render][image]") {
    Image image(10, 20);
    REQUIRE(image.width() == 10);
    REQUIRE(image.height() == 20);
}

TEST_CASE("Image setPixel sets specific pixel and leaves other pixels black", "[render][image]") {
    SECTION("setPixel(3, 4) sets pixel at column 3, row 4 while other pixels are black") {
        Image image(5, 6);
        Colour red(1.0, 0.0, 0.0);
        Colour black(0.0, 0.0, 0.0);

        image.setPixel(3, 4, red);
        REQUIRE(image.pixel(3, 4) == red);

        for (unsigned int y = 0; y < image.height(); ++y) {
            for (unsigned int x = 0; x < image.width(); ++x) {
                if (x == 3 && y == 4) {
                    REQUIRE(image.pixel(x, y) == red);
                } else {
                    REQUIRE(image.pixel(x, y) == black);
                }
            }
        }
    }

    SECTION("setPixel(3, 2) sets pixel at column 3, row 2 while other pixels are black") {
        Image image(5, 5);
        Colour red(1.0, 0.0, 0.0);
        Colour black(0.0, 0.0, 0.0);

        image.setPixel(3, 2, red);
        REQUIRE(image.pixel(3, 2) == red);

        for (unsigned int y = 0; y < image.height(); ++y) {
            for (unsigned int x = 0; x < image.width(); ++x) {
                if (x == 3 && y == 2) {
                    REQUIRE(image.pixel(x, y) == red);
                } else {
                    REQUIRE(image.pixel(x, y) == black);
                }
            }
        }
    }
}
