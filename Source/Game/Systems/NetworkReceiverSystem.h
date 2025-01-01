//
// Created by TCT on 12/9/2024.
//

#ifndef NETWORKRECEIVERSYSTEM_H
#define NETWORKRECEIVERSYSTEM_H

#include "ECS/System/System.h"
#include <string>

class NetworkReceiverSystem : public System{
private:
    std::string playerName;
    std::string roomName;
    std::string roomPassword;
public:
    // Constructor accepting three arguments
    NetworkReceiverSystem(const std::string& playerName, const std::string& roomName, const std::string& roomPassword);

    void update() override;
    // Modify init to accept parameters
    // Modify init to accept parameters
    using System::init; // Avoid hiding the base class init
    void init(const std::string& playerName, const std::string& roomName, const std::string& roomPassword);
};



#endif //NETWORKRECEIVERSYSTEM_H
