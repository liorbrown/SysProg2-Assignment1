#include "Graph.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;

namespace graph{
    // ------------ Vertex implementaion ------------------
    
    Vertex::~Vertex(){
        EdgeNode* currEdge = this->edges;

        // Run on all edges of this vertex
        while (currEdge)
        {
            EdgeNode* next = currEdge->getNext();

            // Note that here we delete only the EdgeNode and not the itself
            // because maybe the edge itself is still use and pointed by other lists
            delete currEdge;

            currEdge = next;
        }
    }

    Vertex** Vertex::getAdjacents() const{

        Vertex** result = new Vertex*[this->degree];
        int i = 0;

        // Run on all vertex edges
        for (EdgeNode* e = this->edges; e ; e = e->getNext())
            // Add to array the adjacent vertex in the current edge
            result[i++] = e->getEdge()->getAdjacent(this);
        
        return result;
    }

    int Vertex::getWeight(const Vertex* v) const{

        // Run on all vertex edges
        for (EdgeNode* e = this->edges; e ; e = e->getNext())
            // Check if v is the adjacent of this in current edge
            if (e->getEdge()->getAdjacent(this) == v)
                return e->getEdge()->getWeight();
            
        throw runtime_error{"The vertices are not adjacents"};
    }

    bool Vertex::isUnioun(Vertex* v){
        Vertex* thisRoot = this;
        Vertex* vRoot = v; 
        
        // Step up in this vertex tree until reach its root
        while (thisRoot->getNext())
            thisRoot = thisRoot->getNext();

        // Step up in given vertex tree until reach its root
        while (vRoot->getNext())
            vRoot = vRoot->getNext();
        
        // Check if they have the same root, so they called "Union"
        if (thisRoot == vRoot)
            return true;
        // If not have the same root, then union their roots and return false
        // because they "where" not union
        else{
            thisRoot->getNext() = vRoot;
            return false;
        }
    }

    // ------------ Graph implementaion ------------------
    Graph::Graph(const unsigned int nVertices):
        nVertices(nVertices),
        vertices(new Vertex[nVertices]), 
        edges(nullptr),
        negativeEdges(0),
        nEdges(0){
        
        // Runs on all graph vertices and sets their id to their index
        for (size_t i = 0; i < nVertices; i++)            
            (*this)[i].getID() = i;
    }

    Graph::~Graph(){
        // Delete vertices array
        delete[] this->vertices;

        EdgeNode* currEdge = this->edges;

        // Run on all graph edges
        while (currEdge){
            EdgeNode* next = currEdge->getNext();

            // Delete edge itself. Note that all other EdgeNode that contains this edge was already deleted
            // when we write "delete[] this->vertices", so we can safety delete this edge
            delete currEdge->getEdge();

            // Deletes edge node
            delete currEdge;

            currEdge = next;
        }
    }

    void Graph::addEdge(unsigned int v1, unsigned int v2, int weight){
        if (v1 >= this->nVertices || v2 >= this->nVertices)
            throw out_of_range{"The given vertices not exist in graph 🫤"};

        if (v1 == v2)
            throw invalid_argument{"This graph is simple, edge from vertex to itself is not allowed 🙄"};

        // Run on all current edges of v1 for check if edge already exist
        for (EdgeNode* e = (*this)[v1].getEdges(); e ; e = e->getNext())
            // Because we dont know if our v1 is also v1 in the edge or its v2
            // we need to check both
            if (e->getEdge()->getV1() == &(*this)[v2] || 
                e->getEdge()->getV2() == &(*this)[v2])
                throw invalid_argument{"Edge already exist 🙄"};
        
        // Creates new edge
        Edge* newEdge = new Edge(&(*this)[v1], &(*this)[v2], weight);

        // Adds new edge to graph edges list
        this->addEdge(newEdge, this->edges);

        // Adds new edge to both vertices edges list, and increment their degree
        this->addEdge(newEdge, (++((*this)[v1])).getEdges());
        this->addEdge(newEdge, (++((*this)[v2])).getEdges());

        // We have to update amount of negative edges, for know any time if there are negative edges
        if (weight < 0)
            this->negativeEdges++;
        
        this->nEdges++;
    }

    void Graph::addEdge(Edge* newEdge, EdgeNode*& edges){

        // Creates new EdgeNode
        EdgeNode* newEdgeNode = new EdgeNode(newEdge);

        // Puts new EdgeNode in the head of given edges list
        newEdgeNode->getNext() = edges;
        edges = newEdgeNode; 
    }

    void Graph::removeEdge(unsigned int v1, unsigned int v2){
        if (v1 >= this->nVertices || v2 >= this->nVertices)
            throw out_of_range{"The given vertices not exists in graph 😶"};

        if (v1 == v2)
            throw invalid_argument{"This graph is simple, edge from vertex to itself is not allowed 🙄"};

        // Set pointer to pointer of previous edge,
        // for make its point to next edge
        EdgeNode** previous = &(*this)[v1].getEdges();
        EdgeNode* currEdge = *previous;

        // Runs on all v1 edges and searce for the edge that connect to v2
        while (currEdge){
            const Edge* edge = currEdge->getEdge();

            // Checks if the adjacent of v1 in this edge is v2
            if (edge->getAdjacent(&(*this)[v1]) == &(*this)[v2]){

                // Removes edge from graph edge list
                this->removeEdge(edge, &this->edges);

                // Removes edge from v2 edge list, and decrease its degree
                this->removeEdge(edge, &(--((*this)[v2])).getEdges());

                if (edge->getWeight() < 0)
                    this->negativeEdges--;
                
                this->nEdges--;

                // Delete edge itself
                delete edge;

                EdgeNode* next = currEdge->getNext();

                // Delete v1 EdgeNode
                delete currEdge;

                // Sets previous EdgeNode to point to next edge
                *previous = next;
                
                // Decrease v1 degree
                --((*this)[v1]);

                return;
            // If current edge is not connect to v2
            } else{
                // Sets previous to pint to pointer of next vertex
                previous = &currEdge->getNext();

                // Continue to next edge
                currEdge = *previous;
            }
        } 

        throw invalid_argument{"Edge not exist 🤨"};
    }

    void Graph::removeEdge(const Edge* edge, EdgeNode** previous){
        EdgeNode* currEdge = *previous;

        // Runs on all edges in given list
        while (currEdge){
            // Check if current edge is given edge
            if (currEdge->getEdge() == edge){
                EdgeNode* next = currEdge->getNext();

                // Delete current EdgeNode
                delete currEdge;

                // Sets previous EdgeNode to point to next edge
                *previous = next;

                return;
            // If current edge isn't given edge
            } else {
                // Sets previous to pint to pointer of next vertex
                previous = &currEdge->getNext();

                // Continue to next edge
                currEdge = *previous;
            }
        }
    }

    void Graph::print_graph() const {
        cout << "The graph have " << this->nVertices << " vertices" << endl;
        cout << "Those are the graph edges:" << endl;

        // Runs on all graph edges, and print them
        for (EdgeNode* e = this->edges ; e ; e = e->getNext())
            cout << *e->getEdge() << endl;
    }

    Edge **Graph::getSortedEdges() const{

        Edge** result = new Edge*[this->nEdges];
        int i = 0;
    
        // Init edges array with all graph edges
        for (EdgeNode* e = this->edges; e ; e = e->getNext())
            result[i++] = e->getEdge();
    
        // Bubble sort edge array by weight
        bool isSwap = true;
    
        for (size_t i = 0; i < this->nEdges - 1 && isSwap; i++){
            isSwap = false;
    
            for (size_t j = this->nEdges - 1; j > i; j--)
                if (result[j-1]->getWeight() > result[j]->getWeight()){
                    Edge* temp = result[j-1];
                    result[j-1] = result[j];
                    result[j] = temp;
    
                    isSwap = true;
                }
            
        }
        
        return result;
    }

    void Graph::clearVertices() const
    {
        // Runs on all graph vertices and clear their next and prev attributes
        for (size_t i = 0; i < this->nVertices; i++)
            this->vertices[i].getNext() = this->vertices[i].getPrev() = nullptr;
    }

    ostream& operator<<(ostream& os, const Edge& e){
        os << e.v1->getID() << " 🔗 " << e.v2->getID() << " | Weight: " << e.weight;
        return os;
    }
}