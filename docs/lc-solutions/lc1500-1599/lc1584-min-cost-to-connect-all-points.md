---
tags:
    - Minimum Spanning Tree
    - Union Find
---

# LC1584. Min Cost to Connect All Points

## Problem Description

[LeetCode Problem 1584](https://leetcode.com/problems/min-cost-to-connect-all-points/description/): You are given an array `points` representing integer coordinates of some points on a 2D-plane, where `points[i] = [xi, yi]`.

The cost of connecting two points `[xi, yi]` and `[xj, yj]` is the **manhattan distance** between them: `|xi - xj| + |yi - yj|`, where `|val|` denotes the absolute value of `val`.

Return _the minimum cost to make all points connected._ All points are connected if there is **exactly one** simple path between any two points.

## Clarification

- array of points, each point is [xi, yi]
- the cost of the edge is the manhattan distance between two points
- minimum cost to connect all points

## Assumption

-

## Solution

The problem can be transformed into minimum spanning tree (MST) problem. Then we can use classical Kruskal's or Prim's algorithm to find the MST.

### Approach - Kruskal's Algorithm

Follow the Krusal's algorithm to find the minimum spanning tree by sorting edges by the cost. Regarding sorting, we can either use normal sorting or priority queue.

=== "Python - sort tuple"
    ```python
    from operator import itemgetter


    class UnionFind:
        def __init__(self, n: int) -> None:
            self.root = [i for i in range(n)]
            self.rank = [0] * n

        def find(self, x: int) -> int:
            if x != self.root[x]:
                self.root[x] = self.find(self.root[x])
            return self.root[x]

        def union(self, x: int, y: int) -> bool:
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

                return True
            else:
                return False


    class Solution:
        def minCostConnectPoints(self, points: List[List[int]]) -> int:
            n_points = len(points)

            edges = []
            for i in range(n_points):  # O(n^2)
                for j in range(i + 1, n_points):
                    xi, yi = points[i]
                    xj, yj = points[j]
                    dist = abs(xi - xj) + abs(yi - yj)
                    edges.append((i, j, dist))

            edges.sort(key=itemgetter(2))

            total_cost = 0
            n_edges = 0
            uf = UnionFind(n_points)
            for i_point, j_point, cost in edges:  # O(n \alpha(n))
                if uf.union(i_point, j_point):  # O(\alpha(n))
                    total_cost += cost
                    n_edges += 1
                    if n_edges == n_points - 1:
                        break

            return total_cost
    ```

=== "Python - sort class"
    ```python
    from operator import attrgetter


    class UnionFind:
        def __init__(self, n: int) -> None:
            self.root = [i for i in range(n)]
            self.rank = [0] * n

        def find(self, x: int) -> int:
            if x != self.root[x]:
                self.root[x] = self.find(self.root[x])
            return self.root[x]

        def union(self, x: int, y: int) -> bool:
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

        def connected(self, x: int, y: int) -> bool:
            return self.find(x) == self.find(y)

    class Edge:
        def __init__(self, point1: int, point2: int, cost: int) -> None:
            self.point1 = point1
            self.point2 = point2
            self.cost = cost

        def __lt__(self, other) -> bool:
            return self.cost < other.cost


    class Solution:
        def minCostConnectPoints(self, points: List[List[int]]) -> int:
            n_points = len(points)

            edges = []
            for i in range(n_points):  # O(n^2)
                xi, yi = points[i]
                for j in range(i + 1, n_points):
                    xj, yj = points[j]
                    dist = abs(xi - xj) + abs(yi - yj)
                    edge = Edge(i, j, dist)
                    edges.append(edge)

            # Sort edges
            edges.sort(key=attrgetter('cost'))  # (1)

            total_cost = 0
            n_edges = 0
            uf = UnionFind(n_points)
            for edge in edges:  # O(n \alpha(n))
                if not uf.connected(edge.point1, edge.point2):
                    uf.union(edge.point1, edge.point2)  # O(\alpha(n))
                    total_cost += edge.cost
                    n_edges += 1

                if n_edges == n_points - 1:
                    break

            return total_cost
    ```

    1. Add key to speed up sorting, which is still slower than sorting list of tuples

=== "Python - heapq class"
    ```python
    import heapq


    class UnionFind:
        def __init__(self, n: int) -> None:
            self.root = [i for i in range(n)]
            self.rank = [0] * n

        def find(self, x: int) -> int:
            if x != self.root[x]:
                self.root[x] = self.find(self.root[x])
            return self.root[x]

        def union(self, x: int, y: int) -> bool:
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

        def connected(self, x: int, y: int) -> bool:
            return self.find(x) == self.find(y)


    class Edge:
        def __init__(self, point1: int, point2: int, cost: int) -> None:
            self.point1 = point1
            self.point2 = point2
            self.cost = cost

        def __lt__(self, other):
            return self.cost < other.cost


    class Solution:
        def minCostConnectPoints(self, points: List[List[int]]) -> int:
            n_points = len(points)
            pq = []

            for i in range(n_points):  # (1)
                xi, yi = points[i]
                for j in range(i + 1, n_points):
                    xj, yj = points[j]
                    dist = abs(xi - xj) + abs(yi - yj)
                    edge = Edge(i, j, dist)
                    # heapq.heappush(pq, edge)  # push and sort in the same time O(\log E)
                    pq.append(edge)

            # Convert pq into a heap. O(E).
            heapq.heapify(pq)

            total_cost = 0
            n_edges = 0
            uf = UnionFind(n_points)
            while pq:
                edge = heapq.heappop(pq)
                if not uf.connected(edge.point1, edge.point2):
                    uf.union(edge.point1, edge.point2)
                    total_cost += edge.cost
                    n_edges += 1
                    if n_edges == n_points - 1:
                        break

            return total_cost
    ```

    1. $O(E)$ without `heappush`, $O(E \log E)$ with `heappush`.

#### Complexity Analysis of Approach 1

- Time complexity: $O(E \log E)$ where $E$ represents the number of edges.  
    - Go through all edges and compute cost takes $O(E)$ time complexity.
    - Sorting all edges takes $O(E \log E)$ from `timsort` in Python. 
    - To find minimum spanning tree, adding points and check points connectivity using union-find takes $O(\alpha(E))$ and in the worst case may need to go through all edges. So it takes $O(E \alpha(E))$.  
    In total, it takes $O(E) + O(E \log E) + O(E \alpha(E)) = O(E \log E)$.
- Space complexity: $O(E)$  
    - Store cost for each edge takes $O(E)$ space.
    - Sorting edges takes $O(E)$ space from `timsort` in Python.
    - Union find structure takes $O(E)$ space to store points (2 points per edge)
    In total, it takes $O(E)$ space.

### Approach 2 -

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

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach -  |  $O(1)$           | $O(n)$ |
Approach -  |  $O(1)$           | $O(n)$  |

## Test
