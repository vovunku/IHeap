#ifndef IHEAP_SKEW_HEAP_H
#define IHEAP_SKEW_HEAP_H

#include <Heap_Interface.h>

class Skew_Heap : public Heap_Interface{
public:
    Skew_Heap();
    Skew_Heap(int value);
    void insert(int value) override ;
    int get_min() const override ;
    void extract_min() override ;
    void meld(Heap_Interface & other) override ;
    ~Skew_Heap();
private:
    class Skew_Node{
    public:
        int key;
        Skew_Node *left_child;
        Skew_Node *right_child;

        Skew_Node(int value);
        Skew_Node* meld(Skew_Node* other);
    };

    Skew_Node* _head;

    void _delete_tree(Skew_Node* node);
};

#endif //IHEAP_SKEW_HEAP_H
