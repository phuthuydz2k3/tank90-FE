//
// Created by TCT on 12/26/2024.
//

#include "LoseUI.h"

#include "Button.h"
#include "Clickable.h"
#include "ECS/Entity/EntityManager.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"
#include "Game/Manager/LoadResourceManager.h"

// void onClick() {
//
// }
void LoseUI::Init() {
    UIUnit::Init();
    Button *button = EntityManager::getInstance()->createEntity<Button>();
    idEntities.push_back(button->getId());
    // button->getComponent<Clickable>()->onClick = onClick;
    button->getComponent<Clickable>()->size = {300, 100};
    Sprite *sprite = button->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/RecGreenBtn.png");
    sprite->size = {300, 100};
    button->getComponent<Transform>()->position = {400, 300};
    button->getComponent<Transform>()->angle = 0;
}

void LoseUI::Close() {
    UIUnit::Close();
}
