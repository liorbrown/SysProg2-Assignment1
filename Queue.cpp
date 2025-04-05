// liorbrown@outlook.co.il

#include "Queue.hpp"
#include <stdexcept>

using namespace std;

void Queue::enqueue(Vertex* v){

    // If queue isn't empty, sets its head prev attribute to point v
    if (!this->isEmpty())
        this->head->getPrev() = v;
    // If queueue wad empty, sets tail to v
    else
        this->tail = v;

    // Puts v in head of queue
    v->getNext() = this->head;
    this->head = v;
}

Vertex* Queue::dequeue(){
    if (this->isEmpty())
        throw runtime_error{"Queue is empty 🫤"}; 
    
    Vertex* result = this->tail;

    // If there was only one vertex in queue, sets head & tail to null
    if (this->head == this->tail)
        this->head = this->tail = nullptr;
    // If there was more the one, sets tail tail to previous one
    else{
        Vertex* newTail = this->tail->getPrev();
        newTail->getNext() = nullptr;
        this->tail = newTail;
    }

    return result;
}
