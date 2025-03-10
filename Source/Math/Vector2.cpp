#include "Vector2.h"
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
VECTOR2 VECTOR2::operator*(const float scalar) const {
    return VECTOR2(x * scalar, y * scalar);
}

VECTOR2 VECTOR2::operator/(float scalar) const {
    return VECTOR2(this->x / scalar, this->y / scalar);
}

VECTOR2 VECTOR2::operator=(const VECTOR2 &other) {
    this->x = other.x;
    this->y = other.y;
    return *this;
}

VECTOR2 VECTOR2::operator-=(const VECTOR2 &other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

VECTOR2 VECTOR2::operator+=(const VECTOR2 &other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

VECTOR2 VECTOR2::operator/=(float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

VECTOR2 VECTOR2::operator*=(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

float VECTOR2::dot(const VECTOR2 &other) const {
    return x * other.x + y * other.y;
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

VECTOR2 VECTOR2::rotate(float angle) const {
    float radians = angle * M_PI / 180.0f;
    float cosTheta = std::cos(radians);
    float sinTheta = std::sin(radians);
    float newX = x * cosTheta - y * sinTheta;
    float newY = x * sinTheta + y * cosTheta;
    return VECTOR2(newX, newY);
}
