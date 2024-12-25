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
#include "Game/Components/NetworkTracking.h"
#include "Game/Components/Transform.h"
#include "Game/Entities/Tank.h"

class Tank;
boost::asio::io_context io_context3;

void NetworkReceiverSystem::update() {
    System::update();
    NetworkReceiver::clientSocket.non_blocking(true);
    while (true) {
        boost::system::error_code error;
        size_t len = NetworkReceiver::clientSocket.receive(boost::asio::buffer(NetworkReceiver::recvBuffer), 0, error);

        if (error && error != boost::asio::error::message_size) {
            if (error == boost::asio::error::would_block || error == boost::asio::error::try_again) {
                // No data received, break the loop
                break;
            } else {
                std::cerr << "Receive failed: " << error.message() << std::endl;
                break;
            }
        }

        if (len % sizeof(TankStatePacket) != 0) {
            std::cerr << "Received packet size mismatch" << std::endl;
            break;
        }

        std::vector<TankStatePacket> receivedTankStates;
        int numPackets = len / sizeof(TankStatePacket);
        for (int i = 0; i < numPackets; ++i) {
            TankStatePacket receivedPacket;
            std::memcpy(&receivedPacket, NetworkReceiver::recvBuffer.data() + i * sizeof(TankStatePacket),
                        sizeof(TankStatePacket));
            receivedTankStates.push_back(receivedPacket);
        }

        // Print received tank states
        auto entities = EntityManager::getInstance()->getEntitiesWithComponent<NetworkReceiver>();
        for (const auto &tankState: receivedTankStates) {
            bool haveTank = false;
            if (tankState.id == NetworkTracking::id) continue;
            for (const auto &entity: entities) {
                NetworkReceiver *networkReceiver = entity->getComponent<NetworkReceiver>();
                std:: cout << networkReceiver->id << " "<< tankState.id << std::endl;
                if (networkReceiver->id == tankState.id) {
                    haveTank = true;
                    std::cout << "Found tank with id: " << tankState.id << std::endl;
                    entity->getComponent<Transform>()->position = VECTOR2(tankState.positionX, tankState.positionY);
                    entity->getComponent<Transform>()->angle = tankState.angle;
                    break;
                }
            }
            std:: cout << entities.size() << std::endl;
            if (!haveTank) {
                Tank *tank = EntityManager::getInstance()->createEntity<Tank>();
                tank->removeComponent<ControlComponent>();
                tank->removeComponent<NetworkTracking>();
                tank->getComponent<Transform>()->position = VECTOR2(tankState.positionX, tankState.positionY);
                tank->getComponent<Transform>()->angle = tankState.angle;
                tank->addComponent<NetworkReceiver>();
                tank->getComponent<NetworkReceiver>()->id = tankState.id;
            }
            std::cout << "Received tank state: " << tankState.id << " " << tankState.positionX << " " << tankState.positionY
                    << " " << tankState.angle << std::endl;
        }
    }
}

void NetworkReceiverSystem::init() {
    System::init();

    // Open UDP socket
    NetworkReceiver::clientSocket.open(boost::asio::ip::udp::v4());

    // Set socket options to allow multiple clients to bind to the same address and port
    NetworkReceiver::clientSocket.set_option(boost::asio::socket_base::reuse_address(true));

    // Bind to port
    boost::asio::ip::udp::endpoint localEndpoint(boost::asio::ip::address_v4::any(), 8082);
    NetworkReceiver::clientSocket.bind(localEndpoint);

    // Connect to server using TCP to get unique ID
    boost::asio::ip::tcp::socket tcpSocket(io_context3);
    tcpSocket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8081));

    // Receive unique ID from server
    int uniqueId;
    boost::asio::read(tcpSocket, boost::asio::buffer(&uniqueId, sizeof(uniqueId)));
    NetworkTracking::id = uniqueId;

    std::cout << "Received unique ID: " << NetworkTracking::id << std::endl;
}
