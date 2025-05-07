---
tags:
    - Monotonic Stack
---

# 84. Largest Rectangle In Histogram

## Problem Description

[LeetCode Problem 84](https://leetcode.com/problems/largest-rectangle-in-histogram/description/):
Given an array of integers `heights` representing the histogram's bar height where the
width of each bar is `1`, return _the area of the largest rectangle in the histogram_.

## Clarification

- The largest area could be just one bar or shared area of multiple bars

## Assumption

-

## Solution

### Approach 1: Brute Force

This problem can be solved using a brute force approach. The idea is to iterate
over each bar in the histogram, find the
width of the rectangle that can be formed with that bar as the smallest height, and
then calculate the area of that rectangle as `height * width`. The maximum area
found during this process will be the answer.

=== "Python"
    ```python
    class Solution:
        def largestRectangleArea(self, heights: List[int]) -> int:
            n = len(heights)
            max_area = 0
            for i in range(n):
                count = 1  # count consecutive heights >= current height, start with 1 including the current height

                # Check right side, starting from the right neighbor
                for j in range(i + 1, n):
                    if heights[j] >= heights[i]:
                        count += 1
                    else:
                        break
                # Check left side, starting from the left neighbor
                for j in range(i - 1, -1, -1):
                    if heights[j] >= heights[i]:
                        count += 1
                    else:
                        break

                # Calculate area and update the max area
                max_area = max(heights[i] * count, max_area)

            return max_area
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n^2)$  
  The outer loop iterates over each bar, and the inner loops check the left and right
  neighbors of each bar. In the worst case, this results in $O(n^2)$ time complexity.
- Space complexity: $O(1)$  
  The algorithm uses a constant amount of space to store variables like `max_area` and
  `count`, regardless of the input size.

### Approach 2: Monotonic Increasing Stack

This problem can be solved using a monotonic increasing stack. The idea is to
maintain a stack to store indices of the bars in increasing order of their heights.
When we encounter a bar that is shorter than the bar at the top of the stack, we pop
from the stack and calculate the area of the rectangle formed with the popped bar as
the smallest height.

- The height of the rectangle is the height of the popped bar.
- The width of the rectangle is determined by:
    - **If the stack is empty** after popping, the width is the current index `i`, i.e.,
    `width = i`. This means that **the popped bar is the smallest height** in the rectangle
    since the stack is monotonic increasing. The rectangle extends from the beginning of
    the histogram to the current index.
    - **If the stack is not empty**, the width is the difference between the current index
    `i` and the index of the new top of the stack, `stack[-1]`, minus one,
    `width = i - stack[-1] - 1`. Since the stack is in increasing order,
    the **popped bar** is larger than previous bar (index of `[stack[-1]`, top of the
    stack after popping). The popped bar is also smaller than the current bar, which
    triggers the popping. Therefore,
    `previous bar (index of stack[-1]) <= popped bar > current bar (i)`. The range of
    rectangle extends from `stack[-1]` to the current index `i`, **minus one** to exclude
    `stack[-1]` since the `corresponding bar <= popped bar`.

The area is calculated as `height * width`, where `height` is the height of the popped
bar and `width` is the width of the rectangle. We continue this process until we have
processed all the bars in the histogram.

=== "python"
    ```python
    class Solution:
        def largestRectangleArea(self, heights: List[int]) -> int:
            stack = []  # Stack to store indices of the bars
            max_area = 0
            n = len(heights)

            for i in range(n + 1):  # Use n + 1 to flush the stack at the end
                # Use 0 as the height for the last bar to flush the stack
                # (1)
                current_height = heights[i] if i < n else 0

                while stack and heights[stack[-1]] > current_height:
                    height = heights[stack.pop()]
                    if not stack:
                        width = i
                    else:
                        width = i - stack[-1] - 1
                    max_area = max(max_area, height * width)

                stack.append(i)
    ```

    1. This ensures that all bars are processed and the stack is empty at the end. This is a trick to handle the last bar and calculate the area for all remaining bars in the stack.

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  The algorithm processes each bar in the histogram once, and each bar is pushed and
  popped from the stack at most once, resulting in a linear time complexity.
- Space complexity: $O(n)$  
  The stack can store all the indices of the bars in the worst case, leading to a linear
  space complexity.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach                     | Time Complexity | Space Complexity
-----------------------------|-----------------|-----------------
Approach 1 - Brute           | $O(n^2)$        | $O(1)$
Approach 2 - Monotonic Stack | $O(n)$          | $O(n)$

## Test
