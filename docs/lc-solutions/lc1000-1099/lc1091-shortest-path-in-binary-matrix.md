---
tags:
    - Breadth-First Search
---

# LC1091. Shortest Path in Binary Matrix

## Problem Description

[LeetCode Problem 1091](https://leetcode.com/problems/shortest-path-in-binary-matrix/): Given an `n x n` binary matrix `grid`, return _the length of the shortest **clear path** in the matrix_. If there is no clear path, return `-1`.

A **clear path** in a binary matrix is a path from the **top-left** cell (i.e., `(0, 0)`) to the **bottom-right** cell (i.e., `(n - 1, n - 1)`) such that:

- All the visited cells of the path are `0`.
- All the adjacent cells of the path are **8-directionally**connected (i.e., they are different and they share an edge or a corner).

The **length of a clear path** is the number of visited cells of this path.

## Clarification

- What is clear path?
- What does 8-directionally connected mean? All 8 elements surround the element are neighbors

## Assumption

-

## Solution

### Approach - BFS

Use Breadth-First Search (BFS) to traverse the nodes.

- Each node may have at most 8 neighbors. Add all its valid neighbors that are 0 and not visited.
- When finding the target, return the current path length that which is also the shorted path.


=== "Python"
    ```python
    class Solution:
        def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
            n_row = len(grid)
            n_col = len(grid[0])
            if grid[0][0] != 0 or grid[n_row - 1][n_col - 1] != 0:
                return -1

            DIRECTIONS = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]

            queue = deque([(0, 0)])
            visited = set([(0, 0)])
            path_len = 1

            while queue:
                size = len(queue)
                for _ in range(size):  # (1)
                    curr_row, curr_col = queue.popleft()
                    if curr_row == n_row - 1 and curr_col == n_col - 1:
                        return path_len
                    for delta_row, delta_col in DIRECTIONS:
                        next_row, next_col = curr_row + delta_row, curr_col + delta_col
                        if 0 <= next_row < n_row and 0 <= next_col < n_col and grid[next_row][next_col] == 0 and (next_row, next_col) not in visited:
                            queue.append((next_row, next_col))
                            visited.add((next_row, next_col))

                path_len += 1

            return -1  # (2)
    ```

    1. Explore nodes with the same path length so far.
    2. No path found.

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  Processing a cell takes $O(1)$ and total $n$ cells are processed at most once. So the time complexity is $O(n)$.
- Space complexity: $O(\sqrt{n})$  
  In the worst case, the queue will hold the max number of nodes with the same path length, which could be the last row and last column with total $2 \times \sqrt{n}$ cells.

## Test
