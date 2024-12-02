//
// Created by AnPhatPC on 26/11/2024.
//

#ifndef NETWORKTRACKINGSYSTEM_H
#define NETWORKTRACKINGSYSTEM_H
#include <SDL_net.h>

#include "ECS/System/System.h"
#include "Game/Components/Transform.h"


class NetworkTrackingSystem : public System{
public:
    void update() override;
    void init() override;

private:
    static IPaddress serverAddress;
    static UDPsocket udpSocket;
    void sendTankPosition(const Transform* transform);
};



#endif //NETWORKTRACKINGSYSTEM_H
