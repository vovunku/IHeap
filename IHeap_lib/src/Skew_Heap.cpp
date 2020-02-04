#include <Skew_Heap.h>

#include<iostream>
#include <exception>

Skew_Heap::Skew_Heap(int value){
    _head = create_node(value);
}

Skew_Heap::Skew_Node * Skew_Heap::create_node(int value) {
    Skew_Node* result = new Skew_Node(value);
    return result;
}

void Skew_Heap::insert(int value){
    Skew_Heap other(value);
    this->meld(other);
}

void Skew_Heap::Skew_Node::invariant() {
    std::swap(this->right_child, this->left_child);
}