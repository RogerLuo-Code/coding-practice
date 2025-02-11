---
tags:
    - Heap
    - Quickselect
---

# LC973. K Closest Points to Origin

## Problem Description

[LeetCode Problem 973](https://leetcode.com/problems/k-closest-points-to-origin/description/):
Given an array of `points` where `points[i] = [xi, yi]`represents a point on the
**X-Y** plane and an integer `k`, return the `k` closest points to the origin `(0, 0)`.

The distance between two points on the **X-Y** plane is the Euclidean distance (i.e.,
$\sqrt{(x1 - x2)^2 + (y1 - y2)^2}$).

You may return the answer in **any order**. The answer is **guaranteed** to be
**unique** (except for the order that it is in).

## Clarification

- Return the k closest points
- Euclidean distance definition
- Return the answer in any order

## Assumption

- k > 0
- No duplicate points

## Solution

### Approach - Heap

We can use max heap with size k to store points with distance. When pushing points
and the size > k, the furthest points away from the origin are removed. In the end, only
the k closest points remained.

=== "Python"
    ```python
    import heapq
    import math

    class Solution:
        def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        max_heap = []

            for i in range(len(points)):
                dist_to_origin = points[i][0] ** 2 + points[i][1] ** 2
                heapq.heappush(
                    max_heap, (-dist_to_origin, i)
                )  # Push negative value to achieve max heap by using min heap

                if len(max_heap) > k:
                    heapq.heappop(max_heap)

            return [points[i] for (_, i) in max_heap]
    ```

    1. Push negative value to achieve max heap by using min heap.

#### Complexity Analysis of Approach 1

- Time complexity: $O(n \log k)$  
    - Iterate all $n$ points. Each iteration will do at most two heap operations. The
    heap operation takes $O(\log k)$ time since the heap size is at most $k$. So the
    time complexity is $O(n \log k)$.
    - Return results by iterating the heap, which takes $O(k)$.
    - So the total time complexity is $O(n \log k) + O(k) = O(n \log k)$.
- Space complexity: $O(k)$  
    The heap takes $O(k)$ space to store $k$ elements.

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
Approach - Heap |  $O(n \log k)$           | $O(k)$ |
Approach -  |  $O(1)$           | $O(n)$  |

## Test
