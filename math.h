#ifndef MATH_H
#define MATH_H

struct VECTOR2
{
    float x;
    float y;

    // Default constructor
    VECTOR2();

    // Parameterized constructor
    VECTOR2(float x, float y);

    // Addition operator
    VECTOR2 operator+(const VECTOR2& other) const;

    // Subtraction operator
    VECTOR2 operator-(const VECTOR2& other) const;

    // Scalar multiplication
    VECTOR2 operator*(float scalar) const;

    VECTOR2 operator+= (const VECTOR2& other) const;

    // Magnitude of the vector
    float magnitude() const;

    // Normalize the vector
    VECTOR2 normalize() const;
};

#endif // MATH_H