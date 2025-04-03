#include "Algorithms.hpp"
#include "Queue.hpp"
#include "Heap.hpp"
#include <stdexcept>

#define INF 999999

using namespace graph;
using namespace std;

Graph *Algorithms::bfs(const Graph &g, const unsigned int s)
{
    const unsigned int nVertices = g.getnVertices();

    if (s >= nVertices)
        throw out_of_range{"The given vertices not exist in graph 🫤"};

    setVAttributes(g, &g[s]);
    Graph* result = buildGraph(g);

    return result;
}

void Algorithms::setVAttributes(const Graph &g, Vertex* s)
{
    initAttributes(g);

    s->getColor() = GRAY;

    g.clearVertices();

    Queue q;

    q.enqueue(s);

    while (!q.isEmpty())
    {
        Vertex* v = q.dequeue();
        Vertex** adjacents = v->getAdjacents();
        for (size_t i = 0; i < v->getDegree(); i++){
            Vertex* adjacent = adjacents[i];

            if (adjacent->getColor() == WHITE){
                adjacent->getColor() = GRAY;
                adjacent->getPI() = v;
                q.enqueue(adjacent);
            }
        }

        v->getColor() = BLACK;
    }
}

void Algorithms::initAttributes(const Graph &g)
{
    for (size_t i = 0; i < g.getnVertices(); i++){
        g[i].getColor() = WHITE;
        g[i].getPI() = nullptr;
        g[i].getD() = INF;
    }
}

Graph *Algorithms::buildGraph(const Graph &g){
    unsigned int size = g.getnVertices();

    Graph* result = new Graph(size);

    for (size_t i = 0; i < size; i++)
        if (g[i].getPI() != nullptr){

            Vertex* v2 = g[i].getPI();

            result->addEdge(i, v2->getID(), g[i].getWeight(v2));
        }
    
    return result;
}

Graph *Algorithms::dfs(const Graph &g, const unsigned int s){

    const unsigned int nVertices = g.getnVertices();
    
    initAttributes(g);

    for (size_t i = 0; i < nVertices; i++)
    {
        Vertex* v = &g[i + s % nVertices];

        if (v->getColor() == WHITE)
            dfsVisit(g, v);
    }

    Graph* result = buildGraph(g);

    return result;
}

void Algorithms::dfsVisit(const Graph &g, Vertex* v){
    
    v->getColor() = GRAY;

    Vertex** adjacents = v->getAdjacents();
    
    for (size_t i = 0; i < v->getDegree(); i++){
        Vertex* adjacent = adjacents[i];

        if (adjacent->getColor() == WHITE){
            adjacent->getPI() = v;
            dfsVisit(g, adjacent);
        }
    }

    v->getColor() = BLACK;
}

void Algorithms::relax(const Edge& e, Vertex* v){
    Vertex* u = e.getAdjacent(v);

    if (u->getD() > v->getD() + e.getWeight()){
        u->getD() = v->getD() + e.getWeight();
        u->getPI() = v;
    }
}

Graph* Algorithms::dijkstra(const Graph &g, const unsigned int s)
{
    if (g.isNegative())
        throw domain_error{"Can't run dijkstra on graph with negative edges"};

    initAttributes(g);
    int size = g.getnVertices();
    g.clearVertices();
    
    Heap q;

    for (size_t i = 0; i < size; i++)
        q.insert(&g[i]);
    
    while (!q.isEmpty()){
        Vertex* v = q.extractMin();

        for (EdgeNode* e = v->getEdges() ; e ; e = e->getNext())
            relax(*e->getEdge(), v);        
    }

    Graph* result = buildGraph(g);

    return result;
}

Graph *Algorithms::prim(const Graph &g)
{
    initAttributes(g);
    g.clearVertices();
    Heap q;

    for (size_t i = 0; i < g.getnVertices(); i++)
        q.insert(&g[i]);
    
    g[0].getD() = 0;

    while (!q.isEmpty()){
        Vertex* v = q.extractMin();
        Vertex** adjacents = v->getAdjacents();

        for (size_t i = 0; i < v->getDegree(); i++){
            Vertex* adjacent = adjacents[i];
            const int weight = v->getWeight(adjacent);

            if (adjacent->getIsInHeap() && weight < adjacent->getD()){
                adjacent->getPI() = v;
                adjacent->getD() = weight;
            }
        } 
    }

    Graph* result = buildGraph(g);
    return result;
}

Graph *Algorithms::kruskal(const Graph &g)
{
    Graph* result = new Graph(g.getnVertices());

    const Edge** edges = g.getSortedEdges();

    g.clearVertices();

    for (size_t i = 0; i < g.getnEdges(); i++){
        Vertex* v1 = edges[i]->getV1();
        Vertex* v2 = edges[i]->getV2();

        if (v1->isUnioun(v2)){
            result->addEdge(v1->getID(), v2->getID(), edges[i]->getWeight());
            v1->getNext() = v2;
        }
    }
  
    return result;
}
