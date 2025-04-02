#pragma once

#include <iostream>

using namespace std;

namespace graph{
    class EdgeNode;

    class Vertex{
        private:
            unsigned int degree;
            EdgeNode* edges;

        public:
            Vertex():degree(0), edges(nullptr){}
            ~Vertex();

            EdgeNode* getEdges() const { return this->edges;}
            EdgeNode*& getEdges() { return this->edges;}
            
            Vertex& operator++(){
                this->degree++;
                return *this;
            }

            Vertex& operator--(){
                this->degree--;
                return *this;
            }
    };

    class Edge{

        private:
            const int weight;
            const unsigned int v1;
            const unsigned int v2;
       
        public:
            Edge(const unsigned int v1, const unsigned int v2, const int weight):
                v1(v1), 
                v2(v2), 
                weight(weight){}
            
            int getWeight() const {return this->weight;}
            int getV1() const {return this->v1;}
            int getV2() const {return this->v2;}

            friend ostream& operator<<(ostream& os, const Edge& e);
    };
  
    class EdgeNode{
        private:
            const Edge* edge;
            EdgeNode* next;

        public:
            EdgeNode(const Edge* edge): edge(edge), next(nullptr){}
            const Edge* getEdge() const { return this->edge;}
            EdgeNode* getNext() const { return this->next;}
            EdgeNode*& getNext(){ return this->next;}
    };

    class Graph{
        private:
            const static int DEFAULT_W = 1;
            
            unsigned int negativeEdges;
            const unsigned int nVertices;
            Vertex* vertices;
            EdgeNode* edges;

            void addEdge(const Edge*, EdgeNode*&);
            void removeEdge(const Edge*, EdgeNode**);
            
        public:
            Graph(const unsigned int nVertices):
                nVertices(nVertices),
                vertices(new Vertex[nVertices]), 
                edges(nullptr),
                negativeEdges(0){}
            ~Graph();
            void addEdge(const unsigned int, const unsigned int, const int);
            void removeEdge(const unsigned int, const unsigned int);
            void print_graph() const;
    };
}