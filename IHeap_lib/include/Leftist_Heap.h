#ifndef IHEAP_LEFTIST_HEAP_H
#define IHEAP_LEFTIST_HEAP_H

#include <Heap_Interface.h>

class Leftist_Heap : public Heap_Interface{
public:
    Leftist_Heap();
    Leftist_Heap(int value);
    void insert(int value) override ;
    int get_min() const override ;
    void extract_min() override ;
    void meld(Heap_Interface & other) override ;
    ~Leftist_Heap();
private:
    class Leftist_Node{
    public:
        int key;
        int rank;
        Leftist_Node *left_child;
        Leftist_Node *right_child;

        Leftist_Node(int value);
        Leftist_Node* meld(Leftist_Node* other);
    };

    Leftist_Node* _head;

    void _delete_tree(Leftist_Node* node);
};

#endif //IHEAP_LEFTIST_HEAP_H
