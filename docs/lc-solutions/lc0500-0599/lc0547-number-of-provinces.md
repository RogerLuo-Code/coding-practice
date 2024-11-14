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
            visited = set()
            n_provinces = 0
            n_cities = len(isConnected)
            for i_city in range(n_cities):
                if i_city not in visited:
                    self.bfs(isConnected, i_city, visited)
                    n_provinces +=1

            return n_provinces

        def bfs(self, isConnected: List[List[int]], i_city: int, visited: Set[int]) -> None:
            queue = deque([i_city])
            visited.add(i_city)
            n_cities = len(isConnected[0])
            while queue:
                curr_city = queue.popleft()
                for next_city in range(n_cities):
                    if next_city not in visited and isConnected[curr_city][next_city]:
                        queue.append(next_city)
                        visited.add(next_city)
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n^2)$  
  In the worst case, it will visit $n$ cities once. when visiting each city, it will
  check $n$ edges (including no connection edge) for the next city. So the time
  complexity is $O(n^2)$.
- Space complexity: $O(n)$  
  In the worst case, the queue and visited will store all cities, which takes $O(n)$ space.

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

We can solve the problem using union-find:

- `union` two cities if they are not in the same disjoined set (i.e. provinces)
- `find` whether any two cities are in the same disjoin set (i.e., province)

We can initialize the `n_provinces` as total number of cities. Whenever conducting `union` operations, reduce `n_provinces` by 1.

=== "python"
    ```python
    class UnionFind:
        def __init__(self, size: int) -> None:
            self.root = [i for i in range(size)]  # (1)
            self.rank = [0] * size
            self.count = size

        def find(self, x: int) -> int:
            if x == self.root[x]:
                return x
            self.root[x] = self.find(self.root[x])
            return self.root[x]

        def union(self, x: int, y: int) -> None:
            root_x = self.find(x)
            root_y = self.find(y)
            if root_x != root_y:
                if self.rank[root_x] > self.rank[root_y]:
                    self.root[root_y] = root_x
                elif self.rank[root_x] < self.rank[root_y]:
                    self.root[root_x] = root_y
                else:  # equal rank
                    self.root[root_y] = root_x
                    self.rank[root_x] += 1
                self.count -= 1

        def getCount(self) -> int:
            return self.count

    class Solution:
        def findCircleNum(self, isConnected: List[List[int]]) -> int:
            if not isConnected or len(isConnected) == 0:
                return 0

            n_cities = len(isConnected)
            uf = UnionFind(n_cities)

            for i_city in range(n_cities):
                for j_city in range(i_city + 1, n_cities):
                    if isConnected[i_city][j_city] == 1:
                        uf.union(i_city, j_city)

            return uf.getCount()
    ```

    1. It's better set `root`, `rank`, and `count` as private attributes, `__root`, `__rank`, and `__count`.

#### Complexity Analysis of Approach 3

- Time complexity: $O(n^2 \alpha(n))$ where $\alpha(n)$ is the inverse Ackermann function.  
  The time complexity is dominated by two for-loops:
     - two for-loops take $n^2/2$ operations
     - within the for-loop, `union` function takes $\alpha(n)$.
  So the total time complexity is $n^2 \alpha(n)$.
- Space complexity: $O(n)$  
  The `UnionFind` use `root` and `rank` arrays. Each stores $n$ elements
  uses $O(n)$ space.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach 1 - BFS  |  $O(n^2)$           | $O(n)$ |
Approach 2 - DFS |  $O(n^2)$           | $O(n)$  |
Approach 3 - Union Find |  $O(n^2 \alpha(n))$           | $O(n)$  |

## Test
