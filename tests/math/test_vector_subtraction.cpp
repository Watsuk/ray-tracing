#include <catch2/catch_test_macros.hpp>
#include "Vector.h"

TEST_CASE("Vector subtraction", "[math][vector][subtraction]") {
    SECTION("Subtracts two vectors component-wise") {
        Vector v1(5.0, 7.0, 9.0);
        Vector v2(1.0, 2.0, 3.0);
        Vector result = v1 - v2;

        REQUIRE(result.x() == 4.0);
        REQUIRE(result.y() == 5.0);
        REQUIRE(result.z() == 6.0);
    }

    SECTION("Self-subtraction yields zero components") {
        Vector v(3.0, 4.0, 5.0);
        Vector result = v - v;

        REQUIRE(result.x() == 0.0);
        REQUIRE(result.y() == 0.0);
        REQUIRE(result.z() == 0.0);
    }
}
