#pragma once
#include "Array.h"
#ifndef STACK_H
#define STACK_H

template<typename V>
class Stack : public Array<V>{
public:
    void push(V value){
        this->push_back(value);
    }

    void pop(){
        this->pop_back();
    }

    V top() const{
        return (*this)[this->size() - 1];
    }
};

#endif