---
tags:
    - Heap
    - Line Sweep
    - Divide and Conquer
---

# 218. The Skyline Problem

## Problem Description

[LeetCode Problem 218](https://leetcode.com/problems/the-skyline-problem/description/):
A city's **skyline** is the outer contour of the silhouette formed by all the buildings
in that city when viewed from a distance. Given the locations and heights of all the
buildings, return _the **skyline** formed by these buildings collectively_.

The geometric information of each building is given in the array `buildings`
where `buildings[i] = [lefti, righti, heighti]`:

- `lefti` is the x coordinate of the left edge of the `ith` building.
- `righti` is the x coordinate of the right edge of the `ith` building.
- `heighti` is the height of the `ith` building.

You may assume all buildings are perfect rectangles grounded on an absolutely flat
surface at height `0`.

The **skyline** should be represented as a list of "key points"
**sorted by their x-coordinate** in the form `[[x1,y1],[x2,y2],...]`. Each key point is
the left endpoint of some horizontal segment in the skyline except the last point in
the list, which always has a y-coordinate `0` and is used to mark the skyline's
termination where the rightmost building ends. Any ground between the leftmost and
rightmost buildings should be part of the skyline's contour.

**Note:** There must be no consecutive horizontal lines of equal height in the output
skyline. For instance, `[...,[2 3],[4 5],[7 5],[11 5],[12 7],...]` is not acceptable;
the three lines of height 5 should be merged into one in the final output as such:
`[...,[2 3],[4 5],[12 7],...]`

## Clarification

-

## Assumption

-

## Solution

### Approach 1: Sweep Line with Max-Heap

The problem can be solved using sweep line algorithm combined with a max-heap. It
processes building edges in order and tracks active building heights to determine the skyline.

=== "Python"
    ```python
    import heapq

    class Solution:
        def getSkyline(self, buildings: list[list[int]]) -> list[list[int]]:
            # Step 1: Create all the critical points
            events = []
            for left, right, height in buildings:
                events.append((left, -height))  # entering event (using negative height)
                events.append((right, height))  # exiting event

            # Step 2: Sort events
            # Sort by x-coordinate; if tie, sort by height: entering before exiting
            events.sort(key=lambda x: (x[0], x[1]))

            # Step 3: Max-heap to keep track of active building heights
            result = []
            max_heap = [0]  # initial ground height
            heap_counter = {0: 1}  # track occurrences
            prev_max = 0

            for x, h in events:
                if h < 0:  # entering a building
                    heapq.heappush(max_heap, h)
                    heap_counter[-h] = heap_counter.get(-h, 0) + 1
                else:  # exiting a building
                    heap_counter[h] -= 1

                # Clean up the heap (remove heights that are no longer active)
                while max_heap and heap_counter[-max_heap[0]] == 0:
                    heapq.heappop(max_heap)

                current_max = -max_heap[0]
                if current_max != prev_max:
                    result.append([x, current_max])
                    prev_max = current_max

            return result
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n \log n)$  
    - Sorting takes $O(n \log n)$ time for $n$ events (twice the number of buildings). 
    - Go through $n$ events and each iteration takes $O(\log n)$ heap operation. So
    the time complexity is $O(n \log n)$
    - So the overall time complexity is $O(n \log n)$
- Space complexity: $O(n)$  
    - Sorting events takes $O(n)$ space.
    - The heap takes $O(n)$ space.
    - So the over space complexity is $O(n)$.

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
