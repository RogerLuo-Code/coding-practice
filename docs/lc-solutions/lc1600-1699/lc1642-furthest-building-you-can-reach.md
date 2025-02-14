---
tags:
    - Heap
---

# LC1642. Furthest Building You Can Reach

## Problem Description

[LeetCode Problem 1642](https://leetcode.com/problems/furthest-building-you-can-reach/description/):
You are given an integer array `heights` representing the heights of buildings, some
`bricks`, and some `ladders`.

You start your journey from building `0` and move to the next building by possibly using
bricks or ladders.

While moving from building `i` to building `i+1` (**0-indexed**),

- If the current building's height is **greater than or equal** to the next building's
height, you do **not** need a ladder or bricks.
- If the current building's height is **less than** the next building's height, you can
either use **one ladder** or `(h[i+1] - h[i])` **bricks**.

_Return the furthest building index (0-indexed) you can reach if you use the given
ladders and bricks optimally._

## Clarification

- integer array is 0-indexed
- use either 1 ladder or (h[i+1] - h[i]) bricks

## Assumption

-

## Solution

### Approach - Heap

The best strategy is to use the ladder for the longest climbs and the bricks for the
shortest climbs.

We can use max heap to track number of bricks used for each step. If running out of
bricks, replace the longest climb with a ladder.

=== "Python"
    ```python
    import heapq

    class Solution:
        def furthestBuilding(self, heights: List[int], bricks: int, ladders: int) -> int:
            max_heap = []
            for i in range(0, len(heights) - 1):
                climb = heights[i + 1] - heights[i]

                # Jump down or walk flat, no need a ladder or bricks
                if climb <= 0:
                    continue

                # Use bricks for this climb and always push it to the max heap
                heapq.heappush(max_heap, -climb)  # (1)
                bricks -= climb

                # If used all the bricks and ladders, return the current index
                if bricks < 0 and ladders == 0:
                    return i  # (2)

                # Run out of bricks. Replace the largest bricks in previous steps with a ladder
                if bricks < 0:
                    bricks += -heapq.heappop(max_heap)
                    ladders -= 1

            # Have enough bricks and ladders to reach the end
            return len(heights) - 1
    ```

    1. Push negative value to use a min heap as a max heap.
    2. `i` is the current building, `i + 1` is the next building to climb but failed.

#### Complexity Analysis of Approach 1

- Time complexity: $O(n \log n)$  
    - Iterate all $n$ heights and each iteration has at most 2 heap operations. Each
    heap operation takes $O(\log s)$ time with heap size $s$. In the worst case, the
    heap size increases from 1 to $n$ after each iteration. The time complexity is
    $O(\log 1) + O(\log 2) + \cdots + O(\log n) \approx n \log n$.
- Space complexity: $O(n)$  
    In the worst case, the heap stores $n - 1$ climbs.

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
Approach - Max Heap |  $O(n \log n)$           | $O(n)$ |
Approach -  |  $O(1)$           | $O(n)$  |

## Test

- **All buildings are the same height** → No bricks or ladders needed.
- **Enough bricks to reach the last building** → Ladders may not be used.
- **Large jumps appear early** → Ladders should be prioritized.