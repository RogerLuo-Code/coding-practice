---
tags:
    - Breadth-First Search
    - Depth-First Search
---

# LC133. Clone Graph

## Problem Description

[LeetCode Problem 133](https://leetcode.com/problems/clone-graph/): Given a reference of a node in a **[connected](https://en.wikipedia.org/wiki/Connectivity_(graph_theory)#Connected_graph)** undirected graph.

Return a [**deep copy**](https://en.wikipedia.org/wiki/Object_copying#Deep_copy) (clone) of the graph.

Each node in the graph contains a value (`int`) and a list (`List[Node]`) of its neighbors.

```Java
class Node {
    public int val;
    public List<Node> neighbors;
}
```

## Clarification

- What does deep copy mean?
- The example of list just show neighbors of each node
- The actual function input is a node not a list

## Assumption

-

## Solution

### Approach - DFS

Copy the node while traversing the graph (either using depth-first search or breadth-first search). To prevent getting stuck in a cycle, we need to track the visited codes that have already been copied.

=== "Python"
    ```python
    from typing import Optional
    class Solution:
        def __init__(self):
            # Dictionary: key is the visited node and value is the clone node
            # This helps to avoid cycle.
            self.visited = {}

        def cloneGraph(self, node: Optiona['Node']) -> Optional['Node']:
            if not node:
                return None

            return self.dfs(node)

        def dfs(self, node: Optional['Node']) -> Optional['Node']:
            if node in self.visited:
                return self.visited[node]

            clone_node = Node(node.val)

            if node.neighbors:
                clone_node.neighbors = [] # chnage from None to [] to store neighbors
                self.visited[node] = clone_node
                clone_node.neighbors = [self.dfs(n) for n in node.neighbors]

            return clone_node
    ```

#### Complexity Analysis of DFS Approach

- Time complexity: $O(n + m)$ where $n$ is number of nodes (vertices) and $m$ is a number of edges  
  When doing DFS, it will traverse all node and edges.  
- Space complexity: $O(n)$  
  The space usage consists of two parts: 1) `visited` hash map to store all node and clone nodes, which is $O(n)$ and 2) recursion call stack $O(h)$. So the space complexity is $O(n) + O(h) = O(n)$

### Approach2 - BFS

Similar to DFS method, we can use breadth-first search method to traverse the graph and make copies. Again, we need a way to track visited nodes.

=== "python"
    ```python
    from collections import deque
    class Solution:
        def cloneGraph(self, node: Optional['Node']) -> Optional['Node']:
            if not node:
                return None

            # Dictionary to store the visited node
            # key: node; value: clone node
            visited = {}

            queue = deque()
            queue.append(node)
            visited[node] = Node(node.val)

            while queue:
                current_node = queue.popleft()

                for neighbor_node in current_node.neighbors:
                    if not visited[current_node].neighbors:
                        visited[current_node].neighbors = []

                    if neighbor_node not in visited:
                        queue.append(neighbor_node)
                        visited[neighbor_node] = Node(neighbor_node.val)

                    visited[current_node].neighbors.append(visited[neighbor_node])

            return visited[node]
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n + m)$  where $n$ is a number of nodes (vertices) and $m$ is a number of edges  
  It traverse all nodes and edges once to make clone. With visited, preventing from visiting nodes more than once.
- Space complexity: $O(n)$  
  The overall space is the combination of space occupied by `visited` dictionary, $O(n)$, storing all nodes and space of queue, $O(w)$, store nodes at one layer, i.e., width of the graph.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach - DFS |  $O(n + m)$    | $O(n)$ |
Approach - BFS |  $O(n + m)$    | $O(n)$  |

## Test
