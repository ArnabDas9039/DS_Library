#pragma once
#ifndef ARRAY_H
#define ARRAY_H

template<typename V>
class Array{
private:
    template <typename First, typename... Rest>
    void initialize(size_t index, First first, Rest... rest){
        ensure_space();
        _values[index] = first;
        initialize(index + 1, rest...);
    }
    
    void initialize(size_t index){}

protected:
    size_t _size = 0, _capacity = 8;
    V* _values = NULL;

    void ensure_space(){
        if(_size >= _capacity){
            _capacity *= 2;
            _values = (V*)realloc(_values, _capacity * sizeof(V));
        }
    }

public:
    Array() : _values(new V[_capacity]){}

    template <typename... Args>
    Array(Args... args){
        _size = sizeof...(args);
        _values = new V[_capacity];
        initialize(0, args...);
    }

    ~Array(){
        _size = 0;
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
        if(index < 0){
            return *(_values + _size + index);
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
        if(index < 0){
            return *(_values + _size + index);
        }
        return *(_values + index);
    }

    friend std::ostream& operator<<(std::ostream& os, Array<V>& arr){
        bool flag = 0;
        for(auto i : arr){
            if(!flag){
                os << "[" << i;
                flag = 1;
                continue;
            }
            os << ", " << i;
        }
        os << "]";
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
    V front() const{ return (*this)[0]; }
    V back() const{ return (*this)[_size - 1]; }

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
        _values[index] = value;
    }

    void erase(int index){
        if(empty()){
            throw std::out_of_range("Array is empty");
        }
        if(index < 0 || index >= _size){
            throw std::out_of_range("Index out of bounds");
        }
        // if(index < 0){
        //     index += _size;
        // }
        for(int i = index; i < _size; i++){
            *(_values + i) = *(_values + i + 1);
        }
        _size--;
    }

};

#endif