// Source/Game/Components/NetworkReceiver.cpp
#include "Game/Components/NetworkReceiver.h"

boost::asio::io_context io_context1;
boost::asio::io_context io_context5;
boost::asio::ip::tcp::socket NetworkReceiver::tcpSocket(io_context5);
boost::asio::ip::udp::socket NetworkReceiver::clientSocket(io_context1);
std::vector<char> NetworkReceiver::recvBuffer(1024); // Define recvBuffer here