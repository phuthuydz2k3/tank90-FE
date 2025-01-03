//
// Created by AnPhatPC on 26/12/2024.
//

#ifndef ACTIONSTATEPACKET_H
#define ACTIONSTATEPACKET_H

struct ActionStatePacket {
    int id;
    // 1: for out game, 2: for shooting, 3: for pause game, 4: for increase score, 5: for get leaderboard , 6: for special shooting
    int type;
    bool isShooting = false;
    bool isSpecialShooting = false;
    bool isOut = false;
    bool isPause = false;
};

#endif //ACTIONSTATEPACKET_H
