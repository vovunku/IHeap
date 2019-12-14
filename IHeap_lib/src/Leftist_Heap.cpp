#include <Leftist_Heap.h>

#include<iostream>
#include <exception>

Leftist_Heap::Leftist_Node::Leftist_Node(int value){
    key = value;
    left_child = nullptr;
    right_child = nullptr;
    rank = 0;
}

Leftist_Heap::Leftist_Heap(){
    _head = nullptr;
}

Leftist_Heap::Leftist_Heap(int value){
    _head = new Leftist_Node(value);
}

void Leftist_Heap::_delete_tree(Leftist_Node* node){
    if(node != nullptr){
        _delete_tree(node->left_child);
        _delete_tree(node->right_child);
        delete node;
    }
}

Leftist_Heap::~Leftist_Heap(){
    _delete_tree(_head);
}

Leftist_Heap::Leftist_Node* Leftist_Heap::Leftist_Node::meld(Leftist_Node* right){
    if(right == nullptr){
        return this;
    }else if(this == nullptr){
        return right;
    }
    Leftist_Node *left = this;
    if(left->key > right->key){
        std::swap(left, right);
    }
    left->right_child = left->right_child->meld(right);
    if(left->left_child != nullptr && left->right_child->rank > left->left_child->rank){
        std::swap(left->right_child, left->left_child);
    }
    left->rank = left->right_child->rank + 1;
    return left;
}

void Leftist_Heap::meld(Heap_Interface& other){
    Leftist_Heap& other_leftist = dynamic_cast<Leftist_Heap&> (other);
    if(other_leftist._head == nullptr){
        return;
    }else if(this->_head == nullptr){
        this->_head = other_leftist._head;
        other_leftist._head = nullptr;
        return;
    }
    this->_head = this->_head->meld(other_leftist._head);
    other_leftist._head = nullptr;
}

void Leftist_Heap::insert(int value) {
    Leftist_Heap other(value);
    this->meld(other);
}

int Leftist_Heap::get_min() const{
    if(this->_head == nullptr){
        throw std::logic_error("nothing to get");
    }
    return this->_head->key;
}

void Leftist_Heap::extract_min() {
    if(this->_head == nullptr){
        throw std::logic_error("nothing to extract");
    }
    Leftist_Node* min_element = this->_head;
    this->_head = min_element->left_child->meld(min_element->right_child);
    delete min_element;
}