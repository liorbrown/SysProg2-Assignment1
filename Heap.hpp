#pragma once

#include "Graph.hpp"

using namespace graph;

class Heap{
    private:
        Vertex* head;
    public:
        Heap(): head(nullptr){}
        void insert(Vertex*);
        Vertex* extractMin();
        bool isEmpty(){return !this->head;}
};