#ifndef IHEAP_LEFTIST_HEAP_H
#define IHEAP_LEFTIST_HEAP_H

#include <Proto_Oblique.h>

class Leftist_Heap : public Proto_Oblique{
public:
    Leftist_Heap() : Proto_Oblique::Proto_Oblique(){};
    Leftist_Heap(int value);
    virtual void insert(int value) override;
private:
    class Leftist_Node : public Oblique_Node{
    public:
        int rank;
        Leftist_Node(int value) : Proto_Oblique::Oblique_Node(value){rank = 0;};
        void invariant() override;
    };
protected:
    Leftist_Node* create_node(int value) override;
};

#endif //IHEAP_LEFTIST_HEAP_H
