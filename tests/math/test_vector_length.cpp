#include <catch2/catch_test_macros.hpp>
#include "math/Vector.h"

TEST_CASE("Vector length (magnitude)", "[math][vector][length]") {
    SECTION("Length of zero vector is zero") {
        Vector v(0.0, 0.0, 0.0);

        REQUIRE(v.length() == 0.0);
    }

    SECTION("Length of unit axis vectors is one") {
        Vector vx(1.0, 0.0, 0.0);
        Vector vy(0.0, -1.0, 0.0);
        Vector vz(0.0, 0.0, 1.0);

        REQUIRE(vx.length() == 1.0);
        REQUIRE(vy.length() == 1.0);
        REQUIRE(vz.length() == 1.0);
    }

    SECTION("Computes length accurately for 3D vector") {
        Vector v(2.0, 3.0, 6.0);

        REQUIRE(v.length() == 7.0);
    }

    SECTION("Length is always positive even with negative components") {
        Vector v(-2.0, -3.0, -6.0);

        REQUIRE(v.length() == 7.0);
    }
}
