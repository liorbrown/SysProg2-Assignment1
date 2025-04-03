#include "Heap.hpp"
#include <stdexcept>

using namespace std;

void Heap::insert(Vertex* v){
    v->getIsInHeap() = true;
    v->getNext() = this->head;
    this->head = v;
}

Vertex* Heap::extractMin(){
    if (this->isEmpty())
        throw runtime_error{"Heap is empty 🫤"};

    Vertex* min = this->head;

    for (Vertex* v = min->getNext(); v ; v = v->getNext())
        if (v->getD() < min->getD())
            min = v;
    
    min->getIsInHeap() = false;
    Vertex* prev = min->getPrev();
    Vertex* next = min->getNext();

    if (prev)
        prev->getNext() = next;

    if (next)
        next->getPrev() = prev;
    
    return min;
}
