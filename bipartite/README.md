## Bipartite Graph Detection

g++ -std=c++11 biparti.cpp

This program show an algorithm for bipartite graph detection.

The graph is represented like this in the structure:
0 1 3
1 2 0
2 1
3 0

At each line, the first number is the id of the node and the others are the linked nodes.
The algorithm is tested on a random generated graph and a manually generated graph.
If the graph is a bipartite graph, then the two sets of nodes are shown.