#include "NetworkTrackingSystem.h"
#include <iostream>
#include <cstring>
#include <boost/asio.hpp>
#include "ECS/Entity/EntityManager.h"
#include "Game/Common/TankStatePacket.h"
#include "Game/Components/NetworkTracking.h"
#include "Game/Components/Transform.h"
#include "Game/Common/Time.h"
#include "Game/Components/NetworkReceiver.h"

boost::asio::io_context io_context;
boost::asio::ip::udp::socket NetworkTrackingSystem::udpSocket(io_context);
boost::asio::ip::udp::endpoint NetworkTrackingSystem::serverEndpoint;
float countTime = 0;
float timeSend = 1.0f / 60.0f; // 60fps

void NetworkTrackingSystem::init() {
    System::init();

    // Open UDP socket
    udpSocket.open(boost::asio::ip::udp::v4());

    // Resolve server address
    boost::asio::ip::udp::resolver resolver(io_context);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "127.0.0.1", "8080");
    serverEndpoint = *resolver.resolve(query).begin();
}

void serializeTransform(const Transform* transform, TankStatePacket& packet, int tankId) {
    packet.id = tankId;
    packet.positionX = transform->position.x;
    packet.positionY = transform->position.y;
    packet.angle = transform->angle;
}

void NetworkTrackingSystem::sendTankPosition(const Transform* transform) {
    TankStatePacket packet;
    int tankId = NetworkReceiver::id;
    serializeTransform(transform, packet, tankId);

    std::vector<char> buffer(sizeof(TankStatePacket));
    std::memcpy(buffer.data(), &packet, sizeof(TankStatePacket));

    boost::system::error_code error;
    udpSocket.send_to(boost::asio::buffer(buffer), serverEndpoint, 0, error);

    if (error) {
        std::cerr << "Failed to send packet: " << error.message() << std::endl;
    }
}

void NetworkTrackingSystem::update() {
    System::update();
    countTime += Time::deltaTime;
    if (countTime < timeSend) return;
    countTime = 0;
    const auto entities = EntityManager::getInstance()->getEntitiesWithComponent<NetworkTracking>();
    for (auto& entity : entities) {
        Transform* transform = entity->getComponent<Transform>();
        NetworkTracking* networkTracking = entity->getComponent<NetworkTracking>();
        if (networkTracking->typeTracking == 0) {
            sendTankPosition(transform);
        }
    }
}