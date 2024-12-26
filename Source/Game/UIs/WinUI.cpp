//
// Created by TCT on 12/26/2024.
//

#include "WinUI.h"

#include <iostream>

#include "Button.h"
#include "Clickable.h"
#include "ECS/Entity/EntityManager.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"
#include "Game/Manager/LoadResourceManager.h"

void onClick() {
    std::cout << "WinUI::onClick" << std::endl;
}

void WinUI::Init() {
    UIUnit::Init();
    Button *button = EntityManager::getInstance()->createEntity<Button>();
    idEntities.push_back(button->getId());
    button->getComponent<Clickable>()->onClick = onClick;
    button->getComponent<Clickable>()->size = {300, 100};
    Sprite *sprite = button->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/RecBtnOrange.png");
    sprite->size = {300, 100};
    button->getComponent<Transform>()->position = {400, 300};
}

void WinUI::Close() {
    UIUnit::Close();
}
