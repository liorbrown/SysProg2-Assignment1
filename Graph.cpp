#include "Graph.hpp"
#include <stdexcept>
#include <iostream>

using namespace graph;
using namespace std;

Vertex::~Vertex(){
    EdgeNode* currEdge = this->edges;

    while (currEdge)
    {
        EdgeNode* next = currEdge->getNext();

        delete currEdge;

        currEdge = next;
    }
}

Graph::~Graph(){
    delete[] this->vertices;
    this->vertices = NULL;

    EdgeNode* currEdge = this->edges;

    while (currEdge)
    {
        EdgeNode* next = currEdge->getNext();

        delete currEdge->getEdge();
        delete currEdge;

        currEdge = next;
    }
}

void Graph::addEdge(unsigned int v1, unsigned int v2, int weight){
    if (v1 >= this->nVertices || v2 >= this->nVertices)
        throw out_of_range{"The given points not exist in graph 🫤"};

    for (EdgeNode* e = this->vertices[v1].getEdges(); e ; e = e->getNext())
        if (e->getEdge()->getV1() == v2 || 
            e->getEdge()->getV2() == v2)
            throw invalid_argument{"Edge already exist 🙄"};
    
    Edge* newEdge = new Edge(v1, v2, weight);

    this->addEdge(newEdge, this->edges);
    this->addEdge(newEdge, this->vertices[v1].getEdges());
    this->addEdge(newEdge, this->vertices[v2].getEdges());

    if (weight < 0)
        this->negativeEdges++;
}

void Graph::addEdge(Edge* newEdge, EdgeNode*& edges){
    EdgeNode* newEdgeNode = new EdgeNode(newEdge);
    newEdgeNode->getNext() = edges;
    edges = newEdgeNode; 
}

void Graph::removeEdge(unsigned int v1, unsigned int v2){
    if (v1 >= this->nVertices || v2 >= this->nVertices)
        throw out_of_range{"The given points not exist in graph 😶"};

    EdgeNode** previous = &this->vertices[v1].getEdges();
    EdgeNode* currEdge = *previous;

    while (currEdge){
        if (currEdge->getEdge()->getV1() == v2 || 
            currEdge->getEdge()->getV2() == v2){
            
            this->removeEdge(currEdge, &this->vertices[v2].getEdges());
            this->removeEdge(currEdge, &this->edges);

            Edge* edge = currEdge->getEdge();

            if (edge->getWeight() < 0)
                this->negativeEdges--;

            delete edge;
            edge = NULL;

            EdgeNode* next = currEdge->getNext();
            delete currEdge;
            currEdge = NULL;
            *previous = next;
            
            return;
        } else{
            previous = &currEdge->getNext();
            currEdge = *previous;
        }
    }

    throw invalid_argument{"Edge dont exist 🤨"};
}

void Graph::removeEdge(EdgeNode* edge, EdgeNode** previous){
    EdgeNode* currEdge = *previous;

    while (currEdge){
        if (currEdge == edge){
            EdgeNode* next = currEdge->getNext();
            delete currEdge;
            currEdge = NULL;
            *previous = next;

            break;
        } else{
            previous = &currEdge->getNext();
            currEdge = *previous;
        }
    }
}

void Graph::print_graph() const {
    cout << "The graph have " << this->nVertices << " vertices" << endl;
    cout << "Those are the graph edges:" << endl;

    for (EdgeNode* e = this->edges ; e ; e = e->getNext())
        e->getEdge()->print_edge();
}

int main(){return 0;}


