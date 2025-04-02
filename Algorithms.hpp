#pragma once

#include "Graph.hpp"
namespace graph{
    enum vColor{
        WHITE, GRAY, BLACK
    };

    class Algorithms{
        private:
            Algorithms(){}
            static void setVAttributes(const unsigned int nVertices,
                                int *pi,
                                const unsigned int s,
                                const Graph &g);
            static void initAttributes(const unsigned int nVertices, vColor *vColors, int *pi);
            static Graph* buildGraph(const unsigned int nVertices, int *pi);
            static void dfsVisit(const Graph &g, const unsigned int, vColor*, int*);

        public:
            static Graph* bfs(const Graph &, const unsigned int);
            static Graph* dfs(const Graph&, const unsigned int);
            static Graph* dijkstra(const Graph&, const unsigned int);
            static Graph* prim(const Graph&);
            static Graph* kruskal(const Graph&);
    };
}