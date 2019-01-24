## Graph Coloring

g++ -std=c++11 coloration.cpp

This program show an algorithm for graph coloring.

The graph is represented like this in the structure:
0 1 3
1 2 0
2 1
3 0

At each line, the first number is the id of the node and the others are the linked nodes.
The algorithm is tested on a random generated graph.
The algorithm first sort the graph by decreasing degree then process to the coloring.