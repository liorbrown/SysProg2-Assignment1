#pragma once

namespace graph{
    class Edge{
        private:
            const static int DEFAULT_W = 1;
            int weight;
            Vertex* v1;
            Vertex* v2;
            Edge* next;
 
        public:
            Edge(Vertex* v1, Vertex* v2, int weight):v1(v1), v2(v2), weight(weight), next(nullptr){}
            Edge(Vertex* v1, Vertex* v2) {Edge(v1,v2,DEFAULT_W);}
    };

    class Vertex{
        private:
            int degree;
            Edge* edges;

        public:
            Vertex():degree(0), edges(nullptr){}
    };

    class Graph{
        private:
            int negativeEdges;
            int nCount;
            Vertex* vertices;
            Edge* edges;
            
        public:
            Graph(int nVertices): 
                nCount(nVertices), 
                vertices(new Vertex[nVertices]), 
                edges(nullptr),
                negativeEdges(0){}
            bool addEdge(int v1, int v2, int weight);
            bool addEdge(int v1, int v2);
            void removeEdge(int v1, int v2);
            void print_graph() const;
    };
}