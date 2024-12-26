//
// Created by TCT on 11/22/2024.
//

#include "ControlSystem.h"

#include <boost/asio/io_context.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/ip/network_v4.hpp>
#include <boost/asio/ip/tcp.hpp>


#include "ECS/Entity/EntityManager.h"
#include "Game/Common/ActionStatePacket.h"
#include "Game/Common/Time.h"
#include "Game/Components/ControlComponent.h"
#include "Game/Components/NetworkReceiver.h"
#include "Game/Components/NetworkTracking.h"
#include "Game/Components/RectangleCollider.h"
#include "Game/Components/Transform.h"
#include "Game/Entities/Bullet.h"
#include "Game/Manager/SoundManager.h"
#include "Math/Vector2.h"

boost::asio::io_context io_context4;

void sendActionStatePacket(const ActionStatePacket& packet) {
    boost::asio::write(NetworkReceiver::tcpSocket, boost::asio::buffer(&packet, sizeof(ActionStatePacket)));
}

void ControlSystem::update() {
    System::update();
    auto entities = EntityManager::getInstance()->getEntitiesWithComponent<ControlComponent>();
    for (auto &entity: entities) {
        ControlComponent *control = entity->getComponent<ControlComponent>();
        control->currentKeyStates = SDL_GetKeyboardState(nullptr);
        int rotationMove = 0;
        int move = 0;
        if (control->isUp()) {
            move += 1;
        }
        if (control->isDown()) {
            move -= 1;
        }
        if (control->isLeft()) {
            rotationMove -= 1;
        }
        if (control->isRight()) {
            rotationMove += 1;
        }
        if (control->isSpeedup()) {
            control->speed = 150;
            control->rotationSpeed = 150;
        } else {
            control->speed = 100;
            control->rotationSpeed = 100;
        }
        if (control->isShoot()) {
            // SoundManager::getInstance()->PlaySound("../Data/Audio/Effect/tank_hit.wav");
            Bullet *bullet = EntityManager::getInstance()->createEntity<Bullet>();
            bullet->getComponent<Transform>()->position =
                    entity->getComponent<Transform>()->position + entity->getComponent<Transform>()->forward() * entity
                    ->getComponent<Sprite>()->size.magnitude() * 0.55f;
            bullet->getComponent<Transform>()->angle = entity->getComponent<Transform>()->angle;
            bullet->getComponent<RectangleCollider>()->layer = Player;
            ActionStatePacket actionPacket;
            actionPacket.id = NetworkTracking::id;
            actionPacket.isShooting = true;
            sendActionStatePacket(actionPacket);
        }
        Transform *transform = entity->getComponent<Transform>();
        if (move != 0) transform->position += transform->forward() * move * Time::deltaTime * control->speed;
        if (rotationMove != 0) transform->angle += rotationMove * Time::deltaTime * control->rotationSpeed;
    }
}

void ControlSystem::init() {
    System::init();
}
