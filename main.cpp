// liorbrown@outlook.co.il

#include "Algorithms.hpp"

using namespace std;
using namespace graph;

int main(){
    Graph g{6};

    g.addEdge(3,4,10);
    g.addEdge(3,5);
    g.addEdge(3,0,7);
    g.addEdge(1,0,7);
    g.addEdge(4,5);
    g.addEdge(2,3,5);

    cout << "Original graph" << endl;
    g.print_graph();

    cout << "BFS" << endl;
    Graph* result = Algorithms::bfs(g, 0);
    result->print_graph();
    delete result;

    result = Algorithms::bfs(g, 2);
    result->print_graph();
    delete result;

    cout << "DFS" << endl;
    result = Algorithms::dfs(g, 2);
    result->print_graph();
    delete result;

    cout << "Dijkstra" << endl;
    result = Algorithms::dijkstra(g, 2);
    result->print_graph();
    delete result;

    cout << "Prim" << endl;
    result = Algorithms::prim(g);

    if (!result)
        cout << "Graph not connected" << endl;
    else{
        result->print_graph();
        delete result;
    }

    cout << "Kruskal" << endl;
    result = Algorithms::kruskal(g);
    
    if (!result)
        cout << "Graph not connected" << endl;
    else{
        result->print_graph();
        delete result;
    }
}