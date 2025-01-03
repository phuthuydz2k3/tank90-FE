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
#include "Game/Entities/GameObject.h"
#include "Game/Manager/LoadResourceManager.h"
#include "Game/Manager/SoundManager.h"
#include "Game/Manager/UIManager.h"
#include "Game/Services/GameplayService.h"
Sprite *exitBtnTextSprite;
Sprite *changeThemeTitleSprite;
bool isSound = true;
std::vector<std::string> paths = {
    "../Data/Images/dirt.png",
    "../Data/Images/sand.png"
};
int currentTheme = 0;

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
        std::cout << "Notified server that client " << NetworkTracking::id << " is " << (isPause ? "paused" : "resumed")
                << std::endl;
    }
}

void PauseUI::Init() {
    UIUnit::Init();
    pause(true);
    Image *container = EntityManager::getInstance()->createEntity<Image>();
    this->idEntities.push_back(container->getId());
    Transform *transform = container->getComponent<Transform>();
    transform->position = {400, 400};
    transform->angle = 0;
    Sprite *sprite = container->getComponent<Sprite>();
    sprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/panel_glass.png");
    sprite->size = {600, 400};
    sprite->layer = 100;

    Button *continueBtn = EntityManager::getInstance()->createEntity<Button>();
    this->idEntities.push_back(continueBtn->getId());
    Transform *continueBtnTransform = continueBtn->getComponent<Transform>();
    continueBtnTransform->parent = transform;
    continueBtnTransform->localPosition = {100, -100};
    continueBtnTransform->localAngle = 0;
    Sprite *continueBtnSprite = continueBtn->getComponent<Sprite>();
    continueBtnSprite->texture = LoadResourceManager::getInstance()->LoadTexture(
        "../Data/UI/button_square_depth_flat.png");
    continueBtnSprite->size = {100, 100};
    continueBtnSprite->layer = 101;
    Clickable *continueBtnClickable = continueBtn->getComponent<Clickable>();
    continueBtnClickable->onClick = []() {
        pause(false);
        UIManager::getInstance()->openUIUnit<GameplayUI>();
        GameplayService().PauseGame(false);
    };
    continueBtnClickable->size = {100, 100};

    Image *continueBtnText = EntityManager::getInstance()->createEntity<Image>();
    this->idEntities.push_back(continueBtnText->getId());
    Transform *continueBtnTextTransform = continueBtnText->getComponent<Transform>();
    continueBtnTextTransform->parent = continueBtnTransform;
    continueBtnTextTransform->localPosition = {0, 0};
    continueBtnTextTransform->localAngle = 0;
    Sprite *continueBtnTextSprite = continueBtnText->getComponent<Sprite>();
    continueBtnTextSprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/right.png");
    continueBtnTextSprite->size = {100, 100};
    continueBtnTextSprite->layer = 102;

    Button *exitBtn = EntityManager::getInstance()->createEntity<Button>();
    this->idEntities.push_back(exitBtn->getId());
    Transform *exitBtnTransform = exitBtn->getComponent<Transform>();
    exitBtnTransform->parent = transform;
    exitBtnTransform->localPosition = {-100, -100};
    exitBtnTransform->localAngle = 0;
    Sprite *exitBtnSprite = exitBtn->getComponent<Sprite>();
    exitBtnSprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/button_square_depth_flat.png");
    exitBtnSprite->size = {100, 100};
    exitBtnSprite->layer = 101;
    Clickable *exitBtnClickable = exitBtn->getComponent<Clickable>();

    exitBtnClickable->size = {100, 100};

    Image *exitBtnText = EntityManager::getInstance()->createEntity<Image>();
    this->idEntities.push_back(exitBtnText->getId());
    Transform *exitBtnTextTransform = exitBtnText->getComponent<Transform>();
    exitBtnTextTransform->parent = exitBtnTransform;
    exitBtnTextTransform->localPosition = {0, 0};
    exitBtnTextTransform->localAngle = 0;
    exitBtnTextSprite = exitBtnText->getComponent<Sprite>();
    exitBtnTextSprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/audioOn.png");
    exitBtnTextSprite->size = {100, 100};
    exitBtnTextSprite->layer = 102;
    exitBtnClickable->onClick = []() {
        isSound = !isSound;
        std::string pathSprite = isSound ? "../Data/UI/audioOn.png" : "../Data/UI/audioOff.png";
        exitBtnTextSprite->texture = LoadResourceManager::getInstance()->LoadTexture(pathSprite);
        SoundManager::getInstance()->setMute(!isSound);
    };

    GameObject *changeTheme = EntityManager::getInstance()->createEntity<GameObject>();
    this->idEntities.push_back(changeTheme->getId());
    changeTheme->addComponent<Transform>();
    Transform *changeThemeTf = changeTheme->getComponent<Transform>();
    changeThemeTf->parent = transform;
    changeThemeTf->localPosition = {0, 100};
    changeThemeTf->localAngle = 0;


    Image *changeThemeTitle = EntityManager::getInstance()->createEntity<Image>();
    this->idEntities.push_back(changeThemeTitle->getId());
    Transform *changeThemeTitleTransform = changeThemeTitle->getComponent<Transform>();
    changeThemeTitleTransform->parent = changeThemeTf;
    changeThemeTitleTransform->localPosition = {0, 0};
    changeThemeTitleSprite = changeThemeTitle->getComponent<Sprite>();
    changeThemeTitleSprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/Images/dirt.png");
    changeThemeTitleSprite->size = {100, 100};
    changeThemeTitleSprite->layer = 102;

    Button *rightBtn = EntityManager::getInstance()->createEntity<Button>();
    this->idEntities.push_back(rightBtn->getId());
    Transform *rightBtnTransform = rightBtn->getComponent<Transform>();
    rightBtnTransform->parent = changeThemeTf;
    rightBtnTransform->localPosition = {100, 0};
    rightBtnTransform->localAngle = 0;
    Sprite *rightBtnSprite = rightBtn->getComponent<Sprite>();
    rightBtnSprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/right.png");
    rightBtnSprite->size = {100, 100};
    rightBtnSprite->layer = 102;
    Clickable *rightBtnClickable = rightBtn->getComponent<Clickable>();
    rightBtnClickable->size = {100, 100};
    rightBtnClickable->onClick = []() {
        currentTheme = (currentTheme + 1) % paths.size();
        changeThemeTitleSprite->texture = LoadResourceManager::getInstance()->LoadTexture(paths[currentTheme]);
        GameplayService().ChangeTheme(currentTheme);
    };

    Button *leftBtn = EntityManager::getInstance()->createEntity<Button>();
    this->idEntities.push_back(leftBtn->getId());
    Transform *leftBtnTransform = leftBtn->getComponent<Transform>();
    leftBtnTransform->parent = changeThemeTf;
    leftBtnTransform->localPosition = {-100, 0};
    leftBtnTransform->localAngle = 0;
    Sprite *leftBtnSprite = leftBtn->getComponent<Sprite>();
    leftBtnSprite->texture = LoadResourceManager::getInstance()->LoadTexture("../Data/UI/left.png");
    leftBtnSprite->size = {100, 100};
    leftBtnSprite->layer = 102;
    Clickable *leftBtnClickable = leftBtn->getComponent<Clickable>();
    leftBtnClickable->size = {100, 100};
    leftBtnClickable->onClick = []() {
        currentTheme = (currentTheme - 1 + paths.size()) % paths.size();
        changeThemeTitleSprite->texture = LoadResourceManager::getInstance()->LoadTexture(paths[currentTheme]);
        GameplayService().ChangeTheme(currentTheme);
    };
}

void PauseUI::Close() {
    UIUnit::Close();
}
