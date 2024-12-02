#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <iostream>
#include <vector>
#include <cstring>
#include "Game/Common/Packet.h"

struct TankState {
    int id;
    Packet packet;
};

std::vector<TankState> tankStates;

void printPacket(const Packet& packet) {
    std::cout << "Received Packet:" << std::endl;
    std::cout << "Position: (" << packet.positionX << ", " << packet.positionY << ")" << std::endl;
    std::cout << "Scale: (" << packet.scaleX << ", " << packet.scaleY << ")" << std::endl;
    std::cout << "Angle: " << packet.angle << std::endl;
}

void updateTankState(int id, const Packet& packet) {
    for (auto& tankState : tankStates) {
        if (tankState.id == id) {
            tankState.packet = packet;
            return;
        }
    }
    // If tank state not found, add new tank state
    tankStates.push_back({id, packet});
}

void broadcastTankStates(UDPsocket serverSocket) {
    // Calculate the total size of the packet
    size_t packetSize = tankStates.size() * sizeof(TankState);
    UDPpacket* udpPacket = SDLNet_AllocPacket(packetSize);
    if (!udpPacket) {
        std::cerr << "Failed to allocate packet: " << SDLNet_GetError() << std::endl;
        return;
    }

    // Copy the tank states into the packet data
    std::memcpy(udpPacket->data, tankStates.data(), packetSize);
    udpPacket->len = packetSize;
    udpPacket->address.host = INADDR_BROADCAST; // Broadcast address
    udpPacket->address.port = 8081; // Broadcast port for clients

    if (SDLNet_UDP_Send(serverSocket, -1, udpPacket) == 0) {
        std::cerr << "Failed to send packet: " << SDLNet_GetError() << std::endl;
    }

    SDLNet_FreePacket(udpPacket);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(0) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (SDLNet_Init() < 0) {
        std::cerr << "SDLNet_Init failed: " << SDLNet_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    UDPsocket serverSocket = SDLNet_UDP_Open(8080);
    if (!serverSocket) {
        std::cerr << "Failed to open UDP socket: " << SDLNet_GetError() << std::endl;
        SDLNet_Quit();
        SDL_Quit();
        return -1;
    }

    UDPpacket* packet = SDLNet_AllocPacket(sizeof(Packet));
    if (!packet) {
        std::cerr << "Failed to allocate packet: " << SDLNet_GetError() << std::endl;
        SDLNet_UDP_Close(serverSocket);
        SDLNet_Quit();
        SDL_Quit();
        return -1;
    }

    Uint32 lastSendTime = SDL_GetTicks();
    Uint32 sendInterval = 1000 / 60; // 60 FPS

    while (true) {
        Uint32 currentTime = SDL_GetTicks();
        if (SDLNet_UDP_Recv(serverSocket, packet)) {
            Packet receivedPacket;
            std::memcpy(&receivedPacket, packet->data, sizeof(Packet));
            printPacket(receivedPacket);

            // Update tank state
            updateTankState(packet->address.host, receivedPacket);
        }

        // Broadcast tank states at 60 FPS
        if (currentTime - lastSendTime >= sendInterval) {
            broadcastTankStates(serverSocket);
            lastSendTime = currentTime;
        }

        SDL_Delay(16);
    }

    SDLNet_FreePacket(packet);
    SDLNet_UDP_Close(serverSocket);
    SDLNet_Quit();
    SDL_Quit();

    return 0;
}