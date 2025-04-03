#pragma once

#include <iostream>

using namespace std;

namespace graph{
    enum vColor{
        WHITE, GRAY, BLACK
    };

    class EdgeNode;

    class Vertex{
        private:
            unsigned int id;
            unsigned int degree;
            EdgeNode* edges;
            unsigned int d;
            Vertex* pi;
            vColor color;
            Vertex* next;
            Vertex* prev;
            bool isInHeap;

        public:
            Vertex():degree(0), edges(nullptr), next(nullptr), prev(nullptr), isInHeap(false){}
            ~Vertex();

            unsigned int getID() const {return this->id;}
            unsigned int& getID() {return this->id;}
            EdgeNode* getEdges() const { return this->edges;}
            EdgeNode*& getEdges() { return this->edges;}
            unsigned int getDegree() const {return this->degree;}
            Vertex** getAdjacents() const;
            Vertex* getNext() const {return this->next;}
            Vertex*& getNext(){return this->next;}
            Vertex* getPrev() const {return this->prev;}
            Vertex*& getPrev(){return this->prev;}
            unsigned int getD() const {return this->d;}
            unsigned int& getD() {return this->d;}
            Vertex* getPI() const {return this->pi;}
            Vertex*& getPI() {return this->pi;}
            vColor getColor() const {return this->color;}
            vColor& getColor() {return this->color;}
            bool getIsInHeap() const {return this->isInHeap;}
            bool& getIsInHeap() {return this->isInHeap;}
            int getWeight(const Vertex*) const;
            bool isUnioun(Vertex*);

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
            Vertex* v1;
            Vertex* v2;
            bool isSorted;
       
        public:
            Edge(Vertex* v1, Vertex* v2, const int weight):
                v1(v1), 
                v2(v2), 
                weight(weight){}
            
            int getWeight() const {return this->weight;}
            Vertex* getV1() const {return this->v1;}
            Vertex* getV2() const {return this->v2;}
            bool getIsSorted() const {return this->isSorted;}
            bool& getIsSorted() {return this->isSorted;}
            Vertex* getAdjacent(const Vertex* v) const{
                return (this->v1 == v ? this->v2 : this->v1);
            }

            friend ostream& operator<<(ostream& os, const Edge& e);
    };
  
    class EdgeNode{
        private:
            Edge* edge;
            EdgeNode* next;

        public:
            EdgeNode(Edge* edge): edge(edge), next(nullptr){}
            Edge* getEdge() const { return this->edge;}
            EdgeNode* getNext() const { return this->next;}
            EdgeNode*& getNext(){ return this->next;}
    };

    class Graph{
        private:
            const static int DEFAULT_W = 1;
            unsigned int nEdges;
            unsigned int negativeEdges;
            const unsigned int nVertices;
            Vertex* vertices;
            EdgeNode* edges;

            void addEdge(Edge*, EdgeNode*&);
            void removeEdge(const Edge*, EdgeNode**);
            
        public:
            Graph(const unsigned int nVertices);
            ~Graph();
            void addEdge(const unsigned int, const unsigned int, const int weight = DEFAULT_W);
            void removeEdge(const unsigned int, const unsigned int);
            void print_graph() const;
            unsigned int getnVertices() const {return this->nVertices;}
            unsigned int getnEdges() const {return this->nEdges;}
            Edge** getSortedEdges() const;
            bool isNegative() const {return this->negativeEdges;}
            void clearVertices() const;
            Vertex& operator[](const int v) const {return this->vertices[v];}
    };
}