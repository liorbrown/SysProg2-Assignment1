This project was carried out as part of a bachelor's degree in computer and software engineering at Ariel University. 
The goal of the project is to implement data structures and algorithms that we learned during our studies, 
in the C++ language, in order to practice writing correct code, and to examine the ability to actually implement topics that were learned theoretically.

The assignment focuses on implementing a simple weighted and undirected graph, and performing several basic algorithms related to graphs:
1. BFS
2. DFS
3. Dijkstra
4. Prim
5. Kruskal

I implemented the graph in the form of an adjacency list, using the OOP method as described on this page - https://en.wikipedia.org/wiki/Adjacency_list
The main idea of ​​the solution is to create 2 additional classes for the graph itself - vertex and an edge, 
where the graph contains an array of vertices of a fixed size that cannot be changed, and a list of edges that is updated. 
Each vertex holds a pointer for the list of edges that come out of it, 
and each edge holds a vote for the 2 vertices connected to it. 
This solution generates more work in the operations of adding and removing edges, 
but ultimately the multiple pointers generate a lot of convenience in implementing the algorithms.

For the purpose of implementing the algorithms, I also created 2 auxiliary classes of queue and stack.
Their implementation is not the original implementation, since it does not meet their real running complexity, 
but in terms of functionality they provide everything that is required to implement the algorithms implemented in the project.

The algorithms themselves are implemented in a static class, which contains all the implementations.

The project also contains a comprehensive test file of the algorithms, a MAKE file with options to run from MAIN, from the tests, or to run valgrind.

The project has been tested by valgrind and currently has 0 memory leaks.

All 1532 lines of code in the project were written by me alone. During
the implementation of the project, I did not resort to the help of AI at all, 
and I solved all the technical difficulties myself, in order to truly create an opportunity for myself to learn and solve challenges in the ultimate way.
