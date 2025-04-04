#include "Queue.hpp"
#include <stdexcept>

using namespace std;

void Queue::enqueue(Vertex* v){

    if (!this->isEmpty())
        this->head->getPrev() = v;
    else
        this->tail = v;

    v->getNext() = this->head;
    this->head = v;
}

Vertex* Queue::dequeue(){
    if (this->isEmpty())
        throw runtime_error{"Queue is empty 🫤"}; 
    
    Vertex* result = this->tail;

    if (this->head == this->tail)
        this->head = nullptr;
    else{
        Vertex* newTail = this->tail->getPrev();
        newTail->getNext() = nullptr;
        this->tail = newTail;
    }

    return result;
}
