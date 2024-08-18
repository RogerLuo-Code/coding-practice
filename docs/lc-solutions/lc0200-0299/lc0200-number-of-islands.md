---
tags:
    - Breadth-First Search
    - Depth-First Search
---

# LC200. Number of Islands
## Problem Description
[LeetCode Problem 200](https://leetcode.com/problems/number-of-islands/): Given an `m x n` 2D binary grid `grid` which represents a map of `'1'`s (land) and `'0'`s (water), return _the number of islands_.

An **island** is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

## Clarification
- Definition of islands: connected `1`s surrounded by `0`s or edges of matrix (assume edges are surrounded by `0`s)
- Peninsula and island may be better words to describe

## Assumption
- Matrix is surrounded by water

## Solution
### Approach - BFS
The problem is equvalent to finding out number of groups with connected `1`s. When encountering a `1` and not visited before, consider it as a root node and use breadth-first search (BFS) to find all connected `1`s and mark them as visisted (either use `set` or mark them as `0`). Count the number of root nodes that trigger BFS. This number is the number of islands.

=== "Python"
    ```python
    from collections import deque

    class Solution:
        DIRECTIONS = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        def numIslands(self, grid: List[List[str]]) -> int:
            if not grid:
                return 0
            n_rows = len(grid)
            n_cols = len(grid[0])
            n_islands = 0
            queue = deque()
            visited = set()

            for i_row in range(n_rows):
                for j_col in range(n_cols):
                    if grid[i_row][j_col] == "1" and (i_row, j_col) not in visited:
                        queue.append((i_row, j_col))
                        visited.add((i_row, j_col))
                        n_islands += 1

                        # Visit connected 1s
                        while queue:
                            base_row, base_col = queue.popleft()
                            for step_row, step_col in self.DIRECTIONS:
                                next_row = base_row + step_row
                                next_col = base_col + step_col
                                if next_row >= 0 and next_row < n_rows and next_col >= 0 and next_col < n_cols \
                                    and grid[next_row][next_col] == "1" and (next_row, next_col) not in visited:
                                        queue.append((next_row, next_col))
                                        visited.add((next_row, next_col))

            return n_islands
    ```

#### Complexity Analysis
* Time complexity: $O(mn)$  
	The worst case is to search all nodes for connected `1`s. The total number of nodes is $m \times n$, where $m$ is number of rows and $n$ is number of columns of the grid.
* Space complexity: $O(mn)$  
	In the worst case, the size of queue and visisted hold all nodes, $m \times n$.

### Approach - DFS 
This problem can also be solved use depth-first search.

=== "python"
    ```python
    from collections import deque

    class Solution:
        DIRECTIONS = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        def numIslands(self, grid: List[List[str]]) -> int:
            if not grid:
                return 0

            n_islands = 0
            visited = set()
            for i_row in range(len(grid)):
                for j_col in range(len(grid[0])):
                    if grid[i_row][j_col] == "1" and (i_row, j_col) not in visited:
                        self.dfs(grid, i_row, j_col, visited)
                        n_islands += 1
            return n_islands

        def dfs(self, grid, i_row, j_col, visited):
            if i_row >= 0 and i_row < len(grid) and j_col >= 0 and j_col < len(grid[0]) \
                and grid[i_row][j_col] == "1" and (i_row, j_col) not in visited:
                    visited.add((i_row, j_col))
                    for step_row, step_col in self.DIRECTIONS:
                        self.dfs(grid, i_row + step_row, j_col + step_col, visited)
    ```

#### Complexity Analysis
* Time complexity: $O(mn)$  
	The worst case is to search all nodes for connected `1`s. 
* Space complexity: $O(mn)$  
	In the worst case, the recursive function depth is $m \times n$.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach -  |  $O(mn)$ 	   	   	| $O(mn)$ | 
Approach -  |  $O(mn)$      	| $O(mn)$  |

## Test