//
// Created by TCT on 10/30/2024.
//

#ifndef SYSTEM_H
#define SYSTEM_H



class System {
public:
    virtual void update();
    virtual void init();
    virtual void clean();
    virtual ~System() = default;
};



#endif //SYSTEM_H
