//
// Created by TCT on 10/30/2024.
//

#ifndef SYSTEM_H
#define SYSTEM_H



class System {
public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void handleInput() = 0;
    virtual void init() = 0;
    virtual void clean() = 0;
    virtual ~System() = default;
};



#endif //SYSTEM_H
