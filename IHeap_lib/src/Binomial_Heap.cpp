#include <Binomial_Heap.h>

#include <algorithm>
#include<iostream>
#include <exception>

void Binomial_Heap::_delete_tree(Binomial_Tree_Node * node) {
    if(node != nullptr){
        this->_delete_tree(node->right_sibling);
        this->_delete_tree(node->left_child);
        delete node;
    }
}

Binomial_Heap::~Binomial_Heap() {
    this->_delete_tree(_head);
}

Binomial_Heap::Binomial_Heap() {
    _head = nullptr;
    _min_element = nullptr;
}

Binomial_Heap::Binomial_Heap(int value){
    _head = new Binomial_Tree_Node(value);
    this->_min_element = _head;
}

Binomial_Heap::Binomial_Tree_Node::Binomial_Tree_Node(int value) {
    this->key = value;
    this->degree = 0;
    this->left_child = nullptr;
    this->right_sibling = nullptr;
}

void Binomial_Heap::Binomial_Tree_Node::adopt_other_node(Binomial_Heap::Binomial_Tree_Node *other) {
    if (other == nullptr) {
        throw std::invalid_argument("adopting nullptr");
    }
    if (this->left_child == nullptr) {
        this->left_child = other;
    }else{
        Binomial_Tree_Node *current;
        current = this->left_child;
        while (current->right_sibling != nullptr) {
            current = current->right_sibling;
        }
        current->right_sibling = other;
    }
    other->right_sibling = nullptr;
    this->right_sibling = nullptr;
    ++this->degree;
}

Binomial_Heap::Binomial_Tree_Node* Binomial_Heap::Binomial_Tree_Node::meld_similar_nodes(struct Binomial_Heap::Binomial_Tree_Node * other) {
    if(other == nullptr){
        throw std::invalid_argument("meld with nullptr");
    }
    if(this->key < other->key) {
        this->adopt_other_node(other);
        return this;
    }else{
        other->adopt_other_node(this);
        return other;
    }
}

void Binomial_Heap::Binomial_Tree_Node::make_other_stepbrother(Binomial_Heap::Binomial_Tree_Node *other) {
    if(other == nullptr){
        throw std::invalid_argument("making nullptr step-brother");
    }
    this->right_sibling = other;
}

void Binomial_Heap::_add_heap_to_root_list(Binomial_Heap &other) {
    Binomial_Tree_Node dummy_head(0);
    Binomial_Tree_Node *iterator = &dummy_head;
    Binomial_Tree_Node *current_position_in_this;
    current_position_in_this = this->_head;
    Binomial_Tree_Node *current_position_in_other;
    current_position_in_other = other._head;

    while(current_position_in_this != nullptr && current_position_in_other != nullptr){
        if(current_position_in_this->degree > current_position_in_other->degree){
            iterator->make_other_stepbrother(current_position_in_other);
            current_position_in_other = current_position_in_other->right_sibling;
        }else{
            iterator->make_other_stepbrother(current_position_in_this);
            current_position_in_this = current_position_in_this->right_sibling;
        }
        iterator = iterator->right_sibling;
    }

    if(current_position_in_this != nullptr){
        iterator->make_other_stepbrother(current_position_in_this);
    }else if(current_position_in_other != nullptr){
        iterator->make_other_stepbrother(current_position_in_other);
    }

    this->_head = dummy_head.right_sibling;
}

void Binomial_Heap::_normalizing() {
    Binomial_Tree_Node dummy_head(0);
    dummy_head.right_sibling = this->_head;
    Binomial_Tree_Node *current_parent = &dummy_head;
    Binomial_Tree_Node *current = this->_head;
    Binomial_Tree_Node *current_double_sibling;
    while(current->right_sibling != nullptr){
        current_double_sibling = current->right_sibling->right_sibling;
        if(current->degree == current->right_sibling->degree){
            current_parent->right_sibling = current->meld_similar_nodes(current->right_sibling);
            current_parent->right_sibling->right_sibling = current_double_sibling;
            current = current_parent->right_sibling;
            continue;
        }
        current_parent = current;
        current = current->right_sibling;
    }
    this->_head = dummy_head.right_sibling;
}

void Binomial_Heap::meld(Heap_Interface & other) {
    Binomial_Heap& other_bin = dynamic_cast<Binomial_Heap&>(other);
    if(other_bin._head == nullptr){
        return;
    }
    //merging
    this->_add_heap_to_root_list(other_bin);
    //normalizing
    this->_normalizing();

    other_bin._head = nullptr;
    (*this)._renew_min();
}

void Binomial_Heap::insert(int value) {
    Binomial_Heap other(value);
    this->meld(other);
    _renew_min();
}

int Binomial_Heap::get_min() const{
    if(this->_min_element != nullptr){
        return this->_min_element->key;
    }else{
        throw std::logic_error("nothing to get");
    }
}

void Binomial_Heap::extract_min() {
    if(_min_element == nullptr){
        throw std::logic_error("nothing to extract");
    }
    if(this->_head != this->_min_element){
        Binomial_Tree_Node* previous = this->_head;
        while(previous->right_sibling != _min_element){
            previous = previous->right_sibling;
        }
        previous->right_sibling = _min_element->right_sibling;
    }else{
        _head = _min_element->right_sibling;
    }
    Binomial_Heap other;
    other._head = _min_element->left_child;
    delete _min_element;
    (*this).meld(other);
    (*this)._renew_min();
}

Binomial_Heap::Binomial_Tree_Node *Binomial_Heap::_find_min() {
    Binomial_Tree_Node* current_node = _head;
    Binomial_Tree_Node* min_element = _head;
    while(current_node != nullptr){
        if(current_node->key < min_element->key){
            min_element = current_node;
        }
        current_node = current_node->right_sibling;
    }
    return min_element;
}

void Binomial_Heap::_renew_min() {
    _min_element = (*this)._find_min();
}
