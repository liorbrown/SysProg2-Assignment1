#pragma once

#include "Graph.hpp"

namespace graph{

    class Algorithms{
        private:
            Algorithms(){}
            static void setVAttributes(Graph&, Vertex*);
            static void initAttributes(Graph&);
            static Graph* buildGraph(Graph&);
            static void dfsVisit(Graph&, Vertex*);
            static void relax(const Edge&, Vertex*);
            static bool isConnect(Graph&);

        public:
            static Graph* bfs(Graph&, const unsigned int);
            static Graph* dfs(Graph&, const unsigned int);
            static Graph* dijkstra(Graph&, const unsigned int);
            static Graph* prim(Graph&);
            static Graph* kruskal(Graph&);
    };
}