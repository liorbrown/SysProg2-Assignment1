#include "Graph.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;

namespace graph{
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
        this->vertices = nullptr;

        EdgeNode* currEdge = this->edges;

        while (currEdge)
        {
            EdgeNode* next = currEdge->getNext();

            delete currEdge->getEdge();
            delete currEdge;

            currEdge = next;
        }
    }

    void Graph::addEdge(unsigned int v1, unsigned int v2, int weight = DEFAULT_W){
        if (v1 >= this->nVertices || v2 >= this->nVertices)
            throw out_of_range{"The given vertices not exist in graph 🫤"};

        if (v1 == v2)
            throw invalid_argument{"This graph is simple, edge from vertex to itself is not allowed 🙄"};

        for (EdgeNode* e = this->vertices[v1].getEdges(); e ; e = e->getNext())
            if (e->getEdge()->getV1() == v2 || e->getEdge()->getV2() == v2)
                throw invalid_argument{"Edge already exist 🙄"};
        
        Edge* newEdge = new Edge(v1, v2, weight);

        this->addEdge(newEdge, this->edges);
        this->addEdge(newEdge, (++(this->vertices[v1])).getEdges());
        this->addEdge(newEdge, (++(this->vertices[v2])).getEdges());

        if (weight < 0)
            this->negativeEdges++;
    }

    void Graph::addEdge(const Edge* newEdge, EdgeNode*& edges){
        EdgeNode* newEdgeNode = new EdgeNode(newEdge);
        newEdgeNode->getNext() = edges;
        edges = newEdgeNode; 
    }

    void Graph::removeEdge(unsigned int v1, unsigned int v2){
        if (v1 >= this->nVertices || v2 >= this->nVertices)
            throw out_of_range{"The given vertices not exists in graph 😶"};

        EdgeNode** previous = &this->vertices[v1].getEdges();
        EdgeNode* currEdge = *previous;

        while (currEdge){
            const Edge* edge = currEdge->getEdge();

            if (edge->getV1() == v2 || edge->getV2() == v2){ 
                
                this->removeEdge(edge, &this->edges);
                this->removeEdge(edge, &(--(this->vertices[v2])).getEdges());

                if (edge->getWeight() < 0)
                    this->negativeEdges--;

                delete edge;

                EdgeNode* next = currEdge->getNext();
                delete currEdge;
                *previous = next;
                
                --this->vertices[v1];

                return;
            } else{
                previous = &currEdge->getNext();
                currEdge = *previous;
            }
        }

        throw invalid_argument{"Edge not exist 🤨"};
    }

    void Graph::removeEdge(const Edge* edge, EdgeNode** previous){
        EdgeNode* currEdge = *previous;

        while (currEdge){
            if (currEdge->getEdge() == edge){
                EdgeNode* next = currEdge->getNext();
                delete currEdge;
                *previous = next;

                return;
            } else {
                previous = &currEdge->getNext();
                currEdge = *previous;
            }
        }
    }

    void Graph::print_graph() const {
        cout << "The graph have " << this->nVertices << " vertices" << endl;
        cout << "Those are the graph edges:" << endl;

        for (EdgeNode* e = this->edges ; e ; e = e->getNext())
            cout << *(e->getEdge()) << endl;
    }

    ostream& operator<<(ostream& os, const Edge& e)
    {
        os << e.v1 << " 🔗 " << e.v2;
        return os;
    }
}

