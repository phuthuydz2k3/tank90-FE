//
// Created by TCT on 11/22/2024.
//

#include "ControlSystem.h"

#include <iostream>

#include "ECS/Entity/EntityManager.h"
#include "Game/Common/Time.h"
#include "Game/Components/ControlComponent.h"
#include "Game/Components/Transform.h"
#include "Game/Entities/Bullet.h"
#include "Math/Vector2.h"

class ControlComponent;

void ControlSystem::update() {
    System::update();
    auto entities = EntityManager::getInstance()->getEntitiesWithComponent<ControlComponent>();
    for (auto &entity: entities) {
        ControlComponent *control = entity->getComponent<ControlComponent>();
        control->currentKeyStates = SDL_GetKeyboardState(nullptr);
        int rotationMove = 0;
        int move = 0;
        if (control->isUp()) {
            move += 1;
        }
        if (control->isDown()) {
            move -= 1;
        }
        if (control->isLeft()) {
            rotationMove -= 1;
        }
        if (control->isRight()) {
            rotationMove += 1;
        }
        if (control->isShoot()) {
            Bullet* bullet = EntityManager::getInstance()->createEntity<Bullet>();
            bullet->getComponent<Transform>()->position = entity->getComponent<Transform>()->position + entity->getComponent<Transform>()->forward() * entity->getComponent<Sprite>()->size.magnitude() * 0.5f;
            bullet->getComponent<Transform>()->angle = entity->getComponent<Transform>()->angle;
        }
        Transform *transform = entity->getComponent<Transform>();
        if (move != 0) transform->position += transform->forward() * move * Time::deltaTime * control->speed;
        if(rotationMove != 0) transform->angle += rotationMove * Time::deltaTime * control->rotationSpeed;
    }
}

void ControlSystem::init() {
    System::init();
}
