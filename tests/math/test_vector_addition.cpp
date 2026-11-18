#include <catch2/catch_test_macros.hpp>
#include "Vector.h"

TEST_CASE("Vector addition", "[math][vector][addition]") {
    SECTION("Adds two vectors component-wise") {
        Vector v1(1.0, 2.0, 3.0);
        Vector v2(4.0, 5.0, 6.0);
        Vector result = v1 + v2;

        REQUIRE(result.x() == 5.0);
        REQUIRE(result.y() == 7.0);
        REQUIRE(result.z() == 9.0);
    }

    SECTION("Addition with negative components") {
        Vector v1(1.0, -2.0, 3.0);
        Vector v2(-4.0, 5.0, -6.0);
        Vector result = v1 + v2;

        REQUIRE(result.x() == -3.0);
        REQUIRE(result.y() == 3.0);
        REQUIRE(result.z() == -3.0);
    }
}
