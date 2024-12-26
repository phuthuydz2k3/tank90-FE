//
// Created by TCT on 12/26/2024.
//

#include "PauseUI.h"

#include "Button.h"
#include "Clickable.h"
#include "GameplayUI.h"
#include "ECS/Entity/EntityManager.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"
#include "Game/Manager/LoadResourceManager.h"
#include "Game/Manager/UIManager.h"
#include "Game/Services/GameplayService.h"

void PauseUI::Init() {
    UIUnit::Init();
    Button *container = EntityManager::getInstance()->createEntity<Button>();
    idEntities.push_back(container->getId());
    container->removeComponent<Clickable>();
    Sprite *sprite = container->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/GreenBox.png");
    sprite->size = {400, 400};
    container->getComponent<Transform>()->position = {400, 400};
    container->getComponent<Transform>()->angle = 0;
    Button * button = EntityManager::getInstance()->createEntity<Button>();
    this->idEntities.push_back(button->getId());
    button->getComponent<Clickable>()->size = {200, 100};
    button->getComponent<Clickable>()->onClick = []() {
        UIManager::getInstance()->openUIUnit<GameplayUI>();
        GameplayService().PauseGame(false);
    };
    Sprite *sprite1 = button->getComponent<Sprite>();
    sprite1->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/RecBtnOrange.png");
    sprite1->size = {200, 100};
    sprite1->layer = 101;
    button->getComponent<Transform>()->position = {400, 400};
    button->getComponent<Transform>()->angle = 0;
}

void PauseUI::Close() {
    UIUnit::Close();
}
