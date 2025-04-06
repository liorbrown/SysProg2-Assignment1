CXX=g++
CXXFLAGS=-std=c++2a -g -c

.PHONY: clean Main test valgrind build

Main: build
	./main.out

valgrind: build
	valgrind --leak-check=yes ./main.out
	$(CXX) GraphTest.o Graph.o Heap.o Queue.o Algorithms.o -o test.out
	valgrind --leak-check=yes ./test.out

test: GraphTest.o Graph.o Heap.o Queue.o Algorithms.o
	$(CXX) $^ -o test.out
	./test.out

build: main.o Graph.o Heap.o Queue.o Algorithms.o
	$(CXX) $^ -o main.out

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

GraphTest.o: GraphTest.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Graph.o: Graph.cpp Graph.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Heap.o: Heap.cpp Heap.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Queue.o: Queue.cpp Queue.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Algorithms.o: Algorithms.cpp Algorithms.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o *.out