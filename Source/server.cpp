#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <iostream>

int main(int argc, char *argv[]) {
    // Initialize SDL_net
    if (SDLNet_Init() < 0) {
        std::cerr << "SDL_net hasn't been initialized: " << SDLNet_GetError() << std::endl;
        return 1;
    }

    // Open a UDP socket
    UDPsocket socket = SDLNet_UDP_Open(12345);
    if (!socket) {
        std::cerr << "Failed to open UDP socket: " << SDLNet_GetError() << std::endl;
        SDLNet_Quit();
        return 1;
    }

    // Allocate memory for the packet
    UDPpacket *packet = SDLNet_AllocPacket(512);
    if (!packet) {
        std::cerr << "Failed to allocate packet: " << SDLNet_GetError() << std::endl;
        SDLNet_UDP_Close(socket);
        SDLNet_Quit();
        return 1;
    }

    std::cout << "Server is listening on port 12345..." << std::endl;

    // Server loop
    while (true) {
        // Wait for incoming packets
        if (SDLNet_UDP_Recv(socket, packet)) {
            std::string receivedData(reinterpret_cast<char*>(packet->data));
            std::cout << "Received position: " << receivedData << std::endl;
        }

        // Delay to prevent high CPU usage
        SDL_Delay(16);
    }

    // Clean up
    SDLNet_FreePacket(packet);
    SDLNet_UDP_Close(socket);
    SDLNet_Quit();

    return 0;
}