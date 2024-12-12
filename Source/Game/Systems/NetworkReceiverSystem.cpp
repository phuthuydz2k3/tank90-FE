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
            std::memcpy(&receivedPacket, NetworkReceiver::recvBuffer.data() + i * sizeof(TankStatePacket), sizeof(TankStatePacket));
            receivedTankStates.push_back(receivedPacket);
        }

        // Print received tank states
        for (const auto &tankState: receivedTankStates) {
            std::cout << "Tank ID: " << tankState.id << std::endl;
            std::cout << "Position: (" << tankState.positionX << ", " << tankState.positionY << ")" << std::endl;
            std::cout << "Angle: " << tankState.angle << std::endl;
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
    NetworkReceiver::id = uniqueId;

    std::cout << "Received unique ID: " << NetworkReceiver::id << std::endl;
}