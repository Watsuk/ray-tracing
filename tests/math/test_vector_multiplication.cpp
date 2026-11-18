#include <catch2/catch_test_macros.hpp>
#include "math/Vector.h"

TEST_CASE("Vector scalar multiplication", "[math][vector][multiplication]") {
    SECTION("Multiplies vector by scalar (vector * scalar)") {
        Vector v(2.0, -3.0, 4.0);
        Vector result = v * 2.5;

        REQUIRE(result.x() == 5.0);
        REQUIRE(result.y() == -7.5);
        REQUIRE(result.z() == 10.0);
    }

    SECTION("Multiplies scalar by vector (scalar * vector)") {
        Vector v(2.0, -3.0, 4.0);
        Vector result = 2.5 * v;

        REQUIRE(result.x() == 5.0);
        REQUIRE(result.y() == -7.5);
        REQUIRE(result.z() == 10.0);
    }

    SECTION("Multiplication by zero scalar") {
        Vector v(2.0, 3.0, 4.0);
        Vector result = v * 0.0;

        REQUIRE(result.x() == 0.0);
        REQUIRE(result.y() == 0.0);
        REQUIRE(result.z() == 0.0);
    }
}
