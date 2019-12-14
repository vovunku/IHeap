#ifndef IHEAP_HEAP_INTERFACE_H
#define IHEAP_HEAP_INTERFACE_H

class Heap_Interface{
public:
    virtual void insert(int p) = 0;
    virtual int get_min() const = 0;
    virtual void extract_min() = 0;
    virtual void meld(Heap_Interface& other) = 0;
};

#endif //IHEAP_HEAP_INTERFACE_H
