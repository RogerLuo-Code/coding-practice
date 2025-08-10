---
tags:
    - Dynamic Programming
---

# 276. lc0276 paint fence

## Problem Description

[LeetCode Problem 276](https://leetcode.com/problems/paint-fence/description/):
You are painting a fence of `n` posts with `k` different colors. You must paint the
posts following these rules:

- Every post must be painted **exactly one** color.
- There **cannot** be three or more **consecutive** posts with the same color.

Given the two integers `n` and `k`, return _the **number of ways** you can paint the fence_.

## Clarification

-

## Assumption

- k > 1 for n > 2

## Solution

### Approach 1: Dynamic Programming

The problem can be solved using dynamic programming:

- **State**: `total_ways[i]` represents the number of ways to paint the first `i` posts.
- **Transition**: there are two scenarios to consider.
    - If using a **different** color than the previous post, there are `k - 1` options for
    the current post. So there are `(k - 1) * total_ways[i - 1]` ways to paint `i` posts
    for this scenario.
    - If using the **same** color as the previous post, there is only one color to use, so
    there are `1 * total_ways[i - 1]` ways to paint the `ith` post. However the
    **restriction** is "cannot be three or more consecutive posts with the same color."
    The number of ways to paint the `(i-1)th` post a different color from the `(i-2)th`
    post is `(k - 1) * total_ways[i - 2]`. So there are `1 * total_ways[i - 1] (different color from i - 2) = (k - 1) * total_ways[i - 2]`
    to paint `i` posts for this scenario.
    - Add above two scenarios together: `total_ways[i] = (k - 1) * total_ways[i - 1] + (k - 1) * total_ways[i - 2]`
- **Base Case**:
    - `total_ways[1] = k` (the first post)
    - `total_ways[2] = k * k` (the first two posts, which can have the same color)

=== "Python"
    ```python
    class Solution:
        def numWays(self, n: int, k: int) -> int:
            if n == 1:
                return k

            total_ways_prev_prev = k
            total_ways_prev = k * k
            for i in range(3, n + 1):
                total_ways_curr = (k - 1) * total_ways_prev + (k - 1) * total_ways_prev_prev
                total_ways_prev, total_ways_prev_prev = total_ways_curr, total_ways_prev

            return total_ways_prev
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  Need to iterate over `n` posts and each iteration takes $O(1)$ time. So the total time
  complexity is $O(n)$.
- Space complexity: $O(1)$  
  Only use 3 local variables to store values which are independent of input size.

### Approach 2: 

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

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - | $O(1)$          | $O(n)$
Approach - | $O(1)$          | $O(n)$

## Test
