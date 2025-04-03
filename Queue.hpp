#pragma once

#include "Node.hpp"

class Queue{
    private:
        Node* head;
        Node* tail;
    public:
        Queue(): head(nullptr), tail(nullptr){}
        ~Queue(){Node::destroy(this->head);}
        bool isEmpty(){return !this->head;}
        void enqueue(const unsigned int);
        unsigned int dequeue();
};