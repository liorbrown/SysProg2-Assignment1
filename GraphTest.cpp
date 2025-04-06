// liorbrown@outlook.co.il

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.hpp"
#include "Algorithms.hpp"
#include "Queue.hpp"
#include "Heap.hpp"

using namespace graph;

/// @brief Check if 2 edges are equal, for testing purpose 
/// @param e1 Edge 1
/// @param e2 Edge 2
/// @return True if they equal, False otherwise
bool operator==(const Edge& e1, const Edge& e2){
    return ((e1.getV1()->getID() == e2.getV1()->getID() &&
            e1.getV2()->getID() == e2.getV2()->getID() ||
            e1.getV1()->getID() == e2.getV2()->getID() &&
            e1.getV2()->getID() == e2.getV1()->getID()) &&
            e1.getWeight() == e2.getWeight());
}

/// @brief Check if 2 graphs are equal, for testing purpose 
/// @param g1 Graph 1
/// @param g2 Graph 2
/// @return True if they equal, False otherwise
bool operator==(const Graph& g1, const Graph& g2){
    // Check first if number of vertices and edges are equals
    if (g1.getnVertices() != g2.getnVertices() ||
        g1.getnEdges() != g2.getnEdges())
        return false;
    
    Edge** g1Edges = g1.getSortedEdges();
    Edge** g2Edges = g2.getSortedEdges();

    bool isFound = true;

    // Runs on all edges in first graph
    for (size_t i = 0; i < g1.getnEdges() && isFound; i++){
        isFound = false;

        // Checks for each if it have corresponding edge in seconed graph
        for (size_t j = 0; j < g2.getnEdges() && !isFound; j++)
            isFound = *g1Edges[i] == *g2Edges[j];
    }    
    
    return isFound;
}

/// @brief Check if vertex v caontained in given list
/// @param list Vertices list
/// @param size List size
/// @param v Vertex to check
/// @return True - if vertex is in list, False otherwise
bool contains(Vertex** list, const unsigned int size, const unsigned int v){

    // Runs on all list and search for given vertex v
    for (size_t i = 0; i < size; i++)
        if (list[i]->getID() == v)
            return true;
    
    return false;   
}

TEST_CASE("Creating graph"){
    Graph g{6};

    CHECK_EQ(g.getnVertices(), 6);
    CHECK_EQ (g.getnEdges(),0);
    CHECK_FALSE(g.isNegative());
    
    CHECK_EQ(g[2].getID(), 2);
    CHECK_EQ(g[4].getID(), 4);
    CHECK_EQ(g[4].getDegree(), 0);
}

TEST_CASE("Adding and removing edges"){
    Graph g{6};

    CHECK_EQ (g.getnEdges(), 0);

    g.addEdge(1,4,10);
    g.addEdge(1,3,-5);
    g.addEdge(1,5);
    g.addEdge(2,4,5);

    CHECK_EQ (g.getnEdges(), 4);
    CHECK (g.isNegative());

    // Check adding of existing edge
    CHECK_THROWS_AS(g.addEdge(1,5), invalid_argument);

    // Check adding of edge from vertex to itself
    CHECK_THROWS_AS(g.addEdge(5,5), invalid_argument);

    // Check add and remove edge of vertices that not exist in graph
    CHECK_THROWS_AS(g.addEdge(1,10), out_of_range);
    CHECK_THROWS_AS(g.removeEdge(1,9), out_of_range);

    // Check removing of edge that is not in graph
    CHECK_THROWS_AS(g.removeEdge(2,3), invalid_argument);
    CHECK_THROWS_AS(g.removeEdge(2,2), invalid_argument);

    g.removeEdge(1,3);

    // Check removing success
    CHECK_EQ (g.getnEdges(), 3);
    CHECK_FALSE (g.isNegative());
}

TEST_CASE("Get sorted edges"){
    Graph g{6};

    Edge** edges = g.getSortedEdges();

    // Check when run it on graph without edges
    CHECK_EQ (edges, nullptr);

    g.addEdge(1,4,10);
    g.addEdge(1,3,-5);
    g.addEdge(1,5);
    g.addEdge(2,4,5);

    edges = g.getSortedEdges();
    
    // Check the sort order, that differrent from insertion order
    CHECK_EQ(edges[0]->getWeight(), -5);
    CHECK_EQ(edges[1]->getWeight(), 1);
    CHECK_EQ(edges[2]->getWeight(), 5);
    CHECK_EQ(edges[3]->getWeight(), 10);
}

TEST_CASE("Get adjacents"){
    Graph g{6};

    Vertex** adjacents = g[1].getAdjacents();

    // Check of vertex without adjacents
    CHECK_EQ(adjacents, nullptr);

    g.addEdge(1,4,10);
    g.addEdge(1,3,-5);
    g.addEdge(1,5);
    g.addEdge(2,4,5);

    // Check getDegree is good
    CHECK_EQ (g[1].getDegree(), 3);

    adjacents = g[1].getAdjacents();
    
    // Check if all adjacents are ijn the array
    CHECK(contains(adjacents, 3, 3));
    CHECK(contains(adjacents, 3, 4));
    CHECK(contains(adjacents, 3, 5));
}

TEST_CASE("Get vertex weight"){
    Graph g{6};

    CHECK_THROWS_AS(g[2].getWeight(&g[3]),runtime_error);

    g.addEdge(1,4,10);
    g.addEdge(1,3,-5);
    g.addEdge(1,5);
    g.addEdge(2,4,5);

    int weight = g[1].getWeight(&g[3]);

    CHECK_EQ (weight, -5);
}

TEST_CASE("Is union function"){
    Graph g{6};

    // Check that first they are not union
    CHECK_FALSE(g[4].isUnion(&g[2]));

    // After we run isUnion, they suppose to be union
    CHECK(g[4].isUnion(&g[2]));

    CHECK_FALSE(g[3].isUnion(&g[4]));
    CHECK(g[3].isUnion(&g[4]));

    // Check that 3 and 2 union, even if not connected directly
    CHECK(g[3].isUnion(&g[2]));
}

TEST_CASE("Queue test"){
    Graph g{6};

    Queue q;

    CHECK (q.isEmpty());

    // Try dequeue empty queue
    CHECK_THROWS_AS(q.dequeue(), runtime_error);

    q.enqueue(&g[2]);
    q.enqueue(&g[1]);
    q.enqueue(&g[5]);

    CHECK_FALSE(q.isEmpty());

    // Check if vertices goes out in the insertion order
    CHECK_EQ(q.dequeue()->getID(), 2);
    CHECK_EQ(q.dequeue()->getID(), 1);
    CHECK_EQ(q.dequeue()->getID(), 5);

    CHECK (q.isEmpty());
}

TEST_CASE("Heap test"){
    Graph g{6};

    Heap q;

    CHECK (q.isEmpty());

    // Check extraction from empty queue
    CHECK_THROWS_AS(q.extractMin(), runtime_error);

    g[2].getD() = 8;
    g[5].getD() = 3;
    g[4].getD() = 5;
    g[0].getD() = 0;

    q.insert(&g[2]);
    q.insert(&g[4]);
    q.insert(&g[0]);
    q.insert(&g[5]);

    CHECK_FALSE(q.isEmpty());

    // Check that they pulled out order by d attribute
    CHECK_EQ(q.extractMin()->getID(), 0);
    CHECK_EQ(q.extractMin()->getID(), 5);
    CHECK_EQ(q.extractMin()->getID(), 4);
    CHECK_EQ(q.extractMin()->getID(), 2);

    CHECK (q.isEmpty());
}

TEST_CASE("BFS test"){
    Graph g{6};

    // Check of given not exist vertex
    CHECK_THROWS_AS(Algorithms::bfs(g,8), out_of_range);

    Graph* result = Algorithms::bfs(g, 2);

    // Check if handling right graph without edges
    CHECK(*result == g);

    g.addEdge(1,4,10);
    g.addEdge(1,3,-5);
    g.addEdge(1,5);
    g.addEdge(2,4,5);
    g.addEdge(2,5,0);

    result = Algorithms::bfs(g, 0);
    Graph excpected{6};

    // Check bfs tree from detached vertex
    CHECK(*result == excpected);

    result = Algorithms::bfs(g, 2);

    excpected.addEdge(1,3,-5);
    excpected.addEdge(2,4,5);
    excpected.addEdge(2,5,0);
    excpected.addEdge(1,5);

    // Check of tree from connected vertex
    CHECK(*result == excpected);

    result = Algorithms::bfs(g, 3);

    excpected.removeEdge(2,4);
    excpected.addEdge(1,4,10);

    // Check that result changes when run on different vertex
    CHECK(*result == excpected);

    g.removeEdge(1,4);
    
    result = Algorithms::bfs(g, 3);

    excpected.removeEdge(1,4);
    excpected.addEdge(2,4,5);

    // Check if updates its path to 4
    CHECK(*result == excpected);
}

TEST_CASE("Dijkstra test"){
    Graph g{6};

    // Check running dijkstra on vertex not exist in graph
    CHECK_THROWS_AS(Algorithms::dijkstra(g,8), out_of_range);

    Graph* result = Algorithms::dijkstra(g, 2);

    // Check if handling right graph without edges
    CHECK(*result == g);

    g.addEdge(1,4,10);
    g.addEdge(1,3,-5);
    g.addEdge(1,5);
    g.addEdge(2,4,5);
    g.addEdge(2,5,0);

    // Check running dijkstra on negative graph
    CHECK_THROWS_AS(Algorithms::dijkstra(g, 2),domain_error);

    g.removeEdge(1,3);
    g.addEdge(1,3,20);

    result = Algorithms::dijkstra(g, 0);
    Graph excpected{6};

    // Check result from detached vertex
    CHECK(*result == excpected);

    result = Algorithms::dijkstra(g, 2);

    excpected.addEdge(1,3,20);
    excpected.addEdge(2,4,5);
    excpected.addEdge(2,5,0);
    excpected.addEdge(1,5);

    // Check result from connected vertex
    CHECK(*result == excpected);

    result = Algorithms::dijkstra(g, 3);

    CHECK(*result == excpected);
}

TEST_CASE("DFS test"){
    Graph g{6};

    // Check running DFS on vertex not exist in graph
    CHECK_THROWS_AS(Algorithms::dfs(g, 9), out_of_range);

    // Check if handling right graph without edges
    Graph* result = Algorithms::dfs(g, 2);
    CHECK(*result == g);
       
    g.addEdge(1,4,10);
    g.addEdge(1,3,-5);
    g.addEdge(1,5);
    g.addEdge(2,4,5);
    g.addEdge(2,5,0);

    result = Algorithms::dfs(g, 0);
    
    Graph excpected{6};
    excpected.addEdge(1,3,-5);
    excpected.addEdge(2,4,5);
    excpected.addEdge(2,5,0);
    excpected.addEdge(1,5);

    // Check result from detached vertex
    CHECK(*result == excpected);

    result = Algorithms::dfs(g, 2);

    excpected.addEdge(1,4,10);
    excpected.removeEdge(2,4);

    // Check result from detached vertex
    CHECK(*result == excpected);

    result = Algorithms::dfs(g, 3);

    excpected.removeEdge(1,4);
    excpected.addEdge(2,4,5);

    // Check that result changes when running from different vertex
    CHECK(*result == excpected);

    g.removeEdge(1,4);
    g.removeEdge(1,5);
    g.addEdge(1,0);

    excpected.removeEdge(1,5);
    excpected.addEdge(0,1);

    result = Algorithms::dfs(g, 3);

    // Check for graph that have many of connected components
    CHECK(*result == excpected);
}

TEST_CASE( "Prim test"){
    Graph g{6};

    // Check running prim on graph without edges
    CHECK_EQ(Algorithms::prim(g), nullptr);
           
    g.addEdge(1,4,10);
    g.addEdge(1,3,-5);
    g.addEdge(1,5);
    g.addEdge(2,4,5);
    g.addEdge(2,5,0);

    // Check running prim on not connected graph
    CHECK_EQ(Algorithms::prim(g), nullptr);
    
    g.addEdge(0,5,0);
    g.addEdge(1,2,30);
    
    Graph* result = Algorithms::prim(g);
    
    Graph excpected{6};
    excpected.addEdge(1,3,-5);
    excpected.addEdge(1,5);
    excpected.addEdge(2,5,0);
    excpected.addEdge(0,5,0);
    excpected.addEdge(2,4,5);

    // Check running prim on connected graph
    CHECK(*result == excpected);
}

TEST_CASE( "Kruskal test"){
    Graph g{6};

    // Check running prim on graph without edges
    CHECK_EQ(Algorithms::kruskal(g), nullptr);
           
    g.addEdge(1,4,10);
    g.addEdge(1,3,-5);
    g.addEdge(1,5);
    g.addEdge(2,4,5);
    g.addEdge(2,5,0);

    // Check running prim on not connected graph
    CHECK_EQ(Algorithms::kruskal(g), nullptr);
    
    g.addEdge(0,5,0);
    g.addEdge(1,2,30);
    
    Graph* result = Algorithms::kruskal(g);
    
    Graph excpected{6};
    excpected.addEdge(1,3,-5);
    excpected.addEdge(1,5);
    excpected.addEdge(2,5,0);
    excpected.addEdge(0,5,0);
    excpected.addEdge(2,4,5);

    // Check running prim on connected graph
    CHECK(*result == excpected);
}