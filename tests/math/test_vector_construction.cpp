#include <catch2/catch_test_macros.hpp>
#include "Vector.h"

TEST_CASE("Vector construction and coordinate getters", "[math][vector][construction]") {
    SECTION("Initializes components with given values and returns them through getters") {
        Vector v(1.5, -2.0, 3.25);

        REQUIRE(v.x() == 1.5);
        REQUIRE(v.y() == -2.0);
        REQUIRE(v.z() == 3.25);
    }

    SECTION("Handles zero values correctly") {
        Vector v(0.0, 0.0, 0.0);

        REQUIRE(v.x() == 0.0);
        REQUIRE(v.y() == 0.0);
        REQUIRE(v.z() == 0.0);
    }
}
