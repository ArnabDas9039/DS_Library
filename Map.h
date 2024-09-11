#pragma once
#include "Array.h"
#include "List.h"
#include "Pair.h"
#ifndef MAP_H
#define MAP_H

template<typename K, typename V>
class Map{
private:
    size_t _size = 0, _bucket_count = 8;
    Array<List<Pair<K, V>*>*> buckets;

    int Hash(K key){
        return std::hash<K>()(key) % _bucket_count;
        // return 0;
    }

public:
    Map(){
        // cout << "Initializing Map" << endl;
        for(size_t i = 0; i < _bucket_count; i++){
            buckets.push_back(new List<Pair<K, V>*>());
            // List<Pair<K, V>*>* bucket = new List<Pair<K, V>*>();
            // buckets[0] = new List<Pair<K, V>*>();
        }
        // cout << "Capacity: " << buckets.capacity() << endl;
    };

    ~Map(){
        delete[] & buckets;
    }

    size_t size(){ return _size; }

    V& operator[](const K& key){
        int index = Hash(key);
        // cout << "Inserting at index: " << index << endl;
        List<Pair<K, V>*>* bucket = buckets[index];

        for(Pair<K, V>* pair : *bucket){
            if(pair->first == key){
                return pair->second;
            }
        }
        Pair<K, V>* m = new Pair<K, V>(key, V());
        bucket->push_back(m);
        _size++;
        return m->second;
    }

    class Iterator {
    private:
        Array<List<Pair<K, V>*>*>& buckets;
        size_t bucketIndex;
        typename List<Pair<K, V>*>::Iterator iter;

    public:
        Iterator(Array<List<Pair<K, V>*>*>& buckets, size_t index, typename List<Pair<K, V>*>::Iterator listIt) : buckets(buckets), bucketIndex(index), iter(listIt){}

        Pair<K, V>& operator*() const{ return **iter; }
        Pair<K, V>* operator->() const{ return *iter; }

        Iterator& operator++(){
            ++iter;
            while(bucketIndex < buckets.capacity() && (buckets[bucketIndex] == NULL || iter == buckets[bucketIndex]->end())){
                bucketIndex++;
                if(bucketIndex < buckets.capacity()){
                    iter = buckets[bucketIndex]->begin();
                }
            }

            return *this;
        }

        bool operator!=(const Iterator& other) const{
            return bucketIndex != other.bucketIndex || iter != other.iter;
        }

    };

    Iterator begin(){
        for(size_t i = 0; i < _bucket_count; i++){
            if(buckets[i] != NULL && buckets[i]->begin() != buckets[i]->end()){
                return Iterator(buckets, i, buckets[i]->begin());
            }
        }
        return end();
    }

    Iterator end(){
        return Iterator(buckets, buckets.size(), typename List<Pair<K, V>*>::Iterator(NULL));
    }

    // void display(){
    //     for(auto bucket : buckets){
    //         if(bucket == NULL){
    //             continue;
    //         }
    //         for(Pair<K, V>* j : *bucket){
    //             cout << j->first << ": " << j->second << endl;
    //         }
    //     }
    //     return;
    // }

    bool empty(){
        return buckets.empty();
    }

    void insert(K key, V value){
        (*this)[key] = value;
        return;
    }

    V get_value(K key){
        int index = Hash(key);
        List<Pair<K, V>*>* bucket = buckets[index];

        for(Pair<K, V>* m : *bucket){
            if(m->first == key){
                return m->second;
            }
        }
        throw std::out_of_range("Key not found");
    }

    void erase(K key){
        int index = Hash(key);
        List<Pair<K, V>*>* bucket = buckets[index];
        for(auto i : *bucket){
            if((*i)->first == key){
                delete* i;
                bucket->erase(i);
                _size--;
            }
        }
        return;
    }

    void clear(){

    }
};

#endif