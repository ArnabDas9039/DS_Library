#pragma once
#ifndef ARRAY_H
#define ARRAY_H

template<typename V>
class Array{
private:

protected:
    size_t _size = 0, _capacity = 8;
    V* _values = NULL;

    void ensure_space(){
        if(_size >= _capacity){
            _capacity = ((_size / 8) + 1) * 8;
            V* new_values = new V[_capacity];
            for(size_t i = 0; i < _size; ++i){
                new_values[i] = std::move(_values[i]);
            }
            delete[] _values;
            _values = new_values;
        }
    }

public:
    Array() : _values(new V[_capacity]){}

    Array(size_t size) : _size(size), _capacity(size >= _capacity ? ((size / 8) + 1) * 8 : 8), _values(new V[_capacity]){
        for(size_t i = 0; i < _size; ++i){
            _values[i] = V();
        }
    }

    ~Array(){
        delete[] _values;
    }

    size_t size(){ return _size; }
    size_t size() const{ return _size; }
    size_t capacity(){ return _capacity; }

    V& operator[](int index){
        if(_size == 0){
            throw std::out_of_range("Array is empty");
        }
        if(index < 0 || index >= _size){
            throw std::out_of_range("Index out of bounds");
        }
        return *(_values + index);
    }
    V& operator[](int index) const{
        if(_size == 0){
            throw std::out_of_range("Array is empty");
        }
        if(index < 0 || index >= _size){
            throw std::out_of_range("Index out of bounds");
        }
        return *(_values + index);
    }

    friend std::ostream& operator<<(std::ostream& os, Array<V>& arr){
        if(arr.empty()){
            os << "[]";
            return os;
        }
        os << "[";
        for(size_t i = 0; i < arr._size; ++i){
            os << arr._values[i];
            if(i < arr._size - 1) os << ", ";
        }
        os << "]";
        return os;
    }

    class Iterator {
    private:
        V* _ptr;

    public:
        Iterator(V* ptr) : _ptr(ptr){}

        V& operator*() const{ return *_ptr; }

        Iterator& operator++(){
            _ptr++;
            return *this;
        }

        bool operator==(const Iterator& other) const{
            return _ptr == other._ptr;
        }

        bool operator!=(const Iterator& other) const{
            return _ptr != other._ptr;
        }

    };

    Iterator begin(){ return Iterator(_values); }
    Iterator end(){ return Iterator(_values + _size); }

    bool empty() const{ return _size == 0; }

    V at(int index) const{ return (*this)[index]; }
    V front() const{
        if(empty()){
            throw std::out_of_range("Array is empty");
        }
        return (*this)[0];
    }
    V back() const{
        if(empty()){
            throw std::out_of_range("Array is empty");
        }return (*this)[_size - 1];
    }

    void push_back(V value){
        ensure_space();
        _values[_size] = value;
        _size++;
        return;
    }

    void pop_back(){
        if(empty()){
            throw std::out_of_range("Array is empty");
        }
        _size--;
    }

    void insert(V value, int index){
        if(index < 0 || index > _size){
            throw std::out_of_range("Index out of bounds");
        }
        ensure_space();
        for(int i = _size; i > index; --i){
            _values[i] = _values[i - 1];
        }
        _values[index] = value;
        _size++;
    }

    void erase(int index){
        if(empty()){
            throw std::out_of_range("Array is empty");
        }
        if(index < 0 || index >= _size){
            throw std::out_of_range("Index out of bounds");
        }
        for(int i = index; i < _size; i++){
            *(_values + i) = *(_values + i + 1);
        }
        _size--;
    }

};

#endif