//
// Created by TCT on 11/24/2024.
//

#include "SpawnPoint.h"

#include "Tank.h"
#include "ECS/Entity/EntityManager.h"
#include "Game/Components/Effect.h"
#include "Game/Manager/LoadResourceManager.h"

class Transform;
class Tank;

SpawnPoint::SpawnPoint() {
    this->addComponent<Effect>();
    this->addComponent<Transform>();

    this->getComponent<Transform>()->position = VECTOR2(100, 100);
    this->getComponent<Transform>()->angle = 0;
    std::list<Frame> frames;
    frames.push_back(
        Frame{LoadResourceManager::getInstance()->LoadTexture("../Data/Images/enemy_spawn_1.png"), nullptr});
    frames.push_back(
        Frame{LoadResourceManager::getInstance()->LoadTexture("../Data/Images/enemy_spawn_2.png"), nullptr});
    frames.push_back(
        Frame{LoadResourceManager::getInstance()->LoadTexture("../Data/Images/enemy_spawn_3.png"), nullptr});
    frames.push_back(
        Frame{LoadResourceManager::getInstance()->LoadTexture("../Data/Images/enemy_spawn_4.png"), nullptr});
    Effect *effect = this->getComponent<Effect>();
    effect->frames = frames;
    effect->size = {50, 50};
    effect->timePerFrame = 0.1f;
    effect->loop = 2;
    effect->onEnd = [this] {
        EntityManager::getInstance()->removeEntity(this->getId());
        Tank *tank = EntityManager::getInstance()->createEntity<Tank>();
        tank->getComponent<Transform>()->position = this->getComponent<Transform>()->position;
        tank->getComponent<Sprite>()->layer = 1;
    };
}
