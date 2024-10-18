# Breadth-first Search (BFS)

The breadth-first search (BFS) is usually used to

- traverse all vertices in a graph;
- find the shortest path between two vertices in a graph where all edges have equal and positive weights.

Sometimes, need a `visited` hash set to track nodes visited to prevent getting stuck in an infinite loop, e.g., in graph with cycle.

Note may not need to use a `visited`. Can check the existing value to indicate whether it is visited or not.