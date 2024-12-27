#include <iostream>
#include <vector>
#include <cstring>
#include <deque>
#include <boost/asio.hpp>
#include "Game/Common/TankStatePacket.h"
#include <SDL2/SDL.h>

#include "Game/Common/ActionStatePacket.h"

std::vector<TankStatePacket> tankStates;
std::deque<boost::asio::ip::tcp::socket> clientSockets;
int nextId = 1;

void printPacket(const TankStatePacket& packet) {
    std::cout << "Received Packet:" << std::endl;
    std::cout << "Position: (" << packet.positionX << ", " << packet.positionY << ")" << std::endl;
    std::cout << "Angle: " << packet.angle << std::endl;
}

void handleClientOutPacket(const ActionStatePacket& packet, boost::asio::ip::tcp::socket& tcpSocket) {
    // Remove the client from tankStates
    tankStates.erase(std::remove_if(tankStates.begin(), tankStates.end(), [&](const TankStatePacket& tankState) {
        return tankState.id == packet.id;
    }), tankStates.end());

    // Remove the client from clientSockets
    clientSockets.erase(std::remove_if(clientSockets.begin(), clientSockets.end(), [&](const boost::asio::ip::tcp::socket& socket) {
     return socket.remote_endpoint() == tcpSocket.remote_endpoint();
 }), clientSockets.end());

    std::cout << "Client " << packet.id << " removed from the game." << std::endl;
}

void broadcastActionStatePacket(const ActionStatePacket& packet) {
    try {
    for (auto& socket : clientSockets) {
        boost::asio::write(socket, boost::asio::buffer(&packet, sizeof(ActionStatePacket)));
    }

    } catch (std::exception& e) {
        // std::cerr << "Exception in broadCast: " << e.what() << std::endl;
    }
}

void handleIncomingPackets(boost::asio::ip::tcp::socket& tcpSocket) {
    try {
        while (true) {
            ActionStatePacket actionPacket;
            boost::system::error_code error;
             size_t len = tcpSocket.read_some(boost::asio::buffer(&actionPacket, sizeof(ActionStatePacket)), error);

            if (error == boost::asio::error::eof) {
                break; // Connection closed cleanly by peer
            } else if (error) {
                std::cout << "Receive failed: " << error.message() << std::endl;
                // throw boost::system::system_error(error); // Some other error
                continue;
            }

            if (len == sizeof(ActionStatePacket)) {
                // Broadcast the ActionStatePacket to all clients
                if (actionPacket.type == 1 && actionPacket.isOut) {
                    handleClientOutPacket(actionPacket, tcpSocket);
                }
                broadcastActionStatePacket(actionPacket);
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in handleIncomingPackets: " << e.what() << std::endl;
    }
}

void handleClient(boost::asio::ip::tcp::socket tcpSocket) {
    try {
        // Check if the client socket already exists in clientSockets
        bool socketExists = false;
        for (const auto& socket : clientSockets) {
            if (socket.remote_endpoint() == tcpSocket.remote_endpoint()) {
                socketExists = true;
                break;
            }
        }
        std::cout << socketExists << std::endl;
        if (!socketExists) {
            // Generate a unique ID for the client
            int clientId = nextId++;

            // Send the unique ID to the client
            boost::asio::write(tcpSocket, boost::asio::buffer(&clientId, sizeof(clientId)));

            // Initialize a tank for the client
            TankStatePacket newTankState;
            newTankState.id = clientId;
            tankStates.push_back(newTankState);

            std::cout << "Assigned ID " << clientId << " to new client" << std::endl;

            // Add the client's socket to the list of client sockets
            clientSockets.push_back(std::move(tcpSocket));
            std::cout << clientSockets.size() << std::endl;
            std::thread(handleIncomingPackets, std::ref(clientSockets.back())).detach();
        } else {
            std::cout << "Client already exists" << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in handleClient: " << e.what() << std::endl;
    }
}

void updateTankState(const TankStatePacket& packet) {
    for (auto& tankState : tankStates) {
        if (tankState.id == packet.id) {
            tankState = packet;
            return;
        }
    }
    // If tank state not found, add new tank state
    tankStates.push_back(packet);
}


void broadcastTankStates(boost::asio::ip::udp::socket& socket, boost::asio::ip::udp::endpoint& broadcast_endpoint) {
    // Calculate the total size of the packet
    size_t packetSize = tankStates.size() * sizeof(TankStatePacket);
    std::vector<char> buffer(packetSize);
    std::memcpy(buffer.data(), tankStates.data(), packetSize);

    boost::system::error_code error;
    socket.send_to(boost::asio::buffer(buffer), broadcast_endpoint, 0, error);

    if (error) {
        std::cerr << "Failed to send packet: " << error.message() << std::endl;
    } else {
        for (const auto& tankState : tankStates) {
            // std::cout << "Tank ID: " << tankState.id << std::endl;
            // std::cout << "Position: (" << tankState.positionX << ", " << tankState.positionY << ")" << std::endl;
            // std::cout << "Angle: " << tankState.angle << std::endl;
            // if(tankState.isShooting) {
            //     std::cout << tankStates.size() << std::endl;
            //     std::cout << "Tank " << tankState.id << " is shooting" << std::endl;
            // }
        }
    }
}

int main(int argc, char* argv[]) {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8081));
    boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 8080));
    boost::asio::ip::udp::endpoint sender_endpoint;
    boost::asio::ip::udp::endpoint broadcast_endpoint(boost::asio::ip::address_v4::broadcast(), 8082);

    socket.set_option(boost::asio::socket_base::broadcast(true));

    std::vector<char> recv_buffer(1024);
    Uint32 lastSendTime = SDL_GetTicks();
    Uint32 sendInterval = 1000 / 60; // 60 FPS

    std::thread([&acceptor]() {
        while (true) {
            boost::asio::ip::tcp::socket tcpSocket(acceptor.get_executor());
            acceptor.accept(tcpSocket);
            std::thread(handleClient, std::move(tcpSocket)).detach();
        }
    }).detach();

    while (true) {
        boost::system::error_code error;
        size_t len = socket.receive_from(boost::asio::buffer(recv_buffer), sender_endpoint, 0, error);

        if (error && error != boost::asio::error::message_size) {
            std::cerr << "Receive failed: " << error.message() << std::endl;
            continue;
        }

        if (len > 0) {
            TankStatePacket receivedPacket;
            std::memcpy(&receivedPacket, recv_buffer.data(), sizeof(TankStatePacket));
            // printPacket(receivedPacket);

            // Update tank state
            updateTankState(receivedPacket);
        }

        Uint32 currentTime = SDL_GetTicks();
        // Broadcast tank states at 60 FPS
        if (currentTime - lastSendTime >= sendInterval) {
            broadcastTankStates(socket, broadcast_endpoint);
            lastSendTime = currentTime;
        }

        SDL_Delay(16);
    }

    return 0;
}