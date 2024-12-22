---
tags:
    - Union Find
---

# LC323. Number of Connected Components in an Undirected Graph

## Problem Description

[LeetCode Problem 323](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/):
You have a graph of `n` nodes. You are given an integer `n` and an array `edges` where
`edges[i] = [ai, bi]` indicates that there is an edge between `ai` and `bi` in the graph.

Return _the number of connected components in the graph_.

## Clarification

- Undirected graph

## Assumption

- node values range from 0 to n - 1

## Solution

### Approach 1 - Union Find

We can use union find to count the number of connected components in the graph.

=== "Python"
    ```python
    class UnionFind:
        def __init__(self, n):
            self.root = [i for i in range(n)]
            self.rank = [0] * n
            self.count = n

        def find(self, x):
            if x == self.root[x]:
                return x
            self.root[x] = self.find(self.root[x])
            return self.root[x]

        def union(self, x, y):
            root_x = self.find(x)
            root_y = self.find(y)

            if root_x != root_y:
                if self.rank[root_x] > self.rank[root_y]:
                    self.root[root_y] = root_x
                elif self.rank[root_x] < self.rank[root_y]:
                    self.root[root_x] = root_y
                else:
                    self.root[root_y] = root_x
                    self.rank[root_x] += 1
                self.count -= 1

    class Solution:
        def countComponents(self, n: int, edges: List[List[int]]) -> int:
            uf = UnionFind(n)

            for edge in edges:
                uf.union(edge[0], edge[1])

            return uf.count
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(V + E \alpha(V))$  where $V$ is number of vertices and $E$ is number of edges  
    - Initialize `root` and `rank` arrays take $O(V)$ time
    - The for-loop requires $O(E)$ operations to iterating all edges. Each iteration calls `union` function and takes $O(\alpha(V))$.  
    So the total time complexity is $O(V + E \alpha(V))$.
- Space complexity: $O(V)$  
  The union find takes $O(V)$ space to stores `root` and `rank`.

### Approach 2 - DFS/BFS

The problem can also be solved using either BFS or DFS. Start from a vertex and traverse the sub-graph (connected components) using either BFS or DFS and mark nodes visited. For the next node not visited, traverse and mark visited again. In the meantime, increase count by 1 since it doesn't belong to previous connected components.

=== "Python - DFS"
    ```python
    class Solution:
        def countComponents(self, n: int, edges: List[List[int]]) -> int:
            count = 0

            # Convert edge list to adjacent list for easy traversing later
            adj_list = [[] for _ in range(n)]
            for edge in edges:
                adj_list[edge[0]].append(edge[1])
                adj_list[edge[1]].append(edge[0])

            visited = set()
            for node in range(n):
                if node not in visited:
                    count += 1
                    self.dfs(node, adj_list, visited)

            return count

        def dfs(self, node: int, adj_list: List[List[int]], visited: Set[int]) -> None:
            visited.add(node)

            for neighbor in adj_list[node]:
                if neighbor not in visited:
                    self.dfs(neighbor, adj_list, visited)
    ```

=== "Python - BFS"
    ```python
    class Solution:
        def countComponents(self, n: int, edges: List[List[int]]) -> int:
            count = 0

            # Convert edge list to adjacent list for easy traversing later
            adj_list = [[] for _ in range(n)]
            for edge in edges:
                adj_list[edge[0]].append(edge[1])
                adj_list[edge[1]].append(edge[0])

            visited = set()
            for node in range(n):
                if node not in visited:
                    count += 1
                    self.bfs(node, adj_list, visited)

            return count

        def bfs(self, node: int, adj_list: List[List[int]], visited: Set[int]) -> None:
            visited.add(node)
            queue = deque([node])

            while queue:
                curr_node = queue.popleft()
                for neighbor in adj_list[curr_node]:
                    if neighbor not in visited:
                        queue.append(neighbor)
                        visited.add(neighbor)
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(V + E)$  
    - Initialize `adj_list` takes $O(V)$ time
    - Convert edge list to `adj_list` takes $O(E)$ time
    - During DFS/BFS traversal, each vertex will only be visited once, taking $O(V)$ time. For each vertex, we iterate its edge list once. In total, takes $O(E)$ time to go through all edges. So the time complexity for traversing is $O(V + E)$.  
    So the total time complexity is $O(V) + O(E) + O(V + E) = O(V + E)$.
- Space complexity: $O(V + E)$  
    - `adj_list` takes $O(V + E)$ space since store all nodes and their edges.
    - `visited` takes $O(V)$ space to track nodes
    - The call stack of DFS or queue of BFS takes $O(V)$ space in the worst case.  
    So the total space complexity is $O(V + E) + O(V) + O(V) = O(V + E)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach 1 - Union Find  |  $O(V + E \alpha(V))$           | $O(V)$ |
Approach 2 - BFS/DFS  |  $O(V + E)$           | $O(V + E)$  |

## Test
