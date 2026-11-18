#include <catch2/catch_test_macros.hpp>
#include "Vector.h"

TEST_CASE("Vector dot product (scalar product)", "[math][vector][dot]") {
    SECTION("Computes the scalar product of two vectors") {
        Vector v1(1.0, 2.0, 3.0);
        Vector v2(4.0, 5.0, 6.0);

        REQUIRE(v1.dot(v2) == 32.0);
    }

    SECTION("Dot product of orthogonal vectors is zero") {
        Vector v1(1.0, 0.0, 0.0);
        Vector v2(0.0, 1.0, 0.0);

        REQUIRE(v1.dot(v2) == 0.0);
    }

    SECTION("Dot product is commutative") {
        Vector v1(1.0, 2.0, 3.0);
        Vector v2(4.0, 5.0, 6.0);

        REQUIRE(v1.dot(v2) == v2.dot(v1));
    }

    SECTION("Dot product with zero vector is zero") {
        Vector v(2.0, 3.0, 4.0);
        Vector zero(0.0, 0.0, 0.0);

        REQUIRE(v.dot(zero) == 0.0);
    }

    SECTION("Self dot product equals squared magnitude") {
        Vector v(2.0, 3.0, 4.0);

        REQUIRE(v.dot(v) == 29.0);
    }

    SECTION("Correctly handles negative components") {
        Vector v1(1.0, -2.0, 3.0);
        Vector v2(-4.0, 5.0, -6.0);

        REQUIRE(v1.dot(v2) == -32.0);
    }
}
