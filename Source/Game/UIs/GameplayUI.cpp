//
// Created by TCT on 12/26/2024.
//

#include "GameplayUI.h"

#include "Button.h"
#include "Clickable.h"
#include "PauseUI.h"
#include "ECS/Entity/EntityManager.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"
#include "Game/Manager/LoadResourceManager.h"
#include "Game/Manager/UIManager.h"
#include "Game/Services/GameplayService.h"

void pauseGame() {
    GameplayService().PauseGame(true);
    UIManager::getInstance()->openUIUnit<PauseUI>();
}
void GameplayUI::Init() {
    UIUnit::Init();
    Button *button = EntityManager::getInstance()->createEntity<Button>();
    idEntities.push_back(button->getId());
    button->getComponent<Clickable>()->onClick = pauseGame;
    button->getComponent<Clickable>()->size = {50, 50};
    Sprite *sprite = button->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/BluePause.png");
    sprite->size = {50, 50};
    button->getComponent<Transform>()->position = {50, 50};
    button->getComponent<Transform>()->angle = 0;
}

void GameplayUI::Close() {
    UIUnit::Close();
}
