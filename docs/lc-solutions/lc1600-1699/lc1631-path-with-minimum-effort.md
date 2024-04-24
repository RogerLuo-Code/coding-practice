---
tags:
- Graph
- Binary Search
---

# LC1631. Path With Minimum Effort
## Problem Description
[LeetCode Problem 1631](https://leetcode.com/problems/path-with-minimum-effort): You are a hiker preparing for an upcoming hike. You are given `heights`, a 2D array of size `rows x columns`, where `heights[row][col]` represents the height of cell `(row, col)`. You are situated in the top-left cell, `(0, 0)`, and you hope to travel to the bottom-right cell, `(rows-1, columns-1)` (i.e., **0-indexed**). You can move **up**, **down**, **left**, or **right**, and you wish to find a route that requires the minimum **effort**.

A route's **effort** is the **maximum absolute difference** in heights between two consecutive cells of the route.

Return _the minimum **effort** required to travel from the top-left cell to the bottom-right cell._

## Clarification

## Assumption

## Solution
### Approach - Binary Search + BFS
Use binary search to find a minimum `effort` such that there exists a route with **maximum absolute difference** <= `effort`. For each `effort`, we can search the route by using either Breadth First Search (BFS) or Depth First Search (DFS).

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
                    if 0 <= r and r < n_row and 0 <= c and c < n_col and abs(heights[r][c] - heights[x][y]) <= effort and (r, c) not in seen:
                        seen.add((r, c))
                        dq.append((r, c))
            return False
    ```

#### Complexity Analysis
* Time complexity: $O(m n)$ where $m$ is the number of rows, $n$ is the number of columns
We do binary search to calculate the `effort` and then do BFS on the matrix for each of these values.

    - Binary search: the search space is $[0, 10^6]$. So the time complexity is $O(\log 10^6)$
    - BFS: the time complexity of the BFS for vertices $V$ and edges $E$ is $O(V + E)$. In the matrix with size $(m, n)$, there are $m \times n$ vertices and $m \times n$ edges. So the time complexity would be $O(mn + mn) = O(mn)$.

The total time complexity is $O(\log 10^6 * (mn))$ which is equivalent to $O(mn)$.

* Space complexity: $O(m n)$  
As we use a queue and seen dictionary of potential max size $mn$.


## Test