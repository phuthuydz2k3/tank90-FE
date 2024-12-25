//
// Created by TCT on 11/23/2024.
//

#include "RectangleCollider.h"

RectangleCollider::RectangleCollider() {
    this->size = VECTOR2(0, 0);
    this->isTrigger = false;
    this->onTriggerEnter = nullptr;
    this->isStatic = false;
}

RectangleCollider::RectangleCollider(const VECTOR2 &size, const bool isTrigger,
                                     void (*onTriggerEnter)(Entity* entity, Entity *other)) {
    this->size = size;
    this->isTrigger = isTrigger;
    this->onTriggerEnter = onTriggerEnter;
}
