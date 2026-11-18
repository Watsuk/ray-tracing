#include <catch2/catch_test_macros.hpp>
#include "colour/Colour.h"

TEST_CASE("Colour construction and getters", "[colour][construction]") {
    SECTION("Initializes color channels with given values and returns them through getters") {
        Colour c(0.2, 0.5, 0.8);

        REQUIRE(c.r() == 0.2);
        REQUIRE(c.g() == 0.5);
        REQUIRE(c.b() == 0.8);
    }

    SECTION("Handles black and white channel extremes") {
        Colour black(0.0, 0.0, 0.0);
        REQUIRE(black.r() == 0.0);
        REQUIRE(black.g() == 0.0);
        REQUIRE(black.b() == 0.0);

        Colour white(1.0, 1.0, 1.0);
        REQUIRE(white.r() == 1.0);
        REQUIRE(white.g() == 1.0);
        REQUIRE(white.b() == 1.0);
    }
}
