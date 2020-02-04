#include <Proto_Oblique.h>

#include<iostream>
#include <exception>

Proto_Oblique::Oblique_Node::Oblique_Node(int value){
    key = value;
    left_child = nullptr;
    right_child = nullptr;
}

Proto_Oblique::Proto_Oblique(){
    _head = nullptr;
}

void Proto_Oblique::_delete_tree(Oblique_Node* node){
    if(node != nullptr){
        _delete_tree(node->left_child);
        _delete_tree(node->right_child);
        delete node;
    }
}

Proto_Oblique::~Proto_Oblique(){
    _delete_tree(_head);
}

Proto_Oblique::Oblique_Node* Proto_Oblique::Oblique_Node::meld(Oblique_Node* right){
    if(right == nullptr){
        return this;
    }else if(this == nullptr){
        return right;
    }
    Oblique_Node *left = this;
    if(left->key > right->key){
        std::swap(left, right);
    }
    left->right_child = left->right_child->meld(right);
    left->invariant();
    return left;
}

void Proto_Oblique::meld(Heap_Interface& other){
    Proto_Oblique& other_Skew = dynamic_cast<Proto_Oblique&> (other);
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

int Proto_Oblique::get_min() const{
    if(this->_head == nullptr){
        throw std::logic_error("nothing to get");
    }
    return this->_head->key;
}

void Proto_Oblique::extract_min() {
    if(this->_head == nullptr){
        throw std::logic_error("nothing to extract");
    }
    Oblique_Node* min_element = this->_head;
    this->_head = min_element->left_child->meld(min_element->right_child);
    delete min_element;
}
