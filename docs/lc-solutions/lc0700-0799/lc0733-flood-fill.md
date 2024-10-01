---
tags:
    - Breadth-First Search
    - Depth-First Search
---

# LC733. Flood Fill

## Problem Description

[LeetCode Problem 733](https://leetcode.com/problems/flood-fill/): You are given an image represented by an `m x n` grid of integers `image`, where `image[i][j]` represents the pixel value of the image. You are also given three integers `sr`, `sc`, and `color`. Your task is to perform a **flood fill**on the image starting from the pixel `image[sr][sc]`.

To perform a **flood fill**:

1. Begin with the starting pixel and change its color to `color`.
2. Perform the same process for each pixel that is **directly adjacent**(pixels that share a side with the original pixel, either horizontally or vertically) and shares the **same color** as the starting pixel.
3. Keep **repeating** this process by checking neighboring pixels of the _updated_ pixels and modifying their color if it matches the original color of the starting pixel.
4. The process **stops** when there are **no more** adjacent pixels of the original color to update.

Return the **modified** image after performing the flood fill.

## Clarification

- Flood fill: fill the same color of directly adjacent pixels
- Adjacent: share a side with the original pixel
- Modify existing image directly?

## Assumption

- Image is valid and sr and sc are within the image range

## Solution

### Approach - BFS

Using BFS (breadth-first search) to find all adjacent pixels with the same color and fill with target color. No need to use a visited variable since the color change indicates the pixel visited.

=== "Python"
    ```python
    from collections import deque

    class Solution:
        def floodFill(self, image: List[List[int]], sr: int, sc: int, color: int) -> List[List[int]]:
            start_pixel_color = image[sr][sc]

            # No need to proceed if the start pixel already has the target color
            if start_pixel_color == color:
                return image

            # Step direction: up, down, left, right
            steps = [(1, 0), (-1, 0), (0, -1), (0, 1)]

            n_row, n_col = len(image), len(image[0])
            queue = deque([(sr, sc)])

            while queue:
                curr_row, curr_col = queue.popleft()

                # Fill the current pixel with the new color
                image[curr_row][curr_col] = color

                # Check all 4 possible directions
                for step_row, step_col in steps:
                    next_row, next_col = curr_row + step_row, curr_col + step_col
                    if 0 <= next_row < n_row and 0 <= next_col < n_col and image[next_row][next_col] == start_pixel_color:
                        queue.append((next_row, next_col))

            return image
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(m \times n)$ where $m$ is the number of rows and $n$ is the number of columns in the `image` matrix  
  In the worst case, all the pixels in the `image` are visited (exactly once).
  Explanation
- Space complexity: $O(m + n)$ where $m$ is the number of rows and $n$ is the number of columns in the `image` matrix  
  In the worst case, the maximum number of pixels is proportional to the perimeter of the region rather than the area. For a full rectangular region, the perimeter is $O(m + n)$.

### Approach2 - DFS

We can use DFS (depth-first search) to fill the adjacent pixels.

=== "python"
    ```python
    class Solution:
        def floodFill(self, image: List[List[int]], sr: int, sc: int, color: int) -> List[List[int]]:
            start_pixel_color = image[sr][sc]

            # If the starting pixel already has the target color, no need to proceed
            if start_pixel_color == color:
                return image

            self. dfs(image, sr, sc, color, start_pixel_color)
            return image

        def dfs(self, image: List[List[int]], r: int, c: int, color: int, start_color:int) -> None:
            n_row, n_col = len(image), len(image[0])
            steps = [(1, 0), (-1, 0), (0, -1), (0, 1)]

            if 0 <= r < n_row and 0 <= c < n_col and image[r][c] == start_color:
                image[r][c] = color
                for step_row, step_col in steps:
                    self.dfs(image, r + step_row, c + step_col, color, start_color)
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(m \times n)$  
  In the worst case, it may visit all pixels exact once when all pixels are connected with the same color.
- Space complexity: $O(\max(m, n))$  
  The space complexity is determined by the depth of the call stack. The max depth is the max distance from a pixel to 4 edges.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach - BFS |  $O(m \times n)$           | $O(m + n)$ |
Approach - DFS |  $O(m \times n)$           | $O(\max(m, n))$  |

## Test
