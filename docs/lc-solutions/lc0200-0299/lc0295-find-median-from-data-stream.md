---
tags:
    - Heap
---

# LC295. Find Median from Data Stream

## Problem Description

[LeetCode Problem 295](https://leetcode.com/problems/find-median-from-data-stream/description/):
The **median** is the middle value in an ordered integer list. If the size of the list
is even, there is no middle value, and the median is the mean of the two middle values.

- For example, for `arr = [2,3,4]`, the median is `3`.
- For example, for `arr = [2,3]`, the median is `(2 + 3) / 2 = 2.5`.

Implement the MedianFinder class:

- `MedianFinder()` initializes the `MedianFinder` object.
- `void addNum(int num)` adds the integer `num` from the data stream to the data structure.
- `double findMedian()` returns the median of all elements so far. Answers within `10-5`
of the actual answer will be accepted.

## Clarification

- Only add number, no remove?

## Assumption

-

## Solution

### Approach - Two Heaps

The idea is to divide numbers into 2 balanced halves: one half `small` stores smaller
numbers and the other half `large` stores larger numbers.

Then, we can use

- **max heap** to store a half of smaller numbers. The top of the max heap is the
largest number among small numbers.
- **min heap** to store a half of larger numbers. The top of the min heap is the lowest
number among large numbers.

When adding numbers, we need to balance the size between the max heap and min heap. After
adding `i` elements:

- if `i` is even, then `len(small) == len(large)`
- if `i` is odd, then `len(small) == len(large) + 1`

Since the both trees are balanced, the median will be either the top of max heap or
average of tops of both heaps.

=== "Python"
    ```python
    import heapq

    class MedianFinder:

        def __init__(self):
            self.left_max_heap = []
            self.right_min_heap = []

        def addNum(self, num: int) -> None:
            heapq.heappush(self.left_max_heap, -num)
            heapq.heappush(self.right_min_heap, -heapq.heappop(self.left_max_heap))  # (1)
            if len(self.right_min_heap) > len(self.left_max_heap):  # (2)
                heapq.heappush(self.left_max_heap, -heapq.heappop(self.right_min_heap))

        def findMedian(self) -> float:
            if len(self.left_max_heap) == len(self.right_min_heap):
                return (-self.left_max_heap[0] + self.right_min_heap[0]) / 2
            else:
                return -self.left_max_heap[0]
    ```

    1. Balance heap values to make sure smaller numbers in the max heap and larger.
    numbers in the min heap.
    2. Maintain size property: `max heap size == min heap size` or
    `max heap size == min heap size + 1`.

#### Complexity Analysis of Approach 1

- Time complexity:
    - Constructor takes $O(1)$ time.
    - `addNum` takes $O(\log n)$ where $n$ is the size of heap. When adding number, it
    takes at most 5 heap operations and each heap operation takes $O(\log n)$ time.
    - `findMedian` takes $O(1)$ since it simply retrieves the top values from two heaps.
- Space complexity: $O(n)$  
    - Need to store all $n$ numbers in two heaps.

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
Approach - Two Heaps |  $O(1)$, $O(\log n)$, $O(1)$           | $O(n)$ |
Approach -  |  $O(1)$           | $O(n)$  |

## Test

- **Only one number is added** → Return that number as median.
- **Even and odd number of elements** → Correctly handle averaging when needed.
- **All numbers are the same** → Median should return that same number.