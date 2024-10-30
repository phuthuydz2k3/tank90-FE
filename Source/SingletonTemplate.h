//
// Created by TCT on 10/29/2024.
//

#ifndef SINGLETONTEMPLATE_H
#define SINGLETONTEMPLATE_H
#include <cstddef>


template<typename T>
class SingletonTemplate {
    using entity = std::size_t;
private:
    static std::unique_ptr<T> instance;

public:
    SingletonTemplate() {
    };

    SingletonTemplate(const SingletonTemplate &) {
    };

    SingletonTemplate &operator=(const SingletonTemplate &) {
    };

    static T &getInstance() {
        if (!instance) {
            instance = new T();
        }
        return *instance;
    }
};

#endif //SINGLETONTEMPLATE_H
