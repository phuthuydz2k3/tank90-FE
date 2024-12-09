//
// Created by TCT on 12/9/2024.
//
#include "Game/Components/NetworkReceiver.h"

UDPsocket NetworkReceiver::clientSocket = nullptr;
UDPpacket* NetworkReceiver::recvPacket = nullptr;