---
tags:
    - Heap
---

# LC703. Kth Largest Element in a Stream

## Problem Description

[LeetCode Problem 703](https://leetcode.com/problems/kth-largest-element-in-a-stream/description/):
You are part of a university admissions office and need to keep track of the `kth`
highest test score from applicants in real-time. This helps to determine cut-off marks
for interviews and admissions dynamically as new applicants submit their scores.

You are tasked to implement a class which, for a given integer `k`, maintains a stream
of test scores and continuously returns the `k`th highest test score **after** a new
score has been submitted. More specifically, we are looking for the `k`th highest score
in the sorted list of all scores.

Implement the `KthLargest` class:

- `KthLargest(int k, int[] nums)` Initializes the object with the integer `k` and the
stream of test scores `nums`.
- `int add(int val)` Adds a new test score `val` to the stream and returns the element
representing the `kth` largest element in the pool of test scores so far.

## Clarification

- Track the kth highest test score **real time**

## Assumption

-

## Solution

### Approach - Heap

Use min heap to track the top k test scores.

=== "Python"
    ```python
    import heapq


    class KthLargest:

        def __init__(self, k: int, nums: List[int]):
            self.min_heap = []
            self.min_heap_size = k
            for num in nums:
                self.add(num)

        def add(self, val: int) -> int:
            heapq.heappush(self.min_heap, val)
            if len(self.min_heap) > self.min_heap_size:
                heapq.heappop(self.min_heap)

            return self.min_heap[0]  # (1)
    ```

    1. The smallest value in the heap is the `kth` largest element.

#### Complexity Analysis of Approach 1

- Time complexity: $O(n \log k)$ where $n$ is the total number of values including
initial values in `nums` and later added ones.
    - The `add` function is called total $n$ times. Each `add` performs one or two heap
    operations. Each operation takes $O(\log k)$ for the heap size $k$.
    - The total time complexity is $O(n \log k)$.
- Space complexity: $O(k)$  
    The min heap stores at most $k$ elements.

## Test
