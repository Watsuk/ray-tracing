#include <catch2/catch_test_macros.hpp>
#include "colour/Colour.h"

TEST_CASE("Colour channels and equality", "[colour]") {
    Colour c(1.0, 0.5, 0.0);
    REQUIRE(c.r() == 1.0);
    REQUIRE(c.g() == 0.5);
    REQUIRE(c.b() == 0.0);
    REQUIRE(c == Colour(1.0, 0.5, 0.0));
}
