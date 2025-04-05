// liorbrown@outlook.co.il

#pragma once

#include "Graph.hpp"

using namespace graph;

/// @brief This class represented vertices queue
/// its not hold the vertices itself, but only points to the original
class Queue{
    private:
        Vertex* head;
        Vertex* tail;
    public:
        Queue(): head(nullptr), tail(nullptr){}
        bool isEmpty(){return !this->head;}

        /// @brief This method insert vertex to queue
        /// @param v Vertex to insert
        void enqueue(Vertex* v);

        /// @brief This method pulls vertex from queue according to FIFO
        /// @return The pulls vertex
        Vertex* dequeue();
};