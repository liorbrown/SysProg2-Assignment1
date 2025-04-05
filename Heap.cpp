// liorbrown@outlook.co.il

#include "Heap.hpp"
#include <stdexcept>

using namespace std;

void Heap::insert(Vertex* v){
    v->getIsInHeap() = true;

    // puts new vertex in queue head
    v->getNext() = this->head;

    // Check if heap is not empty, sets its old head prev pointer to new vertex
    if (!this->isEmpty())
        this->head->getPrev() = v;
    
    // Sets queue head to new vertex
    this->head = v;
}

Vertex* Heap::extractMin(){
    if (this->isEmpty())
        throw runtime_error{"Heap is empty 🫤"};

    Vertex* min = this->head;

    // Runs on all vertices in heap for find the minimum d
    for (Vertex* v = min->getNext(); v ; v = v->getNext())
        if (v->getD() < min->getD())
            min = v;
    
    min->getIsInHeap() = false;
    Vertex* prev = min->getPrev();
    Vertex* next = min->getNext();

    // If it was not the first, sets the previous one to point on the next one
    if (prev)
        prev->getNext() = next;
    // If it was first, sets head to next one
    else
        this->head = min->getNext();
    
    // If it was not the last, sets the next one to point on the previous one
    if (next)
        next->getPrev() = prev;
        
    return min;
}
