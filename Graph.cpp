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

    Vertex** Vertex::getAdjacents() const{

        Vertex** result = new Vertex*[this->degree];
        EdgeNode* currEdge = this->edges;

        for (size_t i = 0; i < this->degree ; i++){
            Vertex* currVertex = currEdge->getEdge()->getAdjacent(this);
            result[i] = currVertex;
            currEdge = currEdge->getNext();
        }
        
        return result;
    }

    int Vertex::getWeight(const Vertex* v) const{
        for (EdgeNode* e = this->edges; e ; e = e->getNext()){
            Edge edge = *e->getEdge();

            if (edge.getV1() == v || edge.getV2() == v)
                return edge.getWeight();
        }
        
        throw runtime_error{"The vertices are not adjacents"};
    }

    bool Vertex::isUnioun(Vertex* v){
        Vertex* thisRoot = this;
        Vertex* vRoot = v; 
        
        while (thisRoot->getNext())
            thisRoot = thisRoot->getNext();

        while (vRoot->getNext())
            vRoot = vRoot->getNext();
        
        if (thisRoot == vRoot)
            return true;
        else{
            thisRoot->getNext() = vRoot;
            return false;
        }
    }

    Graph::Graph(const unsigned int nVertices):
        nVertices(nVertices),
        vertices(new Vertex[nVertices]), 
        edges(nullptr),
        negativeEdges(0),
        nEdges(0){
        
        for (size_t i = 0; i < nVertices; i++)            
            (*this)[i].getID() = i;
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

    void Graph::addEdge(unsigned int v1, unsigned int v2, int weight){
        if (v1 >= this->nVertices || v2 >= this->nVertices)
            throw out_of_range{"The given vertices not exist in graph 🫤"};

        if (v1 == v2)
            throw invalid_argument{"This graph is simple, edge from vertex to itself is not allowed 🙄"};

        for (EdgeNode* e = (*this)[v1].getEdges(); e ; e = e->getNext())
            if (e->getEdge()->getV1() == &(*this)[v2] || 
                e->getEdge()->getV2() == &(*this)[v2])
                throw invalid_argument{"Edge already exist 🙄"};
        
        Edge* newEdge = new Edge(&(*this)[v1], &(*this)[v2], weight);

        this->addEdge(newEdge, this->edges);
        this->addEdge(newEdge, (++((*this)[v1])).getEdges());
        this->addEdge(newEdge, (++((*this)[v2])).getEdges());

        if (weight < 0)
            this->negativeEdges++;
        
        this->nEdges++;
    }

    void Graph::addEdge(Edge* newEdge, EdgeNode*& edges){
        EdgeNode* newEdgeNode = new EdgeNode(newEdge);
        newEdgeNode->getNext() = edges;
        edges = newEdgeNode; 
    }

    void Graph::removeEdge(unsigned int v1, unsigned int v2){
        if (v1 >= this->nVertices || v2 >= this->nVertices)
            throw out_of_range{"The given vertices not exists in graph 😶"};

        if (v1 == v2)
            throw invalid_argument{"This graph is simple, edge from vertex to itself is not allowed 🙄"};

        EdgeNode** previous = &(*this)[v1].getEdges();
        EdgeNode* currEdge = *previous;

        while (currEdge){
            const Edge* edge = currEdge->getEdge();

            if (edge->getV1() == &(*this)[v2] || edge->getV2() == &(*this)[v2]){ 
                
                this->removeEdge(edge, &this->edges);
                this->removeEdge(edge, &(--((*this)[v2])).getEdges());

                if (edge->getWeight() < 0)
                    this->negativeEdges--;
                
                this->nEdges--;
                
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
            cout << *e->getEdge() << endl;
    }

    Edge **Graph::getSortedEdges() const{

        for (EdgeNode* e = this->edges; e ; e = e->getNext())
            e->getEdge()->getIsSorted() = false;

        Edge** result = new Edge*[this->nEdges];

        for (size_t i = 0; i < this->nEdges; i++){
            Edge* min = nullptr;
            
            for (EdgeNode* e = this->edges; e ; e = e->getNext()){
                Edge* edge = e->getEdge();

                if (!edge->getIsSorted() && (!min || edge->getWeight() < min->getWeight()))
                    min = edge;
            }
            
            min->getIsSorted() = true;
            result[i] = min;
        }
        
        return result;
    }

    void Graph::clearVertices() const
    {
        for (size_t i = 0; i < this->nVertices; i++)
            this->vertices[i].getNext() = this->vertices[i].getPrev() = nullptr;
    }

    ostream& operator<<(ostream& os, const Edge& e){
        os << e.v1->getID() << " 🔗 " << e.v2->getID() << " | Weight: " << e.weight;
        return os;
    }
}