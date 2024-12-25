#ifndef NETWORKTRACKINGSYSTEM_H
#define NETWORKTRACKINGSYSTEM_H

#include <boost/asio.hpp>
#include "ECS/System/System.h"
#include "Game/Components/Transform.h"

class NetworkTrackingSystem : public System {
public:
    void update() override;
    void init() override;

private:
    static boost::asio::ip::udp::endpoint serverEndpoint;
    static boost::asio::ip::udp::socket udpSocket;
    void sendTankPosition(const Transform* transform);
};

#endif //NETWORKTRACKINGSYSTEM_H