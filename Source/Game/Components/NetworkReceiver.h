#ifndef NETWORKRECEIVER_H
#define NETWORKRECEIVER_H

#include <boost/asio.hpp>
#include "ECS/Component/Component.h"

class NetworkReceiver : public Component {
public:
    static boost::asio::ip::udp::socket clientSocket;
    static std::vector<char> recvBuffer;
    int id = 0;
};

#endif //NETWORKRECEIVER_H