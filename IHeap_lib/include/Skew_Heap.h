#ifndef IHEAP_SKEW_HEAP_H
#define IHEAP_SKEW_HEAP_H

#include <Proto_Oblique.h>

class Skew_Heap : public Proto_Oblique{
public:
    Skew_Heap() : Proto_Oblique::Proto_Oblique(){};
    Skew_Heap(int value);
    virtual void insert(int value) override;
private:
    class Skew_Node : public Oblique_Node{
    public:
        Skew_Node(int value) : Proto_Oblique::Oblique_Node(value){};
        void invariant() override;
    };
protected:
    Skew_Node* create_node(int value) override;
};

#endif //IHEAP_SKEW_HEAP_H
