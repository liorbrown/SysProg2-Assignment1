#pragma once

#include "Node.hpp"

class Heap{
    private:
        Node* head;
    public:
        Heap(): head(nullptr){}
        ~Heap(){Node::destroy(this->head);}
        void insert(const unsigned int);
        unsigned int extractMin();
        bool isEmpty(){return !this->head;}
};