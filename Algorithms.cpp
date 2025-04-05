// liorbrown@outlook.co.il

#include "Algorithms.hpp"
#include "Queue.hpp"
#include "Heap.hpp"
#include <stdexcept>

#define INF 999999

using namespace graph;
using namespace std;

Graph *Algorithms::bfs(Graph &g, const unsigned int s)
{
    const unsigned int nVertices = g.getnVertices();

    if (s >= nVertices)
        throw out_of_range{"The given vertices not exist in graph 🫤"};

    // Sets PI attribute of all vertices
    setPI(g, &g[s]);

    // Build result tree according to PI
    Graph* result = buildGraph(g);

    return result;
}

void Algorithms::setPI(Graph &g, Vertex* s)
{
    initAttributes(g);
    s->getColor() = GRAY;

    // Clear vertices next and prev attributes before using queue
    // because its using them, and need them fresh 
    g.clearVertices();

    Queue q;

    q.enqueue(s);

    // Runs until queue is empty
    while (!q.isEmpty())
    {
        Vertex* v = q.dequeue();

        Vertex** adjacents = v->getAdjacents();

        // Runs on all v adjacents
        for (size_t i = 0; i < v->getDegree(); i++){
            Vertex* adjacent = adjacents[i];

            // Check if current adjacent is white
            if (adjacent->getColor() == WHITE){
                adjacent->getColor() = GRAY;
                
                // Sets its PI to v, and insert it to queue
                adjacent->getPI() = v;
                q.enqueue(adjacent);
            }
        }

        delete[] adjacents;

        v->getColor() = BLACK;
    }
}

void Algorithms::initAttributes(Graph &g)
{
    // Runs on all vertices, and init their attributes
    for (size_t i = 0; i < g.getnVertices(); i++){
        g[i].getColor() = WHITE;
        g[i].getPI() = nullptr;
        g[i].getD() = INF;
    }
}

Graph *Algorithms::buildGraph(Graph &g){
    unsigned int size = g.getnVertices();

    Graph* result = new Graph(size);

    // Runs on all origin graph vertices
    for (size_t i = 0; i < size; i++)
        // Checks if current vertex PI is not null
        if (g[i].getPI() != nullptr){

            Vertex* v2 = g[i].getPI();

            // Creates new edge in result graph, same as the edge on origin graph
            result->addEdge(i, v2->getID(), g[i].getWeight(v2));
        }
    
    return result;
}

Graph *Algorithms::dfs(Graph &g, const unsigned int s){

    const unsigned int nVertices = g.getnVertices();
    
    // Init all vertices attributes
    initAttributes(g);

    // Runs on all graph vertices, starts from s
    for (size_t i = s; i < s + nVertices; i++){
        Vertex* v = &g[i % nVertices];

        // If current vertex is white, then do dfs-visit on it
        if (v->getColor() == WHITE)
            dfsVisit(g, v);
    }

    // Build result graph according to PI attributes
    Graph* result = buildGraph(g);

    return result;
}

void Algorithms::dfsVisit(Graph &g, Vertex* v){
    
    v->getColor() = GRAY;

    Vertex** adjacents = v->getAdjacents();
    
    // Runs on all v adjacents
    for (size_t i = 0; i < v->getDegree(); i++){
        Vertex* adjacent = adjacents[i];

        // Check if current adjacent is white
        if (adjacent->getColor() == WHITE){
            // Sets its PI to v
            adjacent->getPI() = v;

            // Recursively make dfs-visit to current adjacent
            dfsVisit(g, adjacent);
        }
    }

    delete[] adjacents;

    v->getColor() = BLACK;
}

void Algorithms::relax(const Edge& e, Vertex* v){
    Vertex* u = e.getAdjacent(v);

    // Check if can decrease the d of u, using the edge from v
    if (u->getD() > v->getD() + e.getWeight()){
        u->getD() = v->getD() + e.getWeight();

        // Sets u PI to point on v
        u->getPI() = v;
    }
}

Graph* Algorithms::dijkstra(Graph &g, const unsigned int s)
{
    if (g.isNegative())
        throw domain_error{"Can't run dijkstra on graph with negative edges"};

    // Init all vertices attributes
    initAttributes(g);
    int size = g.getnVertices();

    // Clear all next and prev vertices pointers, because heap need to use them
    g.clearVertices();
    
    Heap q;

    // Inserts all vertices to heap
    for (size_t i = 0; i < size; i++)
        q.insert(&g[i]);
    
    g[s].getD() = 0;

    // Runs until heap is empty
    while (!q.isEmpty()){
        // Gets vertex with minimum d
        Vertex* v = q.extractMin();

        // Runs on all v edges, and use them to relax its neighbors
        for (EdgeNode* e = v->getEdges() ; e ; e = e->getNext())
            relax(*e->getEdge(), v);        
    }

    // Build result graph using PI attribute
    Graph* result = buildGraph(g);

    return result;
}

bool Algorithms::isConnect(Graph& g){
    if (!g.getnEdges())
        return false;

    // Runs bfs on given graph on first vertex
    Graph* bfsGraph = bfs(g,0);

    // Checks if bfs tree "touches" all graph vertices
    bool result = bfsGraph->getnEdges() == g.getnVertices() - 1;

    delete bfsGraph;

    return (result);
}

Graph* Algorithms::prim(Graph &g)
{
    if (!isConnect(g))
        return nullptr;

    initAttributes(g);

    // Clear all next and prev vertices pointers, because heap need to use them
    g.clearVertices();

    Heap q;

    // Inserts all vertices to heap
    for (size_t i = 0; i < g.getnVertices(); i++)
        q.insert(&g[i]);
    
    g[0].getD() = 0;

    //Runs until heap is empty
    while (!q.isEmpty()){
        Vertex* v = q.extractMin();
        Vertex** adjacents = v->getAdjacents();

        // Runs on all vertex adjacents
        for (size_t i = 0; i < v->getDegree(); i++){
            Vertex* adjacent = adjacents[i];

            // Get edge weight from v to current adjacent
            const int weight = v->getWeight(adjacent);

            // Check if adjacent is still in heap, and if its d greater then current edge weight
            if (adjacent->getIsInHeap() && weight < adjacent->getD()){
                // Sets its PI to point on v
                adjacent->getPI() = v;
                adjacent->getD() = weight;
            }
        }
        
        delete[] adjacents;
    }

    // Build result graph according to PI attribute
    Graph* result = buildGraph(g);
    return result;
}

Graph *Algorithms::kruskal(Graph &g)
{
    if (!isConnect(g))
        return nullptr;

    Graph* result = new Graph(g.getnVertices());

    // Gets all graph edges sorted ASC by weight
    Edge** edges = g.getSortedEdges();

    // Clear all next and prev vertices pointers, because union-find need to use them
    g.clearVertices();

    // Runs on all edges
    for (size_t i = 0; i < g.getnEdges(); i++){
        Vertex* v1 = edges[i]->getV1();
        Vertex* v2 = edges[i]->getV2();

        // Check if v1 and v2 are in the same group, if not than union them
        // And add a corresponding edge to result graph
        if (!v1->isUnioun(v2))
            result->addEdge(v1->getID(), v2->getID(), edges[i]->getWeight());
    }

    delete[] edges;
  
    return result;
}
