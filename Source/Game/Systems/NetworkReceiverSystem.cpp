//
// Created by TCT on 12/9/2024.
//

#include "NetworkReceiverSystem.h"
#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include "Game/Common/TankStatePacket.h"
#include "Game/Components/NetworkReceiver.h"
#include <cstring>

#include "ECS/Entity/EntityManager.h"
#include "Game/Common/ActionStatePacket.h"
#include "Game/Components/NetworkTracking.h"
#include "Game/Components/RectangleCollider.h"
#include "Game/Components/Transform.h"
#include "Game/Entities/Bullet.h"
#include "Game/Entities/Tank.h"
#include "Game/Manager/SoundManager.h"

boost::asio::io_context io_context3;

void NetworkReceiverSystem::update()
{
    System::update();
    NetworkReceiver::clientSocket.non_blocking(true);
    NetworkReceiver::tcpSocket.non_blocking(true);
    while (true)
    {
        boost::system::error_code error;
        size_t len = NetworkReceiver::clientSocket.receive(boost::asio::buffer(NetworkReceiver::recvBuffer), 0, error);

        if (error && error != boost::asio::error::message_size)
        {
            if (error == boost::asio::error::would_block || error == boost::asio::error::try_again)
            {
                // No data received, break the loop
                break;
            }
            else
            {
                std::cerr << "Receive failed: " << error.message() << std::endl;
                break;
            }
        }

        if (len % sizeof(TankStatePacket) != 0)
        {
            std::cerr << "Received packet size mismatch" << std::endl;
            break;
        }

        std::vector<TankStatePacket> receivedTankStates;
        int numPackets = len / sizeof(TankStatePacket);
        for (int i = 0; i < numPackets; ++i)
        {
            TankStatePacket receivedPacket;
            std::memcpy(&receivedPacket, NetworkReceiver::recvBuffer.data() + i * sizeof(TankStatePacket),
                        sizeof(TankStatePacket));
            receivedTankStates.push_back(receivedPacket);
        }

        auto entities = EntityManager::getInstance()->getEntitiesWithComponent<NetworkReceiver>();
        for (const auto &tankState : receivedTankStates)
        {
            bool haveTank = false;
            if (tankState.id == NetworkTracking::id)
                continue;
            if (tankState.isDie)
                continue;
            for (const auto &entity : entities)
            {
                NetworkReceiver *networkReceiver = entity->getComponent<NetworkReceiver>();
                if (networkReceiver->id == tankState.id)
                {
                    haveTank = true;
                    entity->getComponent<Transform>()->position = VECTOR2(tankState.positionX, tankState.positionY);
                    entity->getComponent<Transform>()->angle = tankState.angle;
                    // if (tankState.isShooting) {
                    //     SoundManager::getInstance()->PlaySound("../Data/Audio/Effect/tank_hit.wav");
                    //     Bullet *bullet = EntityManager::getInstance()->createEntity<Bullet>();
                    //     bullet->getComponent<Transform>()->position =
                    //             entity->getComponent<Transform>()->position + entity->getComponent<Transform>()->forward() * entity
                    //             ->getComponent<Sprite>()->size.magnitude() * 0.55f;
                    //     bullet->getComponent<Transform>()->angle = entity->getComponent<Transform>()->angle;
                    //     bullet->getComponent<RectangleCollider>()->layer = Enemy;
                    // }

                    break;
                }
            }
            if (!haveTank && !tankState.isDie)
            {
                Tank *tank = EntityManager::getInstance()->createEntity<Tank>();
                tank->removeComponent<ControlComponent>();
                tank->removeComponent<NetworkTracking>();
                tank->getComponent<Transform>()->position = VECTOR2(tankState.positionX, tankState.positionY);
                tank->getComponent<Transform>()->angle = tankState.angle;
                tank->addComponent<NetworkReceiver>();
                tank->getComponent<NetworkReceiver>()->id = tankState.id;
                tank->getComponent<RectangleCollider>()->layer = Enemy;
            }
        }
        for (const auto &entity : entities)
        {
            bool haveTank = false;
            for (const auto &tankState : receivedTankStates)
            {
                if (tankState.id == NetworkTracking::id)
                    continue;
                if (tankState.id == entity->getComponent<NetworkReceiver>()->id && !tankState.isDie)
                {
                    haveTank = true;
                    break;
                }
            }
            if (!haveTank)
            {
                EntityManager::getInstance()->removeEntity(entity->getId());
            }
        }
    }
    while (true)
    {
        ActionStatePacket actionPacket;
        boost::system::error_code error;
        size_t actionLen = NetworkReceiver::tcpSocket.read_some(boost::asio::buffer(&actionPacket, sizeof(ActionStatePacket)), error);

        if (error == boost::asio::error::eof)
        {
            break; // Connection closed cleanly by peer
        }
        else if (error)
        {
            std::cerr << "Receive failed: " << error.message() << std::endl;
            break;
        }

        if (actionLen == sizeof(ActionStatePacket))
        {
            std::cout << actionPacket.isShooting << std::endl;
            std::cout << NetworkTracking::id << std::endl;

            auto entities = EntityManager::getInstance()->getEntitiesWithComponent<NetworkReceiver>();
            std::cout << entities.size() << std::endl;

            for (const auto &entity : entities)
            {
                NetworkReceiver *networkReceiver = entity->getComponent<NetworkReceiver>();
                if (networkReceiver->id == actionPacket.id)
                {
                    if (actionPacket.isShooting)
                    {
                        // SoundManager::getInstance()->PlaySound("../Data/Audio/Effect/tank_hit.wav");
                        Bullet *bullet = EntityManager::getInstance()->createEntity<Bullet>();
                        bullet->getComponent<Transform>()->position =
                            entity->getComponent<Transform>()->position + entity->getComponent<Transform>()->forward() * entity->getComponent<Sprite>()->size.magnitude() * 0.55f;
                        bullet->getComponent<Transform>()->angle = entity->getComponent<Transform>()->angle;
                        std::cout << bullet->getComponent<Transform>()->position.x << " " << bullet->getComponent<Transform>()->position.y << std::endl;
                        bullet->getComponent<RectangleCollider>()->layer = Enemy;
                    }
                }
            }
        }
    }
}

void NetworkReceiverSystem::init()
{
    System::init();

    // Open UDP socket
    NetworkReceiver::clientSocket.open(boost::asio::ip::udp::v4());

    // Set socket options to allow multiple clients to bind to the same address and port
    NetworkReceiver::clientSocket.set_option(boost::asio::socket_base::reuse_address(true));

    // Bind to port
    boost::asio::ip::udp::endpoint localEndpoint(boost::asio::ip::address_v4::any(), 8082);
    NetworkReceiver::clientSocket.bind(localEndpoint);

    // Connect to server using TCP to get unique ID
    NetworkReceiver::tcpSocket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8081));

    // Receive unique ID from server
    int uniqueId;
    boost::asio::read(NetworkReceiver::tcpSocket, boost::asio::buffer(&uniqueId, sizeof(uniqueId)));
    NetworkTracking::id = uniqueId;

    std::cout << "Received unique ID: " << NetworkTracking::id << std::endl;

    // Start a new thread to handle ActionStatePacket
    // std::thread(handleActionStatePackets).detach();
}
