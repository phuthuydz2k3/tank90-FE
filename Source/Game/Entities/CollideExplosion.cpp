//
// Created by TCT on 11/24/2024.
//

#include "CollideExplosion.h"

#include "Game/Components/Effect.h"
#include "Game/Components/Transform.h"
#include "Game/Manager/LoadResourceManager.h"

CollideExplosion::CollideExplosion() {
    this->addComponent<Transform>();
    this->addComponent<Effect>();
    std::list<Frame> frames;
    frames.push_back(Frame({LoadResourceManager::getInstance()->LoadTexture("../Data/Images/Explosion/explosion1.png"), nullptr}));
    frames.push_back(Frame({LoadResourceManager::getInstance()->LoadTexture("../Data/Images/Explosion/explosion2.png"), nullptr}));
    frames.push_back(Frame({LoadResourceManager::getInstance()->LoadTexture("../Data/Images/Explosion/explosion3.png"), nullptr}));
    frames.push_back(Frame({LoadResourceManager::getInstance()->LoadTexture("../Data/Images/Explosion/explosion4.png"), nullptr}));
    frames.push_back(Frame({LoadResourceManager::getInstance()->LoadTexture("../Data/Images/Explosion/explosion5.png"), nullptr}));
    this->getComponent<Effect>()->frames = frames;
}
