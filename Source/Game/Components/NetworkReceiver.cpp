// Source/Game/Components/NetworkReceiver.cpp
#include "Game/Components/NetworkReceiver.h"

boost::asio::io_context io_context1;
boost::asio::ip::udp::socket NetworkReceiver::clientSocket(io_context1);
std::vector<char> NetworkReceiver::recvBuffer(1024); // Define recvBuffer here