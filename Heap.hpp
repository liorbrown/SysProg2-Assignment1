// liorbrown@outlook.co.il

#pragma once

#include "Graph.hpp"

using namespace graph;

/// @brief This class represent minimum heap of vertices.
/// this is not full heap implementation because 'e were not required for best effitioncy
/// But its give us the needed functionality for implement dijkstra.
/// This queue dont hold any of new vertices, but only have pointers to origin vertices
class Heap{
    private:
        Vertex* head;
    public:
        Heap(): head(nullptr){}

        /// @brief Insert new vertex to heap
        /// @param v Vertex to insert
        void insert(Vertex* v);

        /// @brief Extract the minimum vertex in heap, according to its d attribute
        /// @return The extracted vertex
        Vertex* extractMin();
        bool isEmpty(){return !this->head;}
};