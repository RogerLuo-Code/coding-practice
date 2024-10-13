---
tags:
    - Depth-First Search
---

# LC797. All Paths From Source to Target

## Problem Description

[LeetCode Problem 797](https://leetcode.com/problems/all-paths-from-source-to-target/): Given a directed acyclic graph (**DAG**) of `n` nodes labeled from `0` to `n - 1`, find all possible paths from node `0` to node `n - 1` and return them in **any order**.

The graph is given as follows: `graph[i]` is a list of all nodes you can visit from node `i` (i.e., there is a directed edge from node `i` to node `graph[i][j]`).

## Clarification

- Definition of directed acyclic graph (DAG)
- Find all paths from 0 to n - 1

## Assumption

-

## Solution

### Approach - DFS

Use DFS to traverse all nodes and save the path while traversing, If find target target, append the path results. Otherwise, backtracking the path by removing nodes.

Since it is a DAG, no need a visited set since it won't get stuck in a loop (no cycles//loops). Actually the visited set will prevent from finding all paths. Some nodes may need to be visited multiple times when it has multiple indegree.

=== "Python"
    ```python
    class Solution:
        def allPathsSourceTarget(self, graph: List[List[int]]) -> List[List[int]]:
            results = []
            path = [0]
            self.dfs(graph, 0, path, results)
            return results

        def dfs(self, graph: List[List[int]], curr_node: int, path: List[int], results: List[List[int]]) -> None:
            if curr_node == len(graph) - 1:
                results.append(list(path))
            else:
                for next_node in graph[curr_node]:
                    path.append(next_node)
                    self.dfs(graph, next_node, path, results)
                    path.pop()  # (1)
    ```

    1. Backtracking by popping the last node after each recursive call to ensure the current path is restored to its previous state before exploring new branches.

#### Complexity Analysis of Approach 1

- Time complexity: $O(2^n)$  
  In the worst case (complete binary tree), the number of paths explored by the DFS algorithm can be as large as $O(2^n)$.
- Space complexity: $O(n)$  
    - For recursion, the number of recursive call can go up to $n$ calls in the worst case
    - For the current path, it could store $n$ nodes in the worst case.

### Approach2 -

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
Approach -  |  $O(1)$           | $O(n)$ |
Approach -  |  $O(1)$           | $O(n)$  |

## Test
