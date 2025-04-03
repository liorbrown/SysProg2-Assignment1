#include "Queue.hpp"
#include <stdexcept>

using namespace std;

void Queue::enqueue(const unsigned int val){
    Node* newNode = new Node(val);
    
    if (!this->isEmpty())
        this->head->getPrev() = newNode;
    else
        this->tail = newNode;

    newNode->getNext() = this->head;
    this->head = newNode;
}

unsigned int Queue::dequeue(){
    if (this->isEmpty())
        throw runtime_error{"Queue is empty 🫤"}; 
    
    int result = this->tail->getVal();

    Node* newTail = this->tail->getPrev();
    newTail->getNext() = nullptr;
    delete this->tail;
    this->tail = newTail;

    return result;
}
