//
// Created by TCT on 12/9/2024.
//

#include "NetworkReceiverSystem.h"
#include <iostream>
#include <SDL_net.h>
#include <vector>
#include "Game/Common/Packet.h"
#include "Game/Components/NetworkReceiver.h"
#include <cstring>

struct TankState {
    int id;
    Packet packet;
};
void NetworkReceiverSystem::update() {
    System::update();
    // Receive broadcasted state from server
    while (SDLNet_UDP_Recv(NetworkReceiver::clientSocket, NetworkReceiver::recvPacket)) {
        if (NetworkReceiver::recvPacket->len % sizeof(TankState) != 0) {
            std::cerr << "Received packet size mismatch" << std::endl;
            break;
        }

        std::vector<TankState> receivedTankStates;
        int numPackets = NetworkReceiver::recvPacket->len / sizeof(TankState);
        for (int i = 0; i < numPackets; ++i) {
            TankState receivedPacket;
            std::memcpy(&receivedPacket, NetworkReceiver::recvPacket->data + i * sizeof(TankState), sizeof(TankState));
            receivedTankStates.push_back(receivedPacket);
        }

        // Print received tank states
        for (const auto &tankState: receivedTankStates) {
            std::cout << "Tank ID: " << tankState.id << std::endl;
            std::cout << "Position: (" << tankState.packet.positionX << ", " << tankState.packet.positionY << ")" <<
                    std::endl;
            std::cout << "Scale: (" << tankState.packet.scaleX << ", " << tankState.packet.scaleY << ")" << std::endl;
            std::cout << "Angle: " << tankState.packet.angle << std::endl;
        }
    }
}

void NetworkReceiverSystem::init() {
    System::init();
    // Initialize client socket
    NetworkReceiver::clientSocket = SDLNet_UDP_Open(8082);
    if (!NetworkReceiver::clientSocket) {
        std::cerr << "Failed to open UDP socket: " << SDLNet_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    NetworkReceiver::recvPacket = SDLNet_AllocPacket(1024);
    if (!NetworkReceiver::recvPacket) {
        std::cerr << "Failed to allocate packet: " << SDLNet_GetError() << std::endl;
        SDLNet_UDP_Close(NetworkReceiver::clientSocket);
        SDL_Quit();
        return;
    }
}
