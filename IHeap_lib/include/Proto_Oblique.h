#ifndef IHEAP_PROTO_OBLIQUE_H
#define IHEAP_PROTO_OBLIQUE_H

#include <Heap_Interface.h>

class Proto_Oblique : public Heap_Interface{
public:
    Proto_Oblique();
    //Proto_Oblique(int value);
    virtual void insert(int value) = 0;
    int get_min() const override ;
    void extract_min() override ;
    void meld(Heap_Interface & other) override ;
    ~Proto_Oblique();

protected:
    class Oblique_Node{
    public:
        int key;
        Oblique_Node *left_child;
        Oblique_Node *right_child;

        Oblique_Node(int value);
        Oblique_Node* meld(Oblique_Node* other);
        virtual void invariant() = 0;
    };
    virtual Oblique_Node* create_node(int value) = 0;

    Oblique_Node* _head;

    void _delete_tree(Oblique_Node* node);
};

#endif //IHEAP_PROTO_OBLIQUE_H
