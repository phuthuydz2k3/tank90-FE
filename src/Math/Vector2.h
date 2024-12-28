#ifndef MATH_H
#define MATH_H

struct VECTOR2 {
    float x;
    float y;

    // Default constructor
    VECTOR2();

    // Parameterized constructor
    VECTOR2(float x, float y);

    VECTOR2 operator+(const VECTOR2 &other) const;

    VECTOR2 operator-(const VECTOR2 &other) const;

    VECTOR2 operator*(float scalar) const;

    VECTOR2 operator/(float scalar) const;

    VECTOR2 operator=(const VECTOR2 &other);

    VECTOR2 operator-=(const VECTOR2 &other);

    VECTOR2 operator+=(const VECTOR2 &other);

    VECTOR2 operator/=(float scalar);

    VECTOR2 operator *=(float scalar);

    float dot(const VECTOR2 &other) const;

    float magnitude() const;

    VECTOR2 normalize() const;
    VECTOR2 rotate(float angle) const;
};

#endif // MATH_H
