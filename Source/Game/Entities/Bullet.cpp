//
// Created by TCT on 11/23/2024.
//

#include "Bullet.h"

#include "ECS/Entity/EntityManager.h"
#include "Game/Components/DestroyCounter.h"
#include "Game/Components/RectangleCollider.h"

void onTriggerEnter(Entity *entity, Entity *other) {
    if(other->getComponent<RectangleCollider>()->layer == Player) return;
    EntityManager::getInstance()->removeEntity(entity->getId());
}

Bullet::Bullet() {
    this->addComponent<Transform>();
    this->addComponent<Sprite>();
    this->addComponent<FlyComponent>();
    this->addComponent<RectangleCollider>();
    // this->addComponent<DestroyCounter>();
    Sprite *sprite = this->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/Images/bulletUp.png");
    sprite->size = {10, 10};
    this->getComponent<Transform>()->angle = 0;
    this->getComponent<FlyComponent>()->speed = 200;
    this->getComponent<RectangleCollider>()->onTriggerEnter = onTriggerEnter;
    this->getComponent<RectangleCollider>()->size = {10, 10};
}
