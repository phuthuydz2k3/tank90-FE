//
// Created by TCT on 11/23/2024.
//

#include "RectangleColliderSystem.h"

#include <cmath>

#include "ECS/Entity/EntityManager.h"
#include "Game/Components/RectangleCollider.h"
#include "Game/Components/Transform.h"

VECTOR2 getCorner(RectangleCollider &collider, const int index, const float &angle, const VECTOR2 &center) {
    const float hw = collider.size.x / 2;
    const float hh = collider.size.y / 2;
    const float cosA = std::cos(angle);
    const float sinA = std::sin(angle);
    switch (index) {
        case 0: return center + VECTOR2(-hw * cosA - hh * sinA, -hw * sinA + hh * cosA);
        case 1: return center + VECTOR2(hw * cosA - hh * sinA, hw * sinA + hh * cosA);
        case 2: return center + VECTOR2(hw * cosA + hh * sinA, hw * sinA - hh * cosA);
        case 3: return center + VECTOR2(-hw * cosA + hh * sinA, -hw * sinA - hh * cosA);
        default: return center;
    }
}

bool overlapOnAxis(RectangleCollider &collider1, RectangleCollider &collider2, const VECTOR2 &axis,
                   const VECTOR2 &center1, const VECTOR2 &center2) {
    float min1 = std::numeric_limits<float>::max();
    float max1 = std::numeric_limits<float>::lowest();
    float min2 = std::numeric_limits<float>::max();
    float max2 = std::numeric_limits<float>::lowest();
    for (int i = 0; i < 4; i++) {
        float p1 = getCorner(collider1, i, 0, center1).dot(axis);
        min1 = std::min(min1, p1);
        max1 = std::max(max1, p1);
        float p2 = getCorner(collider2, i, 0, center2).dot(axis);
        min2 = std::min(min2, p2);
        max2 = std::max(max2, p2);
    }
    return !(max1 < min2 || max2 < min1);
}

bool checkCollider(RectangleCollider &collider1, RectangleCollider &collider2, const float &angle1, const float &angle2,
                   const VECTOR2 &center1, const VECTOR2 &center2) {
    VECTOR2 axes[] = {
        (getCorner(collider1, 0, angle1, center1) - getCorner(collider1, 1, 0, center1)).normalize(),
        (getCorner(collider1, 0, angle1, center1) - getCorner(collider1, 3, 0, center1)).normalize(),
        (getCorner(collider2, 0, angle2, center2) - getCorner(collider2, 1, 0, center2)).normalize(),
        (getCorner(collider2, 0, angle2, center2) - getCorner(collider2, 3, 0, center2)).normalize()
    };
    for (auto &axis: axes) {
        if (!overlapOnAxis(collider1, collider2, axis, center1, center2)) return false;
    }
    return true;
}

void handleCollider(RectangleCollider &collider1, RectangleCollider &collider2, const float &angle1,
                    const float &angle2,
                    VECTOR2 &center1, VECTOR2 &center2) {
    VECTOR2 axes[] = {
        (getCorner(collider1, 0, angle1, center1) - getCorner(collider1, 1, 0, center1)).normalize(),
        (getCorner(collider1, 0, angle1, center1) - getCorner(collider1, 3, 0, center1)).normalize(),
        (getCorner(collider2, 0, angle2, center2) - getCorner(collider2, 1, 0, center2)).normalize(),
        (getCorner(collider2, 0, angle2, center2) - getCorner(collider2, 3, 0, center2)).normalize()
    };

    float minOverlap = std::numeric_limits<float>::max();
    VECTOR2 smallestAxis;

    for (auto &axis: axes) {
        float min1 = std::numeric_limits<float>::max();
        float max1 = std::numeric_limits<float>::lowest();
        float min2 = std::numeric_limits<float>::max();
        float max2 = std::numeric_limits<float>::lowest();

        for (int i = 0; i < 4; i++) {
            float p1 = getCorner(collider1, i, angle1, center1).dot(axis);
            min1 = std::min(min1, p1);
            max1 = std::max(max1, p1);
            float p2 = getCorner(collider2, i, angle2, center2).dot(axis);
            min2 = std::min(min2, p2);
            max2 = std::max(max2, p2);
        }

        const float overlap = std::min(max1, max2) - std::max(min1, min2);
        if (overlap < 0) return;

        if (overlap < minOverlap) {
            minOverlap = overlap;
            smallestAxis = axis;
        }
    }

    VECTOR2 displacement = smallestAxis * (minOverlap / 2);
    if (center1.dot(smallestAxis) < center2.dot(smallestAxis)) {
        center1 -= displacement;
        center2 += displacement;
    } else {
        center1 += displacement;
        center2 -= displacement;
    }
}

void handleStaticCollider(RectangleCollider &dynamicCollider, RectangleCollider &staticCollider, const float &angle1,
                          const float &angle2,
                          VECTOR2 &center1, const VECTOR2 &center2) {
    VECTOR2 axes[] = {
        (getCorner(dynamicCollider, 0, angle1, center1) - getCorner(dynamicCollider, 1, 0, center1)).normalize(),
        (getCorner(dynamicCollider, 0, angle1, center1) - getCorner(dynamicCollider, 3, 0, center1)).normalize(),
        (getCorner(staticCollider, 0, angle2, center2) - getCorner(staticCollider, 1, 0, center2)).normalize(),
        (getCorner(staticCollider, 0, angle2, center2) - getCorner(staticCollider, 3, 0, center2)).normalize()
    };

    float minOverlap = std::numeric_limits<float>::max();
    VECTOR2 smallestAxis;

    for (auto &axis: axes) {
        float min1 = std::numeric_limits<float>::max();
        float max1 = std::numeric_limits<float>::lowest();
        float min2 = std::numeric_limits<float>::max();
        float max2 = std::numeric_limits<float>::lowest();

        for (int i = 0; i < 4; i++) {
            float p1 = getCorner(dynamicCollider, i, angle1, center1).dot(axis);
            min1 = std::min(min1, p1);
            max1 = std::max(max1, p1);
            float p2 = getCorner(staticCollider, i, angle2, center2).dot(axis);
            min2 = std::min(min2, p2);
            max2 = std::max(max2, p2);
        }

        float overlap = std::min(max1, max2) - std::max(min1, min2);
        if (overlap < 0) return;

        if (overlap < minOverlap) {
            minOverlap = overlap;
            smallestAxis = axis;
        }
    }

    VECTOR2 displacement = smallestAxis * minOverlap;
    if (center1.dot(smallestAxis) < center2.dot(smallestAxis)) {
        center1 -= displacement;
    } else {
        center1 += displacement;
    }
}

void RectangleColliderSystem::update() {
    System::update();
    auto entities = EntityManager::getInstance()->getEntitiesWithComponent<RectangleCollider>();
    for (auto it1 = entities.begin(); it1 != entities.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != entities.end(); ++it2) {
            auto entity1 = *it1;
            auto entity2 = *it2;
            RectangleCollider *collider1 = entity1->getComponent<RectangleCollider>();
            RectangleCollider *collider2 = entity2->getComponent<RectangleCollider>();
            Transform *transform1 = entity1->getComponent<Transform>();
            Transform *transform2 = entity2->getComponent<Transform>();
            if (checkCollider(*collider1, *collider2, transform1->angle, transform2->angle, transform1->position,
                              transform2->position)) {
                if (collider1->onTriggerEnter != nullptr) collider1->onTriggerEnter(entity1, entity2);
                if (collider2->onTriggerEnter != nullptr) collider2->onTriggerEnter(entity2, entity1);
                if (!collider1->isTrigger && !collider2->isTrigger) {
                    if (collider2->isStatic) {
                        handleStaticCollider(*collider1, *collider2, transform1->angle, transform2->angle,
                                             transform1->position,
                                             transform2->position);
                        continue;
                    }
                    if (collider1->isStatic) {
                        handleStaticCollider(*collider2, *collider1, transform2->angle, transform1->angle,
                                             transform2->position, transform1->position);
                        continue;
                    }
                    handleCollider(*collider1, *collider2, transform1->angle, transform2->angle, transform1->position,
                                   transform2->position);
                }
            }
        }
    }
}



void RectangleColliderSystem::init() {
    System::init();
}
