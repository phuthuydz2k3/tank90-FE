//
// Created by TCT on 12/26/2024.
//

#include "LoseUI.h"

#include "Button.h"
#include "Clickable.h"
#include "Image.h"
#include "ECS/Entity/EntityManager.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"
#include "Game/Manager/LoadResourceManager.h"

// void onClick() {
//
// }
void LoseUI::Init() {
    UIUnit::Init();
    Image *container = EntityManager::getInstance()->createEntity<Image>();
    this->idEntities.push_back(container->getId());
    Transform *transform = container->getComponent<Transform>();
    transform->position = {400,400};
    transform->angle = 0;
    Sprite *sprite = container->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/panel_glass.png");
    sprite->size = {600,400};
    sprite->layer = 100;

    Image *lableImg = EntityManager::getInstance()->createEntity<Image>();
    this->idEntities.push_back(lableImg->getId());
    Transform *lableTransform = lableImg->getComponent<Transform>();
    lableTransform->parent = transform;
    lableTransform->localPosition = {0, -100};
    lableTransform->localAngle = 0;
    Sprite *lableSprite = lableImg->getComponent<Sprite>();
    lableSprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/ActionText_Defeat.png");
    lableSprite->size = {100.0f/149.0f * 605.0f, 100};
    lableSprite->layer = 101;

    Button* homeBtn = EntityManager::getInstance()->createEntity<Button>();
    this->idEntities.push_back(homeBtn->getId());
    Transform* homeBtnTransform = homeBtn->getComponent<Transform>();
    homeBtnTransform->parent = transform;
    homeBtnTransform->localPosition = {0, 100};
    homeBtnTransform->localAngle = 0;
    Sprite* homeBtnSprite = homeBtn->getComponent<Sprite>();
    homeBtnSprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/button_square_depth_flat.png");
    homeBtnSprite->size = {100, 100};
    homeBtnSprite->layer = 101;
    homeBtn->getComponent<Clickable>()->onClick = [] {
        std::cout << "LoseUI::onClick" << std::endl;
    };
    homeBtn->getComponent<Clickable>()->size = {100, 100};

    Image* homeBtnImage = EntityManager::getInstance()->createEntity<Image>();
    this->idEntities.push_back(homeBtnImage->getId());
    homeBtnImage->getComponent<Transform>()->parent = homeBtnTransform;
    homeBtnImage->getComponent<Transform>()->localPosition = {0, 0};
    homeBtnImage->getComponent<Transform>()->localAngle = 0;
    homeBtnImage->getComponent<Sprite>()->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/home.png");
    homeBtnImage->getComponent<Sprite>()->size = {50, 50};
    homeBtnImage->getComponent<Sprite>()->layer = 102;
}

void LoseUI::Close() {
    UIUnit::Close();
}
