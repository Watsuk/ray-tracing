#pragma once

#include <string>

namespace raytracer {

/**
 * @brief Returns the welcome / greeting message for the raytracer CLI.
 */
std::string get_greeting();

/**
 * @brief Represents a 2D canvas resolution (width x height).
 *
 * Provided as a concrete domain example with unit-testable methods for TDD.
 */
struct Resolution {
    int width{0};
    int height{0};

    [[nodiscard]] constexpr int total_pixels() const noexcept {
        return width * height;
    }

    [[nodiscard]] constexpr double aspect_ratio() const noexcept {
        if (height <= 0) {
            return 0.0;
        }
        return static_cast<double>(width) / static_cast<double>(height);
    }
};

} // namespace raytracer
