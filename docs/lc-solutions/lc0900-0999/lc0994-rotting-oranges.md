---
tags:
    - Breadth-First Search
---

# LC994. Rotting Oranges

## Problem Description

[LeetCode Problem 994](https://leetcode.com/problems/rotting-oranges/): You are given an
 `m x n` `grid` where each cell can have one of three values:

- `0` representing an empty cell,
- `1` representing a fresh orange, or
- `2` representing a rotten orange.

Every minute, any fresh orange that is **4-directionally adjacent** to a rotten orange
becomes rotten.

Return _the minimum number of minutes that must elapse until no cell has a fresh orange_.
If _this is impossible, return_ `-1`.

## Clarification

- 4-directionally adjacent (top, bottom, left, right)
- return -1, if there is still some fresh orange left
- Is is okay to change input `grid`?


## Assumption

-

## Solution

### Approach - BFS

Add ALL rotten oranges to the queue and use Breadth-First Search (BFS) to add neighbor
oranges layer by layer. The number of layers added is number of minutes elapsed.

During BFS,

- reduce fresh orange number when encounter a fresh one.
- Use `visited` to mark oranges processed instead of changing input `grid`.

If number of fresh oranges is reduced to 0, return number of layers. Otherwise return -1.

=== "Python"
    ```python
    from collections import deque

    class Solution:
        def orangesRotting(self, grid: List[List[int]]) -> int:
            DIRECTIONS = [(0, 1), (0, -1), (-1, 0), (1, 0)]  # Up, down, left, right
            n_rows = len(grid)
            n_cols = len(grid[0])
            n_fresh_oranges = 0  # number of fresh oranges
            n_minutes = 0

            queue = deque()
            visited = set()

            # Add rotten oranges to the queue
            for i_row in range(n_rows):
                for j_col in range(n_cols):
                    if grid[i_row][j_col] == 2:
                        queue.append((i_row, j_col))
                        visited.add((i_row, j_col))

                    if grid[i_row][j_col] == 1:
                        n_fresh_oranges += 1

            # Start from rotten oranges and traverse level by level with 4-directionally
            # adjacent while queue and n_fresh_oranges > 0:

                for _ in range(len(queue)):
                    curr_row, curr_col = queue.popleft()
                    for row_delta, col_delta in DIRECTIONS:
                        next_row, next_col = curr_row + row_delta, curr_col + col_delta
                        if 0 <= next_row < n_rows and 0 <= next_col < n_cols \
                                and (next_row, next_col) not in visited \
                                and grid[next_row][next_col] > 0:
                            queue.append((next_row, next_col))
                            visited.add((next_row, next_col))
                            n_fresh_oranges -= 1

                n_minutes += 1

            return n_minutes if n_fresh_oranges == 0 else -1
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(m \times n)$  
  The time complexity consists of two parts:
    - Scan the grid to fill the queue initially, which takes $O(m \times n)$ time.
    - Run BFS on the queue, which in the worst case would traverse all the cells exactly
    once and therefore takes $O(m \times n)$. 
  So the total time complexity is $O(m \times n) + O(m \times n) = O(m \times n)$.
- Space complexity: $O(m \times n)$  
  In the worst case, the grid is filled with rotten oranges. As a result, the queue 
  would be initialized with all the cells in the grid, which takes $O(m \times n)$ space.

## Test

- One element not rotten, `[[0]]`
- one element rotten, `[[2]]`