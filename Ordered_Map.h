#pragma once
#include "Array.h"
#include "List.h"
#include "Pair.h"
#include "Tree.h"

#ifndef ORDERED_MAPS_H
#define OREDERED_MAPS_H
template<typename K, typename V >
class Ordered_Map{
private:
    size_t _size = 0;

    struct compare_Pair{
        bool operator()(Pair<K, V>* a, Pair<K, V>* b){
            return a->first < b->first;
        }
    };
    Search_Tree<Pair<K, V>*, compare_Pair > _tree;

public:

    Ordered_Map(){}

    ~Ordered_Map(){}

    size_t size(){ return _size; }

    V& operator[](const K& key){
        for(Pair<K, V>* pair : _tree){
            if(pair->first == key){
                return pair->second;
            }
        }

        Pair<K, V>* m = new Pair<K, V>(key, V());
        _tree.insert(m);
        _size++;
        return m->second;
    }

    class Iterator{
    private:
        typename Binary_Tree<Pair<K, V>*>::LevelorderIterator iter;

    public:
        Iterator(typename Binary_Tree<Pair<K, V>*>::LevelorderIterator treeIt) : iter(treeIt){}

        Pair<K, V>& operator*() const{ return **iter; }
        Pair<K, V>* operator->() const{ return *iter; }

        Iterator& operator++(){
            ++iter;
            return *this;
        }

        bool operator==(const Iterator& other) const{
            return iter == other.iter;
        }

        bool operator!=(const Iterator& other) const{
            return iter != other.iter;
        }
    };

    Iterator begin(){ return Iterator(_tree.lbegin()); }
    Iterator end(){ return Iterator(_tree.lend()); }

    // void display(){
    //     for(auto i = _tree.begin(); i != _tree.end(); ++i){
    //         cout << i->value->first << "(" << i->height << ") -> ";
    //     }
    //     cout << endl;
    // }

    void insert(K key, V value){
        (*this)[key] = value;
        return;
    }

    V get_value(K key){
        // cout << "At getvalue" << endl;

        // for(Pair<K, V>* m : *bucket){
        //     if(m->first == key){
        //         // cout << "M is: " << m->first->value << endl;
        //         return m->second;
        //     }
        // }
        throw std::out_of_range("Key not found");
    }

    void erase(K key){
        // for(auto i : *bucket){
        //     if((*i)->first == key){
        //         delete* i;
        //         bucket->erase(i);
        //         _size--;
        //     }
        // }
        return;
    }

    void clear(){}
};

#endif