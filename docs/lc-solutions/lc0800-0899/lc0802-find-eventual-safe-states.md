---
tags:
    - Depth-First Search
---

# LC802. Find Eventual Safe States

## Problem Description

[LeetCode Problem 802](https://leetcode.com/problems/find-eventual-safe-states/): There is a directed graph of `n` nodes with each node labeled from `0` to `n - 1`. The graph is represented by a **0-indexed** 2D integer array `graph` where `graph[i]` is an integer array of nodes adjacent to node `i`, meaning there is an edge from node `i` to each node in `graph[i]`.

A node is a **terminal node** if there are no outgoing edges. A node is a **safe node** if every possible path starting from that node leads to a **terminal node** (or another safe node).

Return _an array containing all the **safe nodes** of the graph_. The answer should be sorted in **ascending** order.

## Clarification

- Definition of safe node
- Directed graph

## Assumption

-

## Solution

### Approach - DFS

Similar to [LC1059](../lc1000-1099/lc1059-all-paths-from-source-lead-to-destination.md), we can use node-coloring variant of DFS to check each node to see whether a cycle is detected (unsafe).

=== "Python"
    ```python
    class Solution:
        def __init__(self):
            self.GREY = 1
            self.BLACK = 2

        def eventualSafeNodes(self, graph: List[List[int]]) -> List[int]:
            results = []
            n_nodes = len(graph)
            color = [None] * n_nodes

            for node in range(len(graph)):
                if self.dfs(node, graph, color):
                    results.append(node)

            return results

        def dfs(self, node: int, graph: List[List[int]], color: List[int]) -> bool:
            # Return false if a cycle is detected where color is grey
            if color[node] != None:
                return color[node] == self.BLACK

            # No outgoing links, reach the end
            if len(graph[node]) == 0:
                return True

            # Mark as grey in process
            color[node] = self.GREY

            for next_node in graph[node]:
                # Short circuit and return false if detected a "False" from any recursive call
                if not self.dfs(next_node, graph, color):
                    return False

            # Recursing process is done
            color[node] = self.BLACK
            return True
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(V + E)$  
  The total time complexity consists of:

    - Iniializing `color` array takes $O(V)$ time
    - The `dfs` function traverse each nodes once, which takes `O(V)` time. Ofr each node, it iterates over all the outgoing edges, which takes $O(E)$ time to iterate over all the edges.

- Space complexity: $O(V)$  
  
    - the `color` array takes $O(V)$ space
    - The recursion call stack used by `dfs` takes $O(V)$ space in the worst case.

### Approach 2 - Topological Sort

Solution

=== "python"
    ```python
    code
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(1)$  
  Explanation
- Space complexity: $O(n)$  
  Explanation

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach - DFS |  $O(V + E))$           | $O(n)$ |
Approach -  |  $O(1)$           | $O(n)$  |

## Test
