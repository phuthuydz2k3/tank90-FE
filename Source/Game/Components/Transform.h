//
// Created by TCT on 10/31/2024.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "ECS/Component/Component.h"
#include "Math/Vector2.h"
#include "math.h"


class Transform : public Component {
public:
    VECTOR2 position;
    VECTOR2 scale;
    VECTOR2 localPosition;
    float angle;
    float localAngle;
    Transform* parent;

    VECTOR2 forward() const;

    Transform();

    Transform(VECTOR2 position, VECTOR2 scale , float angle);
};


#endif //TRANSFORM_H
