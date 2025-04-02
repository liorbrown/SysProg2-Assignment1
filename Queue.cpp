#include "Queue.hpp"

#define EMPTY_FLAG -1

Queue::~Queue(){
    Node* currNode = this->head;

    while (currNode){
        Node* next = currNode->getNext();

        delete currNode;

        currNode = next;
    }
}

void Queue::enqueue(const unsigned int val){
    Node* newNode = new Node(val);
    
    if (!this->isEmpty())
        this->head->getPrev() = newNode;
    else
        this->tail = newNode;

    newNode->getNext() = this->head;
    this->head = newNode;
}

int Queue::dequeue(){
    if (this->isEmpty())
        return EMPTY_FLAG;
    
    int result = this->tail->getVal();

    Node* newTail = this->tail->getPrev();
    newTail->getNext() = nullptr;
    delete this->tail;
    this->tail = newTail;

    return result;
}
