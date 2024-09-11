#pragma once
#ifndef LIST_H
#define LIST_H

template<typename V>
class List{
private:
    class Node{
    public:
        V _value;
        Node* next;
        Node* prev;

        Node(V value, Node* nextNode = NULL, Node* prevNode = NULL) : _value(value), next(nextNode), prev(prevNode){}

        ~Node(){}
    };

    size_t _size = 0;
    Node* _front = NULL;
    Node* _back = NULL;

public:

    List() = default;

    ~List(){ clear(); }

    size_t size(){ return _size; }

    bool empty(){return _size == 0;}
    V front() const{
        if(empty()){
            throw std::out_of_range("List is empty");
        }
        return _front->_value;
    }
    V back() const{
        if(empty()){
            throw std::out_of_range("List is empty");
        }
        return _back->_value;
    }

    class Iterator{
    private:
        Node* _ptr;

    public:
        Iterator(Node* ptr) : _ptr(ptr){}

        V& operator*() const{ return _ptr->_value; }
        V* operator->() const{ return &(_ptr->_value); }

        Iterator& operator++(){
            _ptr = _ptr->next;
            return *this;
        }

        bool operator==(const Iterator& other) const{
            return _ptr == other._ptr;
        }

        bool operator!=(const Iterator& other) const{
            return _ptr != other._ptr;
        }

    };

    Iterator begin(){ return Iterator(_front); }
    Iterator end(){ return Iterator(NULL); }

    class ReverseIterator{
    private:
        Node* _ptr;

    public:
        ReverseIterator(Node* ptr) : _ptr(ptr){}

        V& operator*() const{ return _ptr->_value; }
        V* operator->() const{ return &(_ptr->_value); }

        ReverseIterator& operator++(){
            _ptr = _ptr->next;
            return *this;
        }
        bool operator!=(const ReverseIterator& other) const{
            return _ptr != other._ptr;
        }

    };

    ReverseIterator rbegin(){ return ReverseIterator(_back); }
    ReverseIterator rend(){ return ReverseIterator(NULL); }

    // void display(){
    //     for(Node* i = _front; i != NULL; i = i->next){
    //         cout << i->_value << " ";
    //     }
    //     cout << endl;
    // }

    void push_back(V value){
        Node* n = new Node(value, NULL, _back);
        // cout << "At pushback" << endl;
        if(_front == NULL){
            _front = n;
            _back = n;
            // cout << "First node entered" << endl;
        }
        else{
            _back->next = n;
            _back = n;
            // cout << "More node entered" << endl;
        }
        _size++;
    }

    void push_front(V value){
        Node* n = new Node(value, _front, NULL);

        if(_back == NULL){
            _front = n;
            _back = n;
        }
        else{
            _front->prev = n;
            _front = n;
        }
        _size++;
    }

    void pop_back(){
        if(_size == 0){
            throw std::out_of_range("List is empty");
        }
        Node* del = _back;
        _back = _back->prev;
        if(_back) _back->next = NULL;
        else _front = NULL;
        delete del;
        _size--;
    }

    void pop_front(){
        if(_size == 0){
            throw std::out_of_range("List is empty");
        }
        Node* del = _front;
        _front = _front->next;
        if(_front) _front->prev = NULL;
        else _back = NULL;
        delete del;
        _size--;
    }

    void insert(V value, int index){
        if(index < 0 || index > _size){
            throw std::out_of_range("Index out of bounds");
        }
        if(index == 0){
            push_front(value);
        }
        else if(index == _size){
            push_back(value);
        }
        else{
            Node* s = _front;
            for(int i = 1; i < index; i++){
                s = s->next;
            }

            Node* n = new Node(value, s->next, s);
            s->next->prev = n;
            s->next = n;
            _size++;
        }
    }

    void erase(int index){
        if(empty()){
            throw std::out_of_range("List is empty");
        }
        if(index < 0 || index >= _size){
            throw std::out_of_range("Index out of bounds");
        }
        if(index == 0){
            pop_front();
        }
        else if(index == _size - 1){
            pop_back();
        }
        else{
            Node* s = _front;
            for(int i = 1; i < index; i++){
                s = s->next;
            }

            Node* del = s->next;
            s->next = del->next;
            s->next->prev = s;
            _size--;
        }
    }

    void clear(){
        while(!empty()){
            pop_front();
        }
    }
};

#endif