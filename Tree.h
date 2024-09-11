#pragma once
#include<functional>
#include "Stack.h"
#include "Queue.h"
#include "Map.h"

#ifndef TREE_H
#define TREE_H
template<typename V>
class Binary_Tree{
private:

protected:
    class Leaf{
    public:
        V _value;
        Leaf* left;
        Leaf* right;
        int _height = 0;

        Leaf(V value, Leaf* leftchild = NULL, Leaf* rightchild = NULL) : _value(value), left(leftchild), right(rightchild){}

        ~Leaf(){}
    };

    size_t _size = 0;

public:
    Leaf* _root = NULL;
    Binary_Tree() = default;

    ~Binary_Tree(){}

    size_t size(){ return _size; }

    V getRoot(){
        if(_root == NULL){
            throw std::out_of_range("Root is NULL");
        }
        return _root->_value;
    }

    class InorderIterator{
    private:
        Leaf* _ptr;
        Stack<Leaf*> StackFrontier;

    public:
        InorderIterator(Leaf* ptr) : _ptr(ptr){
            StackFrontier.push(_ptr);
        }

        V& operator*() const{
            if(!StackFrontier.empty()){
                return StackFrontier.top()->_value;
            }
            else{
                throw std::out_of_range("Iterator points to empty stack");
            }
        }
        V* operator->() const{
            if(!StackFrontier.empty()){
                return &(StackFrontier.top()->_value);
            }
            else{
                return NULL;
            }
        }

        InorderIterator& operator++(){
            if(!StackFrontier.empty()){
                Leaf* value = StackFrontier.top();
                StackFrontier.pop();

                if(value->right != NULL){
                    StackFrontier.push(value->right);
                }
                if(value->left != NULL){
                    StackFrontier.push(value->left);
                }
            }
            return *this;
        }

        bool operator==(const InorderIterator& other) const{
            return StackFrontier.top() == other.StackFrontier.top();
        }

        bool operator!=(const InorderIterator& other) const{
            if(StackFrontier.empty() || other.StackFrontier.empty()){
                return false;
            }
            return !(*this == other);
        }
    };

    InorderIterator begin(){ return InorderIterator(_root); }
    InorderIterator end(){ return InorderIterator(NULL); }

    class LevelorderIterator{
    private:
        Leaf* _ptr;
        Queue<Leaf*> QueueFrontier;

    public:
        LevelorderIterator(Leaf* ptr) : _ptr(ptr){
            QueueFrontier.push(_ptr);
        }

        V& operator*() const{ return QueueFrontier.front()->_value; }
        V* operator->() const{ return QueueFrontier.front()->_value; }

        LevelorderIterator& operator++(){
            if(!QueueFrontier.empty()){
                Leaf* value = QueueFrontier.front();
                QueueFrontier.pop();

                if(value->left != NULL){
                    QueueFrontier.push(value->left);
                }
                if(value->right != NULL){
                    QueueFrontier.push(value->right);
                }
            }
            return *this;
        }

        bool operator==(const LevelorderIterator& other) const{
            return QueueFrontier.front() == other.QueueFrontier.front();
        }
        bool operator!=(const LevelorderIterator& other) const{
            if(QueueFrontier.empty() || other.QueueFrontier.empty()){
                return false;
            }
            return !(*this == other);
        }
    };

    LevelorderIterator lbegin(){ return LevelorderIterator(_root); }
    LevelorderIterator lend(){ return LevelorderIterator(NULL); }

    void insert(V value){
        Leaf* node = new Leaf(value);
        if(_root == NULL){
            _root = node;
        }
        else{
            Queue<Leaf*> QueueFrontier;

            QueueFrontier.push(_root);
            while(!QueueFrontier.empty()){
                Leaf* value = QueueFrontier.front();
                QueueFrontier.pop();

                if(value->left != NULL)
                    QueueFrontier.push(value->left);
                else{
                    value->left = node;
                    return;
                }

                if(value->right != NULL)
                    QueueFrontier.push(value->right);
                else{
                    value->right = node;
                    return;
                }
            }
        }
    }
};

template<typename V, typename C = std::less<V> >
class Search_Tree : public Binary_Tree<V>{
private:

public:
    ~Search_Tree(){}

    C compare;

    void updateParentChild(typename Binary_Tree<V>::Leaf* parent, typename Binary_Tree<V>::Leaf* oldChild, typename Binary_Tree<V>::Leaf* newChild){
        if(parent == NULL){
            this->_root = newChild;
        }
        else if(parent->left == oldChild){
            parent->left = newChild;
        }
        else if(parent->right == oldChild){
            parent->right = newChild;
        }
    }

    int getHeight(typename Binary_Tree<V>::Leaf* node){
        if(node == NULL){
            return 0;
        }
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    typename Binary_Tree<V>::Leaf* rebalanceTree(typename Binary_Tree<V>::Leaf* node, V value, typename Binary_Tree<V>::Leaf* parent){
        int balance = getBF(node);

        // Left Left Case
        if(balance > 1 && compare(value, node->left->_value)){
            node = rightRotate(node);
        }
        // Right Right Case
        else if(balance < -1 && compare(node->right->_value, value)){
            node = leftRotate(node);
        }
        // Left Right Case
        else if(balance > 1 && compare(node->left->_value, value)){
            node->left = leftRotate(node->left);
            node = rightRotate(node);
        }
        // Right Left Case
        else if(balance < -1 && compare(value, node->right->_value)){
            node->right = rightRotate(node->right);
            node = leftRotate(node);
        }

        // Update parent's child pointer to the new subtree root
        if(parent == NULL){
            this->_root = node;  // If no parent, then node is the new root
        }
        else if(parent->left == node || (parent->left && compare(node->_value, parent->left->_value))){
            parent->left = node;
        }
        else{
            parent->right = node;
        }

        return node;
    }

    int getBF(typename Binary_Tree<V>::Leaf* node){
        return (node == NULL) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    typename Binary_Tree<V>::Leaf* leftRotate(typename Binary_Tree<V>::Leaf* ptr){
        // cout << "Left Rotate" << endl;
        typename Binary_Tree<V>::Leaf* rt = ptr->right;
        typename Binary_Tree<V>::Leaf* lst = rt->left;

        rt->left = ptr;
        ptr->right = lst;

        return rt;
    }

    typename Binary_Tree<V>::Leaf* rightRotate(typename Binary_Tree<V>::Leaf* ptr){
        // cout << "Right Rotate" << endl;
        typename Binary_Tree<V>::Leaf* lt = ptr->left;
        typename Binary_Tree<V>::Leaf* rst = lt->right;

        lt->right = ptr;
        ptr->left = rst;

        return lt;
    }

    void insert(V value){
        typename Binary_Tree<V>::Leaf* node = new typename Binary_Tree<V>::Leaf(value);
        // cout << "Inserting value: " << value;

        if(this->_root == NULL){
            this->_root = node;
            // updateHeight(node);
        }
        else{
            Stack<typename Binary_Tree<V>::Leaf*> StackFrontier;
            Map<typename Binary_Tree<V>::Leaf*, bool> visit;

            StackFrontier.push(this->_root);
            while(!StackFrontier.empty()){
                typename Binary_Tree<V>::Leaf* parent = StackFrontier.top();

                if(visit[parent]){
                    StackFrontier.pop();
                    parent->_height = getHeight(parent);
                    parent = rebalanceTree(parent, value, (StackFrontier.empty() ? NULL : StackFrontier.top()));
                    continue;
                }

                visit[parent] = true;

                if(compare(value, parent->_value)){
                    // Go left
                    if(parent->left != NULL){
                        StackFrontier.push(parent->left);
                    }
                    else{
                        parent->left = node;
                        break;
                    }
                }
                else{
                    // Go right
                    if(parent->right != NULL){
                        StackFrontier.push(parent->right);
                    }
                    else{
                        parent->right = node;
                        break;
                    }
                }
            }

            while(!StackFrontier.empty()){
                typename Binary_Tree<V>::Leaf* parent = StackFrontier.top();
                StackFrontier.pop();
                parent->_height = getHeight(parent);
                parent = rebalanceTree(parent, value, (StackFrontier.empty() ? NULL : StackFrontier.top()));
            }
        }
        return;
    }

    // void display(Leaf* parent){
    //     if(parent == NULL){
    //         cout << "(-1) -> ";
    //         return;
    //     }
    //     cout << parent->value << "(" << parent->height << ") -> ";
    //     display(parent->left);
    //     display(parent->right);
    // }

};
#endif