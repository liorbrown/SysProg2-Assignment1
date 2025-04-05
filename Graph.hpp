#pragma once

#include <iostream>

using namespace std;

namespace graph{

    // This is enum is used in BF & DFS algorithms
    enum vColor{
        WHITE, GRAY, BLACK
    };

    // This "strange" declaration is needed because Vertex is depend on EdgeNode
    // but EdgeNode depend on Edge and Edge depend on vertx
    // so the solution for this plonter is to declare EdgeNode twice
    class EdgeNode;

    /// @brief this class represent vertex in graph
    /// the class include basic data of vertex like id and degree
    /// and also enhanced data like pi, d & color that is used for algorithms
    class Vertex{
        private:
            // Basic data
            unsigned int id;
            unsigned int degree;
            EdgeNode* edges;

            // Enhanced data for algorithms usage
            unsigned int d;
            Vertex* pi;
            vColor color;

            // Data that used for data structures 
            // that contains the vertex like heap, queue , etc.
            Vertex* next;
            Vertex* prev;

            // I aware that this not pure oop practice that object know the structure that contains it
            // but i prefer this for get better efficiency in the algorithm
            bool isInHeap;

        public:
            Vertex():
                degree(0), 
                edges(nullptr), 
                next(nullptr), 
                prev(nullptr), 
                isInHeap(false){}

            /// @brief Destructor - delete vertex edges list
            ~Vertex();

            // Geters & seters
            unsigned int getID() const {return this->id;}
            unsigned int& getID() {return this->id;}
            unsigned int getDegree() const {return this->degree;}
            EdgeNode* getEdges() const { return this->edges;}
            EdgeNode*& getEdges() { return this->edges;}
            
            unsigned int getD() const {return this->d;}
            unsigned int& getD() {return this->d;}
            Vertex* getPI() const {return this->pi;}
            Vertex*& getPI() {return this->pi;}
            vColor getColor() const {return this->color;}
            vColor& getColor() {return this->color;}

            Vertex* getNext() const {return this->next;}
            Vertex*& getNext(){return this->next;}
            Vertex* getPrev() const {return this->prev;}
            Vertex*& getPrev(){return this->prev;}
            bool getIsInHeap() const {return this->isInHeap;}
            bool& getIsInHeap() {return this->isInHeap;}

            /// @brief Get all adjacents vertices of this vertex
            /// @return Array of pointers to adjacents vertices
            Vertex** getAdjacents() const;
            
            /// @brief Get the weight of the edge that connect this vertex to given vertex
            /// @param  v Vertex to check weight of edge to it
            /// @return the weight of the edge that connect this vertex to given vertex
            int getWeight(const Vertex* v) const;

            /// @brief Check if this and given vertices are in the same group, in terms of union-find groups,
            /// and also union the to vertices groups in the end to one group.
            /// NOTE: Actualy this function is implement all the union-find structure wtihout really create 
            /// union-find structure. this possible only because the assingment not requierd get real union-find
            /// complexity, so i do it realy simple in one function that  give me exactly 
            /// the same functionality of union-find structure
            /// @param v Vertex to check and union this vertex with
            /// @return True - if vertices "was" in same group before function, False otherwise
            /// in any case in the end of function they will be in same grouop
            bool isUnioun(Vertex* v); 

            /// @brief This operator increase vertex degree
            /// @return This vertex "After" increasment
            Vertex& operator++(){
                this->degree++;
                return *this;
            }

            /// @brief This operator decrease vertex degree
            /// @return THis vertex "After" decreasment
            Vertex& operator--(){
                this->degree--;
                return *this;
            }
    };

    /// @brief This class represented edge in graph
    class Edge{

        private:
            const int weight;
            Vertex* v1;
            Vertex* v2;
       
        public:
            Edge(Vertex* v1, Vertex* v2, const int weight):
                v1(v1), 
                v2(v2), 
                weight(weight){}
            
            // Geters only. no changes aloowed once edge created
            int getWeight() const {return this->weight;}
            Vertex* getV1() const {return this->v1;}
            Vertex* getV2() const {return this->v2;}

            /// @brief This function gets one vertex of this edge, and return the other one 
            /// @param v The vertex to check its neighbor
            /// @return The other vertex of this edge
            Vertex* getAdjacent(const Vertex* v) const{
                return (this->v1 == v ? this->v2 : this->v1);
            }

            /// @brief Output operator for print edge data
            /// @param os stream to move data to it
            /// @param e Edge o get its data
            /// @return The given stream
            friend ostream& operator<<(ostream& os, const Edge& e);
    };
  
    /// @brief This class is container of the Edge class, and its purpose is to enabled creating of
    /// edges linked lists. note that because we want that the same edge could be linked in different lists
    /// like the graph general list and the vertices edges lists, so we have have to sepperate the edge itself
    /// from the node in list. thus we can create one edge, and list it in many lists
    class EdgeNode{
        private:
            Edge* edge;
            EdgeNode* next;

        public:
            EdgeNode(Edge* edge): edge(edge), next(nullptr){}

            // Geters & setter
            Edge* getEdge() const { return this->edge;}
            EdgeNode* getNext() const { return this->next;}
            EdgeNode*& getNext(){ return this->next;}
    };

    /// @brief This class represent a simple a-directed weighted graph
    /// with const amount of vertices
    class Graph{
        private:
            const static int DEFAULT_W = 1;

            unsigned int nEdges;
            unsigned int negativeEdges;
            const unsigned int nVertices;
            Vertex* vertices;
            EdgeNode* edges;

            /// @brief This method adds new edge to given edges list
            /// @param e The new edge to add
            /// @param list The edges list to ass new edge to it
            void addEdge(Edge* e, EdgeNode*& list);

            /// @brief This method remove given edge from given edges list
            /// @param e Edge to remove
            /// @param Pointer to edge list to remove from
            void removeEdge(const Edge* e, EdgeNode** previous);
            
        public:
            Graph(const unsigned int nVertices);

            /// @brief Destructor - delete edges list
            ~Graph();

            // Geters
            unsigned int getnVertices() const {return this->nVertices;}
            unsigned int getnEdges() const {return this->nEdges;}

            /// @brief Check if graph have negative edges
            /// @return True if have negative edges, False otherwise
            bool isNegative() const {return this->negativeEdges;}
            
            /// @brief This method add to graph new edge between 2 given vertices
            /// @param v1 Vertex 1 id
            /// @param v2 Vertex 2 id
            /// @param weight Edge weight. Default = 1
            void addEdge(const unsigned int v1, const unsigned int v2, const int weight = DEFAULT_W);

            /// @brief This method remove the edge between 2 vertices from graph
            /// @param v1 Vertex 1 id
            /// @param v2 Vertex 2 id
            void removeEdge(const unsigned int v1, const unsigned int v2);

            /// @brief Print graph data
            void print_graph() const;
            
            /// @brief Creates array of pointers to all graph edges, sorted ASC by edges weight 
            /// @return The sorted array
            Edge** getSortedEdges() const;
            
            /// @brief This method sets to null the next and prev members of all vertices.
            /// this need to be called before creating of structures like queue and heap
            /// that using those attributes, to avoid irrelevant prior data
            void clearVertices() const;

            /// @brief This [] operator גesigned to make it easier to access vertices, 
            /// as this is a very repetitive operation.
            /// @param v Vertex id
            /// @return The wanted vertex
            Vertex& operator[](const int v) const {return this->vertices[v];}
    };
}