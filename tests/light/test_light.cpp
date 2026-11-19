#include <catch2/catch_test_macros.hpp>
#include "light/Light.h"
#include "test_helpers.h"

TEST_CASE("Light construction and getters", "[light]") {
    SECTION("Constructs with position and colour, getters return them") {
        Vector pos(10.0, 20.0, -5.0);
        Colour col(1.0, 0.9, 0.8);
        Light light(pos, col);

        requireVectorsEqual(light.position(), pos);
        REQUIRE(light.colour() == col);

        // Also verify getPosition and getColour aliases
        requireVectorsEqual(light.getPosition(), pos);
        REQUIRE(light.getColour() == col);
    }

    SECTION("Default constructor creates light at origin with white colour") {
        Light defaultLight;

        requireVectorsEqual(defaultLight.position(), Vector(0.0, 0.0, 0.0));
        REQUIRE(defaultLight.colour() == Colour(1.0, 1.0, 1.0));
    }
}
