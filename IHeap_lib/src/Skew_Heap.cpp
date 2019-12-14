#include <Skew_Heap.h>

#include<iostream>
#include <exception>

Skew_Heap::Skew_Node::Skew_Node(int value){
    key = value;
    left_child = nullptr;
    right_child = nullptr;
}

Skew_Heap::Skew_Heap(){
    _head = nullptr;
}

Skew_Heap::Skew_Heap(int value){
    _head = new Skew_Node(value);
}

void Skew_Heap::_delete_tree(Skew_Node* node){
    if(node != nullptr){
        _delete_tree(node->left_child);
        _delete_tree(node->right_child);
        delete node;
    }
}

Skew_Heap::~Skew_Heap(){
    _delete_tree(_head);
}

Skew_Heap::Skew_Node* Skew_Heap::Skew_Node::meld(Skew_Node* right){
    if(right == nullptr){
        return this;
    }else if(this == nullptr){
        return right;
    }
    Skew_Node *left = this;
    if(left->key > right->key){
        std::swap(left, right);
    }
    left->right_child = left->right_child->meld(right);
    std::swap(left->right_child, left->left_child);
    return left;
}

void Skew_Heap::meld(Heap_Interface& other){
    Skew_Heap& other_Skew = dynamic_cast<Skew_Heap&> (other);
    if(other_Skew._head == nullptr){
        return;
    }else if(this->_head == nullptr){
        this->_head = other_Skew._head;
        other_Skew._head = nullptr;
        return;
    }
    this->_head = this->_head->meld(other_Skew._head);
    other_Skew._head = nullptr;
}

void Skew_Heap::insert(int value) {
    Skew_Heap other(value);
    this->meld(other);
}

int Skew_Heap::get_min() const{
    if(this->_head == nullptr){
        throw std::logic_error("nothing to get");
    }
    return this->_head->key;
}

void Skew_Heap::extract_min() {
    if(this->_head == nullptr){
        throw std::logic_error("nothing to extract");
    }
    Skew_Node* min_element = this->_head;
    this->_head = min_element->left_child->meld(min_element->right_child);
    delete min_element;
}
