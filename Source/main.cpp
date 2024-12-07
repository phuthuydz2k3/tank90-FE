#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <cstring>
#include <SDL2/SDL_net.h>
#include <arpa/inet.h> // Include for inet_addr and htonl
#include <sys/socket.h>
#include <iostream>
#include "ECS/Entity/EntityManager.h"
#include "ECS/System/SystemManager.h"
#include "Game/Common/Packet.h"
#include "Game/Manager/LoadResourceManager.h"
#include "Game/Common/Time.h"
#include "Game/Components/Transform.h"
#include "Game/Services/GameplayService.h"
#include "Game/Systems/NetworkTrackingSystem.h"

NetworkTrackingSystem networkTrackingSystem;
UDPsocket clientSocket;
UDPpacket* recvPacket;

struct TankState {
    int id;
    Packet packet;
};

void Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL haven't been initialized: " << SDL_GetError() << std::endl;
        return;
    }

    // Initialize SDL_net
    if (SDLNet_Init() < 0) {
        std::cerr << "SDL_net haven't been initialized: " << SDLNet_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image haven't been initialized: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    LoadResourceManager::getInstance()->InitWindow();
    SystemManager::getInstance()->init();
    GameplayService().LoadMap(1);
    networkTrackingSystem.init();

    // Initialize client socket
    clientSocket = SDLNet_UDP_Open(8082);
    if (!clientSocket) {
        std::cerr << "Failed to open UDP socket: " << SDLNet_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    recvPacket = SDLNet_AllocPacket(1024);
    if (!recvPacket) {
        std::cerr << "Failed to allocate packet: " << SDLNet_GetError() << std::endl;
        SDLNet_UDP_Close(clientSocket);
        SDL_Quit();
        return;
    }
}

void Update() {
    SDL_SetRenderDrawColor(LoadResourceManager::getInstance()->GetRenderer(), 0, 0, 0, 255);
    SystemManager::getInstance()->update();
    EntityManager::getInstance()->lateUpdate();
    SDL_RenderPresent(LoadResourceManager::getInstance()->GetRenderer());
    SDL_RenderClear(LoadResourceManager::getInstance()->GetRenderer());

    // Receive broadcasted state from server
    while (SDLNet_UDP_Recv(clientSocket, recvPacket)) {
        if (recvPacket->len % sizeof(TankState) != 0) {
            std::cerr << "Received packet size mismatch" << std::endl;
            break;
        }

        std::vector<TankState> receivedTankStates;
        int numPackets = recvPacket->len / sizeof(TankState);
        for (int i = 0; i < numPackets; ++i) {
            TankState receivedPacket;
            std::memcpy(&receivedPacket, recvPacket->data + i * sizeof(TankState), sizeof(TankState));
            receivedTankStates.push_back(receivedPacket);
        }

        // Print received tank states
        for (const auto& tankState : receivedTankStates) {
            std::cout << "Tank ID: " << tankState.id << std::endl;
            std::cout << "Position: (" << tankState.packet.positionX << ", " << tankState.packet.positionY << ")" << std::endl;
            std::cout << "Scale: (" << tankState.packet.scaleX << ", " << tankState.packet.scaleY << ")" << std::endl;
            std::cout << "Angle: " << tankState.packet.angle << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    Init();
    bool running = true;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 sendInterval = 1000 / 60; // 60 FPS
    Uint32 lastSendTime = SDL_GetTicks();
    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        Time::deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        Update();

        // Ensure sending data at 60 FPS
        if (currentTime - lastSendTime >= sendInterval) {
            networkTrackingSystem.update();
            lastSendTime = currentTime;
        }
        SDL_Delay(16);
    }

    LoadResourceManager::getInstance()->CleanUp();
    EntityManager::getInstance()->clearEntities();
    SDLNet_FreePacket(recvPacket);
    SDLNet_UDP_Close(clientSocket);

    return 0;
}
