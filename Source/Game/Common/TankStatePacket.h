//
// Created by AnPhatPC on 01/12/2024.
//

#ifndef PACKET_H
#define PACKET_H

struct TankStatePacket {
    int id;
    float positionX;
    float positionY;
    float angle;
    bool isShooting = false;
    bool isDie;
};

#endif //PACKET_H
