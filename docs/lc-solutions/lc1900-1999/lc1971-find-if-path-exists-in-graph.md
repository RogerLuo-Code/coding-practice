---
tags:
    - Breadth-First Search
    - Depth-First Search
    - Union Find
---

# LC1973. Find if Path Exists in Graph

## Problem Description

[LeetCode Problem 1973](https://leetcode.com/problems/find-if-path-exists-in-graph/): There is a **bi-directional** graph with `n` vertices, where each vertex is labeled from `0` to `n - 1` (**inclusive**). The edges in the graph are represented as a 2D integer array `edges`, where each `edges[i] = [ui, vi]` denotes a bi-directional edge between vertex `ui` and vertex `vi`. Every vertex pair is connected by **at most one** edge, and no vertex has an edge to itself.

You want to determine if there is a **valid path** that exists from vertex `source` to vertex `destination`.

Given `edges` and the integers `n`, `source`, and `destination`, return `true` _if there is a **valid path** from_ `source` _to_ `destination`_, or_ `false` _otherwise__._

## Clarification

- bi-directional and no self-loop
- at most 1 edge between vertices
- can source and destination be the same?

## Assumption

-

## Solution

Go through edges and construct vortex matrix and then use either BFS or DFS to check if path exists

### Approach - BFS

=== "Python"
    ```python
    class Solution:
        def validPath(self, n: int, edges: List[List[int]], source: int, destination: int) -> bool:
            vertices = [[] for _ in range(n)]
            for edge in edges:  # (1)
                vertices[edge[0]].append(edge[1])
                vertices[edge[1]].append(edge[0])

            queue = deque([source])
            visited = set([source])
            while queue:
                curr_node = queue.popleft()
                if curr_node == destination:  # (2)
                    return True
                for next_node in vertices[curr_node]:
                    if next_node not in visited:
                        queue.append(next_node)
                        visited.add(next_node)

            return False
    ```

    1. Add both edges since it is a bi-directed graph.  Each node may add duplicate values, which will be handled by visited later.
    2. Can handle normal cases and special case where source and destination are the same node

#### Complexity Analysis of Approach 1

- Time complexity: $O(V + E)$  
  The time complexity consists of:

    - Build vertices matrix by visiting all `E` edges, which takes $O(E)$   
    - In BFS, each vertex is only visited once, it takes $O(V)$ to traverse all nodes. 

- Space complexity: $O(V + E)$  
  The space used consists of:

     - Use a list to store all edges, which take $O(2 \times E) = O(E)$ space  
     - Use `visited` to track visited nodes, which takes $O(V)$ in the worst case
     - Use `queue` to traverse nodes, which takes $O(v)$ in the worst case


### Approach 2 - DFS

Solution

=== "python"
    ```python
    class Solution:
    def validPath(self, n: int, edges: List[List[int]], source: int, destination: int) -> bool:
        vertices = [[] for _ in range(n)]
        for edge in edges:
            # Undirected graph and it's okay to add redundant nodes
            # Since we will use visited to check later
            vertices[edge[0]].append(edge[1])
            vertices[edge[1]].append(edge[0])

        visited = set()
        return self.dfs(vertices, visited, source, destination)


    def dfs(self, vertices: List[List[int]], visited: Set[int], curr_node: int, destination: int) -> bool:
        if curr_node == destination:
                return True

        if curr_node not in visited:
            visited.add(curr_node)
            for next_node in vertices[curr_node]:
                if self.dfs(vertices, visited, next_node, destination):
                    return True
        return False
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(V + E)$ where $V$ and $E$ are the number of vertices and edges.  
    - For building `vertices` matrix of all `m` edges, it takes $O(m)$.
    - Each node is only visited once by using DFS with visited, it takes $O(n)$ to traverse all nodes.
- Space complexity: $O(V + E)$  
    - Use a list of list to store two nodes per edge for all edges, it takes $O(2 \times E) = $O(E)$.
    - Use `set` to track the visited nodes, it may add all $n$ nodes in the worst case.
    - The recursive function uses function call call stack, uses $O(n)$ space in the worst case.

### Approach 3 - Union Find

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach - BFS |  $O(V + E)$           | $O(V + E)$ |
Approach - DFS |  $O(V + E)$           | $O(V + E)$  |

## Test
