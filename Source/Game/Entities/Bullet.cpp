//
// Created by TCT on 11/23/2024.
//

#include "Bullet.h"

#include "CollideExplosion.h"
#include "ECS/Entity/EntityManager.h"
#include "Game/Components/DestroyCounter.h"
#include "Game/Components/Effect.h"
#include "Game/Components/RectangleCollider.h"
#include "Game/Feature/BeDestroy.h"

void onTriggerEnter(Entity *entity, Entity *other) {
    if (other->getComponent<RectangleCollider>()->layer == entity->getComponent<RectangleCollider>()->layer) return;
    if(other->hasComponent<BeDestroy>()) {
        other->getComponent<BeDestroy>()->Destroy();
        other->getComponent<BeDestroy>()->isDestroyed = true;
    }
    CollideExplosion *collide_explosion = EntityManager::getInstance()->createEntity<CollideExplosion>();
    collide_explosion->getComponent<Transform>()->position = entity->getComponent<Transform>()->position;
    collide_explosion->getComponent<Effect>()->size = {25, 25};
    collide_explosion->getComponent<Effect>()->timePerFrame = 0.1f;
    collide_explosion->getComponent<Effect>()->loop = 1;
    collide_explosion->getComponent<Effect>()->onEnd = [collide_explosion] {
        EntityManager::getInstance()->removeEntity(collide_explosion->getId());
    };
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
    sprite->size = {5, 5};
    this->getComponent<Transform>()->angle = 0;
    this->getComponent<FlyComponent>()->speed = 200;
    this->getComponent<RectangleCollider>()->onTriggerEnter = onTriggerEnter;
    this->getComponent<RectangleCollider>()->size = {5, 5};
    this->getComponent<RectangleCollider>()->isTrigger = true;
}
