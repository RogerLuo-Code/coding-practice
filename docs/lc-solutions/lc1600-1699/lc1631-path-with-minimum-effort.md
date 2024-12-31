---
tags:
    - Shortest Path
    - Breadth-First Search
    - Binary Search
---

# LC1631. Path With Minimum Effort

## Problem Description

[LeetCode Problem 1631](https://leetcode.com/problems/path-with-minimum-effort): You are
a hiker preparing for an upcoming hike. You are given `heights`, a 2D array of size
`rows x columns`, where `heights[row][col]` represents the height of cell `(row, col)`.
You are situated in the top-left cell, `(0, 0)`, and you hope to travel to the
bottom-right cell, `(rows-1, columns-1)` (i.e., **0-indexed**). You can move **up**,
**down**, **left**, or **right**, and you wish to find a route that requires the minimum
**effort**.

A route's **effort** is the **maximum absolute difference** in heights between two
consecutive cells of the route.

Return _the minimum **effort** required to travel from the top-left cell to the
bottom-right cell._

## Clarification

## Assumption

## Solution

### Approach - Shortest Path Faster Algorithm

Use a queue to track the path with effort. Use breadth-first search to search cells,
which allow visiting cells multiple times. We will update the minimum effort between
`(0, 0)` and any node `(i, j)` during the search. We will add the cell to the queue if
it has less effort.

=== "Python"
    ```python
    from collections import deque, defaultdict

    class Solution:
        def minimumEffortPath(self, heights: List[List[int]]) -> int:
            n_rows = len(heights)
            n_cols = len(heights[0])

            DIRECTIONS = ((-1, 0), (1, 0), (0, -1), (0, 1))  # (1)
            min_effort = defaultdict(lambda: float("inf"))  # (2)
            queue = deque([(0, 0, 0)])  # (row, col, effort)
            min_effort[(0, 0)] = 0

            while queue:
                curr_row, curr_col, effort = queue.popleft()
                for delta_row, delta_col in DIRECTIONS:
                    next_row, next_col = curr_row + delta_row, curr_col + delta_col
                    if 0 <= next_row < n_rows and 0 <= next_col < n_cols:
                        abs_diff = abs(heights[next_row][next_col] - heights[curr_row][curr_col])
                        new_effort = max(abs_diff, effort)
                        if new_effort < min_effort[(next_row, next_col)]:
                            queue.append((next_row, next_col, new_effort))
                            min_effort[(next_row, next_col)] = new_effort

            return min_effort[(n_rows - 1, n_cols - 1)]
    ```

    1. up, down, left, right.
    2. dictionary[cell] = minimum effort on the path from (0, 0) and the current cell.

#### Complexity Analysis of Approach 1

- Time complexity: $O(m n)$  
    - For queue operation, each node will be added to the queue at most $4$ times
    (4 move directions in the 2D array). There will be at most $4 m n$ queue operations.
    Each queue operation (enqueue or dequeue) takes $O(1)$. So the queue operation takes
    $O(m n)$.
    - For neighboring exploration, each node will explore $4$ neighbors. For at most
    $4 m n$ nodes, the total neighboring explorations is $16 m n$. So neighboring
    exploration takes $O(m n)$.  
    So the total time complexity is $O(m n) + O(m n) = O(m n)$.
- Space complexity: $O(m n)$  
    - The `min_effort` dictionary takes $O(m n)$ space for total $m n$ cells.
    - The `queue` takes $O(m n)$ space since $m n$ cells can be added at most 4 times.  
    So the total space complexity is $O(m n) + O(m n) = O(m n)$.

### Approach 2 - Dijkstra

This problem can also use Dijkstra's algorithm to find the minimum effort (i.e.,
shortest path).

=== "Python"
    ```python
    import heapq
    import math
    from collections import defaultdict

    class Solution:
        def minimumEffortPath(self, heights: List[List[int]]) -> int:
            n_rows = len(heights)
            n_cols = len(heights[0])

            DIRECTIONS = ((-1, 0), (1, 0), (0, -1), (0, 1))  # (1)
            min_effort = defaultdict(lambda: math.inf)  # (2)
            pq = [(0, 0, 0)]  # (3)

            while pq:
                effort, curr_row, curr_col = heapq.heappop(pq)  # (4)
                if (curr_row, curr_col) not in min_effort:
                    min_effort[(curr_row, curr_col)] = effort

                    for delta_row, delta_col in DIRECTIONS:
                        next_row, next_col = curr_row + delta_row, curr_col + delta_col
                        if 0 <= next_row < n_rows and 0 <= next_col < n_cols:
                            abs_diff = abs(heights[next_row][next_col] - heights[curr_row][curr_col])
                            new_effort = max(abs_diff, effort)
                            heapq.heappush(pq, (new_effort, next_row, next_col))

            return min_effort[(n_rows - 1, n_cols - 1)]
    ```

    1. up, down, left, right.
    2. dictionary[(row, col)] = minimum effort on the path from (0, 0) and the current cell.
    3. (effort, row, col)
    4. The priority queue returns the minimum item based on the first element of the
    tuple (effort).

#### Complexity Analysis of Approach 2

- Time complexity: $O(m n \log (m n))$ where $m$ is number of rows and $n$ is number of
columns.  
    - Each node (cell) can be added to the priority queue at most 1 time with at most
    $m n$ queue operations.
    - Each queue operation (push or pop from a heap) takes $O(\log s)$, which $s$ is the
    size of the heap. The size of the heap is bounded by the number of nodes, i.e.,
    $s \leq m n$. So the queue operation time complexity is $O(\log (m n))$.  
    So the total time complexity is $O(m n \log (m n))$.

- Space complexity: $O(m n)$  
    The heap size may contains at most $m n$ nodes and `min_effort` dictionary takes
    $O(m n)$ space. So the total is $O(m n) + O(m n) = O(m n)$.

### Approach 3 - Binary Search + BFS

Use binary search to find a minimum `effort` between $0$ and $10^6$ (given constraint)
such that there exists a route with **maximum absolute difference** <= `effort`. For
each `effort`, we can search the route by using either Breadth First Search (BFS) or
Depth First Search (DFS).

=== "Python"
    ```python
    class Solution:
        def minimumEffortPath(self, heights: List[List[int]]) -> int:
            low, high = 0, 10**6
            while low < high:
                effort = (low + high) // 2
                if self.isPath(heights, effort):
                    high = effort
                else:
                    low = effort + 1
            return low

        def isPath(self, heights: List[List[int]], effort: int) -> bool:
            n_row, n_col = len(heights), len(heights[0])
            seen, dq = {(0, 0)}, deque([(0, 0)])
            while dq:
                x, y = dq.popleft()
                if (x, y) == (n_row - 1, n_col - 1):
                    return True

                for r, c in (x, y + 1), (x, y - 1), (x + 1, y), (x - 1, y):
                    if 0 <= r and r < n_row and 0 <= c and c < n_col
                            and abs(heights[r][c] - heights[x][y]) <= effort
                            and (r, c) not in seen:
                        seen.add((r, c))
                        dq.append((r, c))
            return False
    ```

#### Complexity Analysis of Approach 3

- Time complexity: $O(m n)$ where $m$ is the number of rows, $n$ is the number of columns
We do binary search to calculate the `effort` and then do BFS on the matrix for each of
these values.
    - Binary search: the search space is $[0, 10^6]$. So the time complexity is $O(\log 10^6)$
    - BFS: the time complexity of the BFS for vertices $V$ and edges $E$ is $O(V + E)$.
    In the matrix with size $(m, n)$, there are $m \times n$ vertices and $m \times n$
    edges. So the time complexity would be $O(mn + mn) = O(mn)$.  
    The total time complexity is $O(\log 10^6 * (mn))$ which is equivalent to $O(mn)$.

- Space complexity: $O(m n)$  
As we use a queue and seen dictionary of potential max size $mn$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach - SPFA |  $O(m n)$           | $O(m n)$ |
Approach - Dijkstra |  $O(m n \log(m n))$           | $O(m n)$  |
Approach - Binary Search | $O(m n)$ | $O(m n)$ |

## Test
