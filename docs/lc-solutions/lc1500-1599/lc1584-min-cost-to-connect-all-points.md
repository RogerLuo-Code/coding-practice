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

**Tip**: We can use input array indices to represent the nodes.

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

- Time complexity: $O(n^2 \log n)$ where $n$ represents the number of points.  
    - Go through all edges, $n (n - 1) / 2 \approx n^2 / 2$,among points to compute cost.
    - Sorting all edges takes $O(n^2 \log (n^2)) = O(n^2 2 \log(n)) = O(n^2 \log(n))$ from `timsort` in Python. 
    - To find minimum spanning tree, adding points and check points connectivity using union-find takes $O(\alpha(n))$ and in the worst case may need to go through all $n^2$ edges. So it takes $O(n^2 \alpha(n))$.  
    In total, it takes $O(n^2) + O(n^2 \log n) + O(n^2 \alpha(n)) = O(n^2 \log (n))$.
- Space complexity: $O(n^2)$  
    - Store cost for each edge takes $O(n^2)$ space.
    - Sorting edges takes $O(n^2)$ space from `timsort` in Python.
    - Union find structure takes $O(n)$ space to store points (2 points per edge)
    In total, it takes $O(n^2 + n^2 + n) = O(n^2)$ space.

### Approach 2 - Prim's Algorithm (Min Heap)

We can also use Prim's algorithm to solve the minimum spanning tree problem. We use min-heap data structure to track the lowest-weighted edge, `(weight, next_point)`.

Note that we don't need to include the `curr_point` like this `(weight, curr_point, next_point)`. We just need to find the lowest weight edge and associated next point. The current point is already evaluated, either in the minimum spanning tree or may form a cycle.

=== "python - min heap"
    ```python
    import heapq


    class Solution:
        def minCostConnectPoints(self, points: List[List[int]]) -> int:
            n_points = len(points)
            points_in_mst = set()  # track points which are in minimum spanning tree (MST)
            min_heap = [(0, 0)]  # Min-heap to store minimum weight edge at top

            total_cost = 0
            n_edges_used = 0

            while n_edges_used < n_points:
                cost, curr_point = heapq.heappop(min_heap)

                # Discard the point if already in MST (prevent cycle)
                if curr_point in points_in_mst:
                    continue

                points_in_mst.add(curr_point)
                total_cost += cost
                n_edges_used += 1

                for next_point in range(n_points):
                    # Add (edge weight, next_point) from the curr_point
                    if next_point not in points_in_mst:
                        next_cost = abs(
                            points[curr_point][0] - points[next_point][0]
                        ) + abs(points[curr_point][1] - points[next_point][1])
                        heapq.heappush(min_heap, (next_cost, next_point))

            return total_cost
    ```

#### Complexity Analysis of Approach 2

Min heap method:

- Time complexity: $O(n^2 \log (n))$  
  In the worst case, we push/pop $n (n - 1) / 2 \approx n^2 / 2$ edges. Each push/pop operation takes $O(\log (n^2 / 2) = 2 \log(n)$So the overall time complexity is $O(n^2 \log (n))$
- Space complexity: $O(n^2)$  
    - In the worst case, the min heap stores all $n^2 / 2$ edges.
    - The `set` to track points in the minimum spanning tree stores $n$ points.
    So the overall space complexity is $O(n^2) + O(n) = O(n^2)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach 1 - Kruskal  |  $O(n^2 \log (n))$           | $O(n^2)$ |
Approach 2A - Prim - Min Heap  |  $O(n^2 \log (n))$           | $O(n^2)$  |

## Test
