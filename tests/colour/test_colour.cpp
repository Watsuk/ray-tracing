#include <catch2/catch_test_macros.hpp>
#include "colour/Colour.h"

TEST_CASE("Colour channels and equality", "[colour]") {
    Colour c(1.0, 0.5, 0.0);
    REQUIRE(c.r() == 1.0);
    REQUIRE(c.g() == 0.5);
    REQUIRE(c.b() == 0.0);
    REQUIRE(c == Colour(1.0, 0.5, 0.0));
}

TEST_CASE("Colour arithmetic operations", "[colour]") {
    SECTION("Scalar multiplication") {
        Colour c(0.4, 0.6, 0.8);
        Colour result = c * 0.5;
        REQUIRE(result == Colour(0.2, 0.3, 0.4));

        Colour friendResult = 0.5 * c;
        REQUIRE(friendResult == Colour(0.2, 0.3, 0.4));
    }

    SECTION("Colour component-wise multiplication") {
        Colour c1(1.0, 0.5, 0.2);
        Colour c2(0.5, 0.5, 0.0);
        Colour result = c1 * c2;
        REQUIRE(result == Colour(0.5, 0.25, 0.0));
    }
}
