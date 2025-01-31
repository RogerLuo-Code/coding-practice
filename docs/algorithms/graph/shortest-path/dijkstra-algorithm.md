# Dijkstra's Algorithm

Dijkstra's Algorithm uses a greedy approach. Each step selects the minimum weight from
currently reached vertices to find the shortest path to other vertices.

The greedy approach only guarantees that each step takes the optimal choice in the current
state. How does Dijkstra's algorithm ensure that the final result is optimal? Require edge
has non-negative weight.

Limitation: can only work on graphs with non-negative weights.

