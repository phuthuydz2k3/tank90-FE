//
// Created by TCT on 10/31/2024.
//

#include "Transform.h"
VECTOR2 Transform::forward() const {
    float angleRadians = (this->angle + 90) * M_PI / 180.0f;
    float x = -cos(angleRadians);
    float y = -sin(angleRadians);
    return VECTOR2(x, y);
}

Transform::Transform() {
    this->position = VECTOR2(0, 0);
    this->scale = VECTOR2(1, 1);
}

Transform::Transform(VECTOR2 position, VECTOR2 scale, float angle) {
    this->position = position;
    this->scale = scale;
    this->angle = angle;
}
