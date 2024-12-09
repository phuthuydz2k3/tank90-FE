#include "NetworkTrackingSystem.h"
#include <iostream>
#include <cstring>
#include <SDL_net.h>
#include "ECS/Entity/EntityManager.h"
#include "Game/Common/Packet.h"
#include "Game/Components/NetworkTracking.h"
#include "Game/Components/Transform.h"
#include "Game/Common/Time.h"

IPaddress NetworkTrackingSystem::serverAddress;
UDPsocket NetworkTrackingSystem::udpSocket;
float countTime = 0;
float timeSend = 1.0f/60.0f; // 60fps
void NetworkTrackingSystem::init() {
    System::init();

    // Initialize SDL_net
    if (SDLNet_Init() < 0) {
        std::cerr << "SDL_net haven't been initialized: " << SDLNet_GetError() << std::endl;
        return;
    }

    // Create UDP socket
    udpSocket = SDLNet_UDP_Open(0);
    if (!udpSocket) {
        std::cerr << "Failed to open UDP socket: " << SDLNet_GetError() << std::endl;
        return;
    }

    // Resolve server address
    if (SDLNet_ResolveHost(&serverAddress, "127.0.0.1", 8080) < 0) {
        std::cerr << "Failed to resolve server address: " << SDLNet_GetError() << std::endl;
        return;
    }
}

void serializeTransform(const Transform* transform, Packet& packet) {
    packet.positionX = transform->position.x;
    packet.positionY = transform->position.y;
    packet.scaleX = transform->scale.x;
    packet.scaleY = transform->scale.y;
    packet.angle = transform->angle;
}

void NetworkTrackingSystem::sendTankPosition(const Transform* transform) {
    Packet packet;
    serializeTransform(transform, packet);

    UDPpacket* udpPacket = SDLNet_AllocPacket(sizeof(Packet));
    if (!udpPacket) {
        std::cerr << "Failed to allocate packet: " << SDLNet_GetError() << std::endl;
        return;
    }

    std::memcpy(udpPacket->data, &packet, sizeof(Packet));
    udpPacket->len = sizeof(Packet);
    udpPacket->address = serverAddress;

    if (SDLNet_UDP_Send(udpSocket, -1, udpPacket) == 0) {
        std::cerr << "Failed to send packet: " << SDLNet_GetError() << std::endl;
    }

    SDLNet_FreePacket(udpPacket);
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