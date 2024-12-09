//
// Created by TCT on 12/9/2024.
//

#ifndef NETWORKRECEIVER_H
#define NETWORKRECEIVER_H

#include <SDL_net.h>

#include "ECS/Component/Component.h"

class NetworkReceiver : public Component {
public:
    static  UDPsocket clientSocket;
    static  UDPpacket* recvPacket;
};



#endif //NETWORKRECEIVER_H
