//
// Created by TCT on 11/23/2024.
//

#ifndef RETANGLECOLLIDER_H
#define RETANGLECOLLIDER_H
#include "ECS/Component/Component.h"
#include "ECS/Entity/Entity.h"
#include "Game/Common/ColliderLayer.h"
#include "Math/Vector2.h"


class RectangleCollider : public Component {
public:
    RectangleCollider();

    RectangleCollider(const VECTOR2 &size, bool isTrigger, void (*onTriggerEnter)(Entity *entity, Entity *other));

    VECTOR2 size;
    bool isTrigger;
    bool isStatic;
    ColliderLayer layer;

    void (*onTriggerEnter)(Entity *entity, Entity *other);
};


#endif //RETANGLECOLLIDER_H
