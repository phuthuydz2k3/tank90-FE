#ifndef NETWORKRECEIVER_H
#define NETWORKRECEIVER_H

#include <boost/asio.hpp>
#include "ECS/Component/Component.h"

class NetworkReceiver : public Component {
public:
    static boost::asio::ip::udp::socket clientSocket;
    static boost::asio::ip::tcp::socket tcpSocket;
    static std::vector<char> recvBuffer;
    int id = 0;
    static bool receivingEnabled;
};

#endif //NETWORKRECEIVER_H