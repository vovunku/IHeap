#include <Leftist_Heap.h>

#include<iostream>
#include <exception>

Leftist_Heap::Leftist_Heap(int value){
    _head = create_node(value);
}

Leftist_Heap::Leftist_Node * Leftist_Heap::create_node(int value) {
    Leftist_Node* result = new Leftist_Node(value);
    return result;
}

void Leftist_Heap::insert(int value){
    Leftist_Heap other(value);
    this->meld(other);
}

void Leftist_Heap::Leftist_Node::invariant() {
    if(this->left_child != nullptr && dynamic_cast<Leftist_Node*>(this->right_child)->rank > dynamic_cast<Leftist_Node*>(this->left_child)->rank){
        std::swap(this->right_child, this->left_child);
    }
    this->rank = dynamic_cast<Leftist_Node*>(this->right_child)->rank + 1;
}