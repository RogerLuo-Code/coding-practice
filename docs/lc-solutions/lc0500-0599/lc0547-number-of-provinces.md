---
tags:
    - Breadth-First Search
    - Depth-First Search
---

# LC547. Number of Provinces

## Problem Description

[LeetCode Problem 547](https://leetcode.com/problems/number-of-provinces): There are `n`
cities. Some of them are connected, while some are not. If city `a` is connected
directly with city `b`, and city `b` is connected directly with city `c`, then city `a`
is connected indirectly with city `c`.

A **province** is a group of directly or indirectly connected cities and no other cities
outside of the group.

You are given an `n x n` matrix `isConnected` where `isConnected[i][j] = 1` if the `ith`
city and the `jth` city are directly connected, and `isConnected[i][j] = 0` otherwise.

Return _the total number of **provinces**_.

## Clarification

- What does "no other cities outside of the group" mean?

## Assumption

-

## Solution

Go through each city, and use either DFS or BFS to find all connected cities and also
mark visited city in the meantime. Once done, increase number of provinces by 1. If the
city is visited, skip.

### Approach - BFS

Use breadth-first search to traverse the graph.

=== "Python"
    ```python
    from collections import deque

    class Solution:
        def findCircleNum(self, isConnected: List[List[int]]) -> int:
            queue = deque()
            visited = set()
            n_provinces = 0
            n_row = len(isConnected)
            n_col = len(isConnected[0])

            # Traverse city by city
            for i_row in range(n_row):
                if i_row in visited:
                    continue

                queue.append(i_row)
                visited.add(i_row)

                while queue:
                    current_city = queue.popleft()
                    for next_city in range(n_col):
                        if next_city != current_city and next_city not in visited \
                                and isConnected[current_city][next_city] == 1:
                            queue.append(next_city)
                            visited.add(next_city)

                n_provinces += 1

            return n_provinces
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n^2)$  
  IIn the worst case, it will visit $n$ cities once. when visiting each city, it will
  check $n$ edges (including no connection edge) for the next city. So the time
  complexity is $O(n^2)$.
- Space complexity: $O(n)$  
  In the worst case, the queue will store all cities, which takes $O(n)$ space.

### Approach 2 - DFS

Use depth-first search to traverse the cities.

=== "python"
    ```python
    class Solution:
        def findCircleNum(self, isConnected: List[List[int]]) -> int:
            n_provinces = 0
            visited = set()
            for i_city in range(len(isConnected)):
                if i_city not in visited:
                    self.dfs(i_city, isConnected, visited)
                    n_provinces += 1

            return n_provinces

        def dfs(self, curr_city: int, isConnected: List[List[int]], visited: set[int]) -> None:
            visited.add(curr_city)
            for next_city in range(len(isConnected[curr_city])):
                if next_city not in visited and isConnected[curr_city][next_city] == 1:
                    self.dfs(next_city, isConnected, visited)
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n^2)$  
  In the worst case, it will visit $n$ cities once. when visiting each city, it will
  check $n$ edges (including no connection edge) for the next city. So the time
  complexity is $O(n^2)$.
- Space complexity: $O(n)$  
  In the worst case, recursive function is called $n$ times and recursion call stack
  uses $O(n)$ space.

### Approach 3 - Union Find

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach 1 - BFS  |  $O(n^2)$           | $O(n)$ |
Approach 2 - DFS |  $O(n^2)$           | $O(n)$  |
Approach 3 - Union Find |  $O(?)$           | $O(?)$  |

## Test
