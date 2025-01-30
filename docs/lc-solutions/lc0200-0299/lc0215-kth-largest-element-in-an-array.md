---
tags:
    - Heap
    - Quickselect
---

# LC215. Kth Largest Element in an Array

## Problem Description

[LeetCode Problem 215](https://leetcode.com/problems/kth-largest-element-in-an-array/):
Given an integer array `nums` and an integer `k`, return _the_ `kth` _largest element in
the array_.

Note that it is the `kth` largest element in the sorted order, not the `kth` distinct element.

Can you solve it without sorting?

## Clarification

- Integer array with duplicates
- Return the kth position in the sorted order. Not kth distinct element

## Assumption

-

## Solution

### Approach - Min-Heap

We can use min-heap to solve the problem. Push all the elements into a min-heap but pop
from the heap when the size exceeds `k`. By limiting the heap's size to `k`, after
handling all elements, the heap will contain exactly the `k` largest elements from the array.

=== "Python"
    ```python
    import heapq

    class Solution:
        def findKthLargest(self, nums: List[int], k: int) -> int:
            k_largest_queue = []

            for num in nums:
                heapq.heappush(k_largest_queue, num)
                if len(k_largest_queue) > k:
                    heapq.heappop(k_largest_queue)

            return k_largest_queue[0]
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n \log k)$  
    - We iterate `n` numbers and each iteration performs one or two heap operations. The
    heap operation takes $O(\log k)$ since the heap size is limited to `k`.
    - So the total time complexity is $O(n \log k)$.
- Space complexity: $O(k)$  
    The heap uses $O(k)$ space.

### Approach 2 - Quickselect

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
Approach - Min-Heap  |  $O(n \log k)$           | $O(k)$ |
Approach - Quickselect |  $O(1)$           | $O(n)$  |

## Test

- Small arrays where k=1k=1 or k=nk=n.
- Arrays with all identical elements.
- Negative numbers.
- Arrays with only one element.
