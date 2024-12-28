//
// Created by TCT on 12/26/2024.
//

#ifndef UIUNIT_H
#define UIUNIT_H
#include <vector>


class UIUnit {
public:
    std::vector<int> idEntities;
    virtual void Init();
    virtual void Close();
};


#endif //UIUNIT_H
