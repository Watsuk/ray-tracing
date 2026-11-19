#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "math/Vector.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("Vector normalize", "[math][vector][normalize]") {
    SECTION("Vector (3, 4, 0) produces normalised vector (3/5, 4/5, 0)") {
        Vector v(3.0, 4.0, 0.0);
        Vector normalized = v.normalize();

        requireVectorsEqual(normalized, Vector(3.0 / 5.0, 4.0 / 5.0, 0.0));
        REQUIRE_THAT(normalized.x(), WithinAbs(3.0 / 5.0, tolerance));
        REQUIRE_THAT(normalized.y(), WithinAbs(4.0 / 5.0, tolerance));
        REQUIRE_THAT(normalized.z(), WithinAbs(0.0, tolerance));
        REQUIRE_THAT(normalized.length(), WithinAbs(1.0, tolerance));
    }

    SECTION("Normalizing unit axis vectors keeps them unchanged") {
        Vector vx(1.0, 0.0, 0.0);
        Vector vy(0.0, -1.0, 0.0);
        Vector vz(0.0, 0.0, 1.0);

        requireVectorsEqual(vx.normalize(), vx);
        requireVectorsEqual(vy.normalize(), vy);
        requireVectorsEqual(vz.normalize(), vz);
    }

    SECTION("Normalizing vector with negative components has length 1") {
        Vector v(0.0, 0.0, -5.0);
        Vector normalized = v.normalize();

        requireVectorsEqual(normalized, Vector(0.0, 0.0, -1.0));
        REQUIRE_THAT(normalized.length(), WithinAbs(1.0, tolerance));
    }

    SECTION("Normalizing 3D vector (2, 3, 6) with length 7") {
        Vector v(2.0, 3.0, 6.0);
        Vector normalized = v.normalize();

        requireVectorsEqual(normalized, Vector(2.0 / 7.0, 3.0 / 7.0, 6.0 / 7.0));
        REQUIRE_THAT(normalized.length(), WithinAbs(1.0, tolerance));
    }


}
