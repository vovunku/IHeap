#ifndef IHEAP_BINOMIAL_HEAP_H
#define IHEAP_BINOMIAL_HEAP_H

#include <Heap_Interface.h>

class Binomial_Heap : public Heap_Interface{
public:
    Binomial_Heap();
    Binomial_Heap(int value);
    void insert(int value) override ;
    int get_min() const override ;
    void extract_min() override ;
    void meld(Heap_Interface & other) override;
    ~Binomial_Heap();
private:
    class Binomial_Tree_Node{
    public:
        Binomial_Tree_Node(int value);

        int key;
        int degree;

        Binomial_Tree_Node* left_child;
        Binomial_Tree_Node* right_sibling;

        Binomial_Tree_Node* meld_similar_nodes(Binomial_Tree_Node* other);
        void adopt_other_node(Binomial_Tree_Node* other);
        void make_other_stepbrother(Binomial_Tree_Node* other);
    };



    Binomial_Tree_Node *_head;
    Binomial_Tree_Node *_min_element;

    Binomial_Tree_Node* _find_min();
    void _renew_min();

    void _add_heap_to_root_list(Binomial_Heap& other);
    void _normalizing();
    void _delete_tree(Binomial_Tree_Node* node);
};

#endif //IHEAP_BINOMIAL_HEAP_H

