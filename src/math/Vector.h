#pragma once

class Vector {
private:
    double _x;
    double _y;
    double _z;

public:
    // Parameterized constructor: initializes components with given values
    Vector(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    // Dot product (scalar product)
    double dot(const Vector& other) const;

    // Magnitude of the vector
    double length() const;

    // Operator overloads
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;

    // Friend function to allow scalar * vector (e.g. 2.0 * v)
    friend Vector operator*(double scalar, const Vector& vector);
};
