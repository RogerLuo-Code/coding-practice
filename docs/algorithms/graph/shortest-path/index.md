# Overview of Single Source Shortest Path

Breadth-first search (BFS) algorithm is used to find the shortest path in **unweighted**
graphs.

For a weighted graph, the BSF doesn't work. There are two common single source shortest
path algorithms.

1. [Dijkstra's algorithm](dijkstra-algorithm.md) (only works with **non-negative** weights)
2. [Bellman-Ford algorithm](bellman-ford-algorithm.md) (works with any weights) --> 
improved version, [shortest path faster algorithm](shortest-path-faster-algorithm.md)

**Edge relaxation** is to select the shortest path between two nodes.

