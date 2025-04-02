#pragma once

#include "iostream"

namespace graph{
    class EdgeNode;

    class Vertex{
        private:
            int degree;
            EdgeNode* edges;

        public:
            Vertex():degree(0), edges(nullptr){}
            ~Vertex();

            EdgeNode* getEdges() const { return this->edges;}
            EdgeNode*& getEdges() { return this->edges;}
    };

    class Edge{

        private:
            int weight;
            unsigned int v1;
            unsigned int v2;
       
        public:
            Edge(unsigned int v1, unsigned int v2, int weight):
                v1(v1), 
                v2(v2), 
                weight(weight){}
            
            unsigned int getV1() const {return this->v1;}
            unsigned int getV2() const {return this->v2;}
            int getWeight() const {return this->weight;}
            void print_edge() const {
                std::cout << this->v1 << " 🔗 " << this->v2 << std::endl;
            }
    };

    class EdgeNode{
        private:
            Edge* edge;
            EdgeNode* next;

        public:
            EdgeNode(Edge* edge): edge(edge), next(nullptr){}
            Edge* getEdge(){ return this->edge;}
            EdgeNode* getNext() const { return this->next;}
            EdgeNode*& getNext(){ return this->next;}
    };

    class Graph{
        private:
            const static int DEFAULT_W = 1;
            int negativeEdges;
            int nVertices;
            Vertex* vertices;
            EdgeNode* edges;
            void addEdge(Edge*, EdgeNode*&);
            void removeEdge(EdgeNode*, EdgeNode**);
            
        public:
            Graph(int nVertices):
                nVertices(nVertices),
                vertices(new Vertex[nVertices]), 
                edges(nullptr),
                negativeEdges(0){}
            ~Graph();
            void addEdge(unsigned int, unsigned int, int);
            void addEdge(unsigned int v1, unsigned int v2) {this->addEdge(v1, v2, DEFAULT_W);}
            void removeEdge(unsigned int, unsigned int);
            void print_graph() const;
    };
}