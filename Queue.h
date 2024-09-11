#pragma once
#include "Array.h"
#ifndef QUEUE_H
#define QUEUE_H

template<typename V>
class Queue : public Array<V>{
public:
    void push(V value){
        this->push_back(value);
    }
    void pop(){
        if(this->_size == 0){
            throw std::out_of_range("Array is empty");
        }
        for(int i = 0; i < this->_size; i++){
            this->_values[i] = this->_values[i + 1];
        }
        this->_size--;
        return;
    }
};

#endif