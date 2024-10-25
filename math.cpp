#include "math.h"
#include <cmath>

// Default constructor
VECTOR2::VECTOR2() : x(0), y(0) {
}

// Parameterized constructor
VECTOR2::VECTOR2(const float x, const float y) : x(x), y(y) {
}

// Addition operator
VECTOR2 VECTOR2::operator+(const VECTOR2 &other) const {
    return VECTOR2(x + other.x, y + other.y);
}

// Subtraction operator
VECTOR2 VECTOR2::operator-(const VECTOR2 &other) const {
    return VECTOR2(x - other.x, y - other.y);
}

// Scalar multiplication
VECTOR2 VECTOR2::operator*(float scalar) const {
    return VECTOR2(x * scalar, y * scalar);
}

// Magnitude of the vector
float VECTOR2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

// Normalize the vector
VECTOR2 VECTOR2::normalize() const {
    float mag = magnitude();
    return VECTOR2(x / mag, y / mag);
}
