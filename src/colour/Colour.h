#pragma once

#include <iostream>

class Colour {
private:
    double _r;
    double _g;
    double _b;

public:
    Colour(double r, double g, double b);

    double r() const;
    double g() const;
    double b() const;

    Colour operator*(double scalar) const;
    Colour operator*(const Colour& other) const;
    friend Colour operator*(double scalar, const Colour& c);

    bool operator==(const Colour& other) const = default;

    friend std::ostream& operator<<(std::ostream& os, const Colour& c) {
        return os << "(" << c._r << ", " << c._g << ", " << c._b << ")";
    }
};
