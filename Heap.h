#pragma once
#include "Array.h"
#include<functional>
#ifndef HEAP_H
#define HEAP_H

template<typename V, typename C = std::less<V> >
class Heap : public Array<V>{
public:
    C compare;

    int get_leftchild_index(int parent_index){ return (2 * parent_index) + 1; }
    int get_rightchild_index(int parent_index){ return (2 * parent_index) + 2; }
    int get_parent_index(int child_index){ return (child_index - 1) / 2; }

    bool has_leftchild(int index){ return get_leftchild_index(index) < this->size(); }
    bool has_rightchild(int index){ return get_rightchild_index(index) < this->size(); }
    bool has_parent(int index){ return get_parent_index(index) >= 0; }

    V leftchild(int index){ return *(this->_values + get_leftchild_index(index)); }
    V rightchild(int index){ return *(this->_values + get_rightchild_index(index)); }
    V parent(int index){ return *(this->_values + get_parent_index(index)); }

    void peek(){
        // cout << "Front is: " << *this->_values << endl;
        return;
    }

    void push(V value){
        this->push_back(value);
        // cout << "Size is: " << this->size() << endl;
        heapify_up();
    }

    void pop(){
        // cout << "At pop" << endl;
        *this->_values = *(this->_values + this->_size - 1);
        this->pop_back();
        heapify_down();
    }

    void heapify_up(){
        // cout << "At Heapify Up" << endl;
        int index = this->size() - 1;
        // cout << "Size: " << this->size() << " Index: " << index << endl;

        while(has_parent(index) && compare(*(this->_values + index), parent(index))){
            // while(has_parent(index) && *(this->_values + index) < parent(index)){
            // cout << "Heapifying Up" << endl;
            V temp = *(this->_values + get_parent_index(index));
            *(this->_values + get_parent_index(index)) = *(this->_values + index);
            *(this->_values + index) = temp;
            // swap(this[get_parent_index(index)], this[index]);
            index = get_parent_index(index);
        }
    }

    void heapify_down(){
        // cout << "At Heapify Down" << endl;
        int index = 0;
        // cout << "Size: " << this->size() << " Index: " << index << endl;

        while(has_leftchild(index)){
            int smaller_child_index = get_leftchild_index(index);

            if(has_rightchild(index) && compare(rightchild(index), leftchild(index))){
                // if(has_rightchild(index) && rightchild(index) < leftchild(index)){
                smaller_child_index = get_rightchild_index(index);
            }

            if(compare(*(this->_values + index), *(this->_values + smaller_child_index))){
                // if(*(this->_values + index) < *(this->_values + smaller_child_index)){
                break;
            }
            else{
                // cout << "Heapifying Down" << endl;
                V temp = *(this->_values + index);
                *(this->_values + index) = *(this->_values + smaller_child_index);
                *(this->_values + smaller_child_index) = temp;
                // swap(this[index], this[smaller_child_index]);
            }

            index = smaller_child_index;
        }
    }
};

#endif