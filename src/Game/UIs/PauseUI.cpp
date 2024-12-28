//
// Created by TCT on 12/26/2024.
//

#include "PauseUI.h"

#include <boost/asio/write.hpp>
#include <boost/system/error_code.hpp>

#include "Button.h"
#include "Clickable.h"
#include "GameplayUI.h"
#include "Image.h"
#include "ECS/Entity/EntityManager.h"
#include "Game/Common/ActionStatePacket.h"
#include "Game/Components/NetworkReceiver.h"
#include "Game/Components/NetworkTracking.h"
#include "Game/Components/Sprite.h"
#include "Game/Components/Transform.h"
#include "Game/Manager/LoadResourceManager.h"
#include "Game/Manager/UIManager.h"
#include "Game/Services/GameplayService.h"
void pause(bool isPause) {

    ActionStatePacket packet;
    packet.type = 3;
    packet.id = NetworkTracking::id;
    packet.isPause = isPause;

    boost::system::error_code error;
    boost::asio::write(NetworkReceiver::tcpSocket, boost::asio::buffer(&packet, sizeof(ActionStatePacket)), error);

    if (error) {
        std::cerr << "Failed to send packet: " << error.message() << std::endl;
    } else {
        std::cout << "Notified server that client " << NetworkTracking::id << " is " << (isPause ? "paused" : "resumed") << std::endl;
    }
}
void PauseUI::Init() {
    UIUnit::Init();
    pause(true);
    Image *container = EntityManager::getInstance()->createEntity<Image>();
    this->idEntities.push_back(container->getId());
    Transform *transform = container->getComponent<Transform>();
    transform->position = {400,400};
    transform->angle = 0;
    Sprite *sprite = container->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/panel_glass.png");
    sprite->size = {600,300};
    sprite->layer = 100;

    Button *continueBtn = EntityManager::getInstance()->createEntity<Button>();
    this->idEntities.push_back(continueBtn->getId());
    Transform* continueBtnTransform = continueBtn->getComponent<Transform>();
    // continueBtnTransform->parent = transform;
    continueBtnTransform->position = {500,400};
    continueBtnTransform->angle = 0;
    Sprite *continueBtnSprite = continueBtn->getComponent<Sprite>();
    continueBtnSprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/button_square_depth_flat.png");
    continueBtnSprite->size = {100,100};
    continueBtnSprite->layer = 101;
    Clickable *continueBtnClickable = continueBtn->getComponent<Clickable>();
    continueBtnClickable->onClick = []() {
        pause(false);
        UIManager::getInstance()->openUIUnit<GameplayUI>();
        GameplayService().PauseGame(false);
    };
    continueBtnClickable->size = {100,100};

    Image *continueBtnText = EntityManager::getInstance()->createEntity<Image>();
    this->idEntities.push_back(continueBtnText->getId());
    Transform *continueBtnTextTransform = continueBtnText->getComponent<Transform>();
    continueBtnTextTransform->parent = continueBtnTransform;
    continueBtnTextTransform->localPosition = {0,0};
    continueBtnTextTransform->localAngle = 0;
    Sprite *continueBtnTextSprite = continueBtnText->getComponent<Sprite>();
    continueBtnTextSprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/right.png");
    continueBtnTextSprite->size = {100,100};
    continueBtnTextSprite->layer = 102;

    Button *exitBtn = EntityManager::getInstance()->createEntity<Button>();
    this->idEntities.push_back(exitBtn->getId());
    Transform* exitBtnTransform = exitBtn->getComponent<Transform>();
    exitBtnTransform->parent = transform;
    exitBtnTransform->localPosition = {-100,0};
    exitBtnTransform->localAngle = 0;
    Sprite *exitBtnSprite = exitBtn->getComponent<Sprite>();
    exitBtnSprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/button_square_depth_flat.png");
    exitBtnSprite->size = {100,100};
    exitBtnSprite->layer = 101;
    Clickable *exitBtnClickable = exitBtn->getComponent<Clickable>();
    exitBtnClickable->onClick = []() {
        // pause(false);
        // GameplayService().outGame();
        // LoadResourceManager::getInstance()->CleanUp();
        // EntityManager::getInstance()->clearEntities();
    };
    exitBtnClickable->size = {100,100};

    Image *exitBtnText = EntityManager::getInstance()->createEntity<Image>();
    this->idEntities.push_back(exitBtnText->getId());
    Transform *exitBtnTextTransform = exitBtnText->getComponent<Transform>();
    exitBtnTextTransform->parent = exitBtnTransform;
    exitBtnTextTransform->localPosition = {0,0};
    exitBtnTextTransform->localAngle = 0;
    Sprite *exitBtnTextSprite = exitBtnText->getComponent<Sprite>();
    exitBtnTextSprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/home.png");
    exitBtnTextSprite->size = {100,100};
    exitBtnTextSprite->layer = 102;

}

void PauseUI::Close() {
    UIUnit::Close();
}
