#pragma once

#include "Graph.hpp"

using namespace graph;

class Queue{
    private:
        Vertex* head;
        Vertex* tail;
    public:
        Queue(): head(nullptr), tail(nullptr){}
        bool isEmpty(){return !this->head;}
        void enqueue(Vertex*);
        Vertex* dequeue();
};