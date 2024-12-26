//
// Created by TCT on 12/26/2024.
//

#include "GameplayUI.h"

#include "Button.h"
#include "Clickable.h"
#include "Image.h"
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
    Button *container = EntityManager::getInstance()->createEntity<Button>();
    idEntities.push_back(container->getId());
    container->getComponent<Transform>()->position = {50,50};
    container->getComponent<Transform>()->angle = 0;
    container->getComponent<Clickable>()->onClick = pauseGame;
    container->getComponent<Clickable>()->size = {70, 70};
    Sprite *sprite = container->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/button_round_border.png");
    sprite->size = {70, 70};
    sprite->layer = 100;

    Image *image = EntityManager::getInstance()->createEntity<Image>();
    idEntities.push_back(image->getId());
    Sprite *sprite1 = image->getComponent<Sprite>();
    sprite1->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/pause.png");
    sprite1->size = {30, 30};
    sprite1->layer = 101;
    image->getComponent<Transform>()->parent = container->getComponent<Transform>();
    image->getComponent<Transform>()->localPosition = {0, 0};
    image->getComponent<Transform>()->angle = 0;

}

void GameplayUI::Close() {
    UIUnit::Close();
}
