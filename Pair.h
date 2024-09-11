#pragma once
#ifndef PAIR_H
#define PAIR_H

template<typename K, typename V>
class Pair{
public:
    K first;
    V second;

    Pair(K key, V value) : first(key), second(value){}

    ~Pair(){}

    friend std::ostream& operator<<(std::ostream& os, const Pair<K, V>& pair){
        os << pair.first << ": " << pair.second;
    }
};

#endif