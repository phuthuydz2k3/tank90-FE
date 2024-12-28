//
// Created by TCT on 10/29/2024.
//

#ifndef SINGLETONTEMPLATE_H
#define SINGLETONTEMPLATE_H

template<class T>
class SingletonTemplate {
public:
    static T *getInstance() {
        if (!instance) {
            instance = new T;
        }
        return instance;
    }

protected:
    static T *instance;

    SingletonTemplate() {
    };

    SingletonTemplate(const SingletonTemplate &) {
    };

    SingletonTemplate &operator=(const SingletonTemplate &) {
    };
};

template<typename T>
T *SingletonTemplate<T>::instance = nullptr;

#endif //SINGLETONTEMPLATE_H
