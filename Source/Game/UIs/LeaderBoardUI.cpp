//
// Created by TCT on 12/27/2024.
//

#include "LeaderBoardUI.h"

#include "Button.h"
#include "Clickable.h"
#include "Image.h"
#include "Text.h"
#include "ECS/Entity/EntityManager.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"
#include "Game/Entities/GameObject.h"
#include "Game/Manager/LoadResourceManager.h"
#include "Game/Services/GameplayService.h"


void LeaderBoardUI::Init() {
    UIUnit::Init();
    std::cout << "LeaderBoardUI" << std::endl;
    Image *leaderBoard = EntityManager::getInstance()->createEntity<Image>();
    this->idEntities.push_back(leaderBoard->getId());
    Transform *leaderBoardTransform = leaderBoard->getComponent<Transform>();
    leaderBoardTransform->position = {400, 100};
    leaderBoardTransform->angle = 0;
    Sprite *leaderBoardSprite = leaderBoard->getComponent<Sprite>();
    leaderBoardSprite->texture = LoadResourceManager::getInstance()->LoadTexture(
        "../Data/Images/Icon_ColorIcon_Leaderboard.png");
    leaderBoardSprite->size = {150, 150};
    leaderBoardSprite->layer = 100;

    Image *container = EntityManager::getInstance()->createEntity<Image>();
    this->idEntities.push_back(container->getId());
    Transform *transform = container->getComponent<Transform>();
    transform->position = {400, 500};
    transform->angle = 0;
    Sprite *sprite = container->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/panel_glass.png");
    sprite->size = {600, 600};
    sprite->layer = 100;

    Button *homeBtn = EntityManager::getInstance()->createEntity<Button>();
    this->idEntities.push_back(homeBtn->getId());
    Transform *homeBtnTransform = homeBtn->getComponent<Transform>();
    homeBtnTransform->parent = transform;
    homeBtnTransform->localPosition = {200, 0};
    homeBtnTransform->angle = 0;
    Sprite *homeBtnSprite = homeBtn->getComponent<Sprite>();
    homeBtnSprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/button_square_depth_flat.png");
    homeBtnSprite->size = {100, 100};
    homeBtnSprite->layer = 102;
    homeBtn->getComponent<Clickable>()->size = {100, 100};
    homeBtn->getComponent<Clickable>()->onClick = [] {
        std::cout << "Home" << std::endl;
    };

    Image *homeIcon = EntityManager::getInstance()->createEntity<Image>();
    this->idEntities.push_back(homeIcon->getId());
    homeIcon->getComponent<Transform>()->parent = homeBtnTransform;
    homeIcon->getComponent<Transform>()->localPosition = {0, 0};
    homeIcon->getComponent<Transform>()->localAngle = 0;
    homeIcon->getComponent<Sprite>()->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/home.png");
    homeIcon->getComponent<Sprite>()->size = {50, 50};
    homeIcon->getComponent<Sprite>()->layer = 103;


    auto leaderboard = GameplayService().GetLeaderBoard();
    std::sort(leaderboard.begin(), leaderboard.end(),
              [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
                  return a.second > b.second;
              });
    int count = leaderboard.size() > 5 ? 5 : leaderboard.size();
    for (int i = -1; i < count; i++) {
        GameObject *userName = EntityManager::getInstance()->createEntity<GameObject>();
        this->idEntities.push_back(userName->getId());
        userName->addComponent<Transform>();
        userName->addComponent<Text>();
        userName->getComponent<Text>()->text = i == -1 ? "Name" : leaderboard[i].first;
        userName->getComponent<Text>()->font = LoadResourceManager::getInstance()->LoadFont(
            "../Data/Text/BrownieStencil-8O8MJ.ttf", 20);
        userName->getComponent<Text>()->color = {0, 0, 0, 255};
        Transform *userNameTransform = userName->getComponent<Transform>();
        userNameTransform->parent = transform;
        userNameTransform->localPosition = {-200, -100 + i * 100.0f};
        userNameTransform->angle = 0;

        GameObject *score = EntityManager::getInstance()->createEntity<GameObject>();
        this->idEntities.push_back(score->getId());
        score->addComponent<Transform>();
        score->addComponent<Text>();
        score->getComponent<Text>()->text = i == -1 ? "Score" : std::to_string(leaderboard[i].second);
        score->getComponent<Text>()->font = LoadResourceManager::getInstance()->LoadFont(
            "../Data/Text/BrownieStencil-8O8MJ.ttf", 20);
        score->getComponent<Text>()->color = {0, 0, 0, 255};
        Transform *scoreTransform = score->getComponent<Transform>();
        scoreTransform->parent = transform;
        scoreTransform->localPosition = {50, -100 + i * 100.0f};
        scoreTransform->angle = 0;
    }
}
