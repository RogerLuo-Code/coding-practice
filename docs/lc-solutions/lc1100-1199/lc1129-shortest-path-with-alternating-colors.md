---
tags:
    - Breadth-First Search
---

# LC1129. Shortest Path with Alternating Colors

## Problem Description

[LeetCode Problem 1129](https://leetcode.com/problems/shortest-path-with-alternating-colors/): You are given an integer `n`, the number of nodes in a directed graph where the nodes are labeled from `0` to `n - 1`. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.

You are given two arrays `redEdges` and `blueEdges` where:

- `redEdges[i] = [ai, bi]` indicates that there is a directed red edge from node `ai` to node `bi`in the graph, and
- `blueEdges[j] = [uj, vj]` indicates that there is a directed blue edge from node `uj` to node `vj` in the graph.

Return an array `answer` of length `n`, where each `answer[x]` is the length of the shortest path from node `0` to node `x` such that the edge colors alternate along the path, or `-1` if such a path does not exist.

## Clarification

- Directed graph with self-edges and parallel edges
- Shortest path from 0 to x with alternating color on edges
- redEdges and blueEdges mapped to nodes? ith edge corresponding to ith node?

## Assumption

-

## Solution

### Approach - BFS

Do a breadth-first search, where the "nodes" are actually (Node, color of last edge taken). Use `visited` to track node with the last edge color.

=== "Python"
    ```python
    from collections import deque

    class Solution:
        def __init__(self):
            self.RED = 0
            self.BLUE = 1

        def shortestAlternatingPaths(self, n: int, redEdges: List[List[int]], blueEdges: List[List[int]]) -> List[int]:
            answer = [-1] * n
            queue = deque([(0, -1)])  # Add (node, last_edge_color) pair, node 0, with no last edge color (-1)
            visited = set([(0, -1)])

            # Convert edge list with different colors to one node adjacent list with color
            adj_list = [[] for _ in range(n)]
            for edge in redEdges:
                adj_list[edge[0]].append((edge[1], self.RED))

            for edge in blueEdges:
                adj_list[edge[0]].append((edge[1], self.BLUE))

            path_len = 0
            while queue:
                size = len(queue)

                for _ in range(size):
                    node, last_edge_color = queue.popleft()
                    if answer[node] == -1:
                        answer[node] = path_len

                    for next_node_edge_color in adj_list[node]:
                        if next_node_edge_color[1] != last_edge_color and next_node_edge_color not in visited:
                            queue.append(next_node_edge_color)
                            visited.add(next_node_edge_color)

                path_len += 1

            return answer
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n + e)$ where $n$ is number of nodes and $e$ is number of edges  
  The total time complexity consists of:
    - Converting edges to node adjacent list takes $O(e)$
    - For BFS, each queue operation takes $O(1)$ time and each node will be visited at most twice (one for blue edge and one for red edge), which takes $O(n)$. For each node, it will go through all edges, both blue and red ones, which takes total $O(e)$. So the time complexity for BFS is $O(n + e)$
- Space complexity: $O(n + e)$  
    - Build the adjacent list takes $O(e)$ space.
    - The BFS queue takes $O(2 \times 2 \times n) = O(n)$. Each node is added at most twice in the form of two integers tuple `(node, edge color)`.
    - The answer takes $O(n)$ space.
    - The visited takes $O(2 \times 2 \times n) = O(n)$ since each node can be visited at most twice (blue and red edges) in the form of two integer tuple `(node, edge color)`.

## Test
