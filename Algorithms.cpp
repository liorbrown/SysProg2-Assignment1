#include "Algorithms.hpp"
#include "Queue.hpp"
#include <stdexcept>

#define VERTEX_NULL -1

using namespace graph;

Graph *Algorithms::bfs(const Graph &g, const unsigned int s)
{
    const unsigned int nVertices = g.getnVertices();

    if (s >= nVertices)
        throw out_of_range{"The given vertices not exist in graph 🫤"};

    int* pi = new int[nVertices];

    setVAttributes(nVertices, pi, s, g);
    Graph* result = buildGraph(nVertices, pi);

    return result;
}

void Algorithms::setVAttributes(const unsigned int nVertices, 
                                int *pi, 
                                const unsigned int s, 
                                const Graph &g)
{
    vColor* vColors = new vColor[nVertices];

    initAttributes(nVertices, vColors, pi);

    vColors[s] = GRAY;
    pi[s] = VERTEX_NULL;

    Queue q;

    q.enqueue(s);

    while (!q.isEmpty())
    {
        int v = q.dequeue();

        unsigned int *adjacents = g.getAdjacents(v);

        for (size_t i = 0; i < g[v].getDegree(); i++)
        {
            unsigned int adjacent = adjacents[i];

            if (vColors[adjacent] == WHITE)
            {
                vColors[adjacent] = GRAY;
                pi[adjacent] = v;
                q.enqueue(adjacent);
            }
        }

        delete adjacents;

        vColors[v] = BLACK;
    }
}

void Algorithms::initAttributes(const unsigned int nVertices, vColor *vColors, int *pi)
{
    for (size_t i = 0; i < nVertices; i++)
    {
        vColors[i] = WHITE;
        pi[i] = VERTEX_NULL;
    }
}

Graph *Algorithms::buildGraph(const unsigned int nVertices, int *pi){
    Graph* result = new Graph(nVertices);

    for (size_t i = 0; i < nVertices; i++)
        if (pi[i] != VERTEX_NULL)
            result->addEdge(i, pi[i]);
    
    return result;
}

Graph *Algorithms::dfs(const Graph &g, const unsigned int s){

    const unsigned int nVertices = g.getnVertices();
    int* pi = new int[nVertices];
    vColor* vColors = new vColor[nVertices];
    
    initAttributes(nVertices, vColors, pi);

    for (size_t i = 0; i < nVertices; i++)
    {
        size_t v = i + s % nVertices;

        if (vColors[v] == WHITE)
            dfsVisit(g, v, vColors, pi);
    }

    Graph* result = buildGraph(nVertices, pi);

    return result;
}

void Algorithms::dfsVisit(const Graph &g, const unsigned int v, vColor* vColors, int* pi){
    
    vColors[v] = GRAY;

    const unsigned int* adjacents = g.getAdjacents(v);

    for (size_t i = 0; i < g[v].getDegree(); i++)
    {
        const unsigned int adjacent = adjacents[i];

        if (vColors[adjacent] == WHITE){
            pi[adjacent] = v;
            dfsVisit(g, adjacent, vColors, pi);
        }
    }

    delete adjacents;

    vColors[v] = BLACK;
}

Graph* Algorithms::dijkstra(const Graph &g, const unsigned int s)
{
    Graph* result = new Graph(g.getnVertices());
    return result;
}

Graph *Algorithms::prim(const Graph &g)
{
    Graph* result = new Graph(g.getnVertices());
    return result;
}

Graph *Algorithms::kruskal(const Graph &g)
{
    Graph* result = new Graph(g.getnVertices());
    return result;
}
