#pragma once

#include "Graph.hpp"

namespace graph{

    class Algorithms{
        private:
            Algorithms(){}
            static void setVAttributes(const Graph&, Vertex*);
            static void initAttributes(const Graph&);
            static Graph* buildGraph(const Graph&);
            static void dfsVisit(const Graph&, Vertex*);
            static void relax(const Edge&, Vertex*);

        public:
            static Graph* bfs(const Graph &, const unsigned int);
            static Graph* dfs(const Graph&, const unsigned int);
            static Graph* dijkstra(const Graph&, const unsigned int);
            static Graph* prim(const Graph&);
            static Graph* kruskal(const Graph&);
    };
}