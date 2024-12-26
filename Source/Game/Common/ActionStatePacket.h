//
// Created by AnPhatPC on 26/12/2024.
//

#ifndef ACTIONSTATEPACKET_H
#define ACTIONSTATEPACKET_H

struct ActionStatePacket {
    int id;
    // 1: for out game, 2: for shooting, 3: for pause game
    int type;
    bool isShooting = false;
    bool isOut = false;
    bool isPause = false;
};

#endif //ACTIONSTATEPACKET_H
