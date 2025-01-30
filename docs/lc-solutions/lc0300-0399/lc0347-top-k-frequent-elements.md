---
tags:
    - Heap
    - Quickselect
---

# LC347. Top K Frequent Elements

## Problem Description

[LeetCode Problem 347](https://leetcode.com/problems/top-k-frequent-elements/description/):
Given an integer array `nums` and an integer `k`, return _the_ `k` _most frequent
elements_. You may return the answer in **any order**.

## Clarification

- Most frequent elements --> top number of appearances
- What to return, when k > len(num)

## Assumption

-

## Solution

### Approach - Heap

First, count number of appearances for each number. Then push
`(number of appearances, num)` to a **min** heap with size `k`. After pushing all pairs,
the heap stores top `k` frequent elements.

=== "Python"
    ```python
    import heapq
    from collections import defaultdict


    class Solution:
        def topKFrequent(self, nums: List[int], k: int) -> List[int]:
            # Count number of appearances for each number.
            num_appearances = defaultdict(lambda: 0)
            for num in nums:
                num_appearances[num] += 1

            # Use Min Heap to store top k (number of appearances, num)
            min_heap = []
            for num, n_appearances in num_appearances.items():
                heapq.heappush(min_heap, (n_appearances, num))
                if len(min_heap) > k:
                    heapq.heappop(min_heap)

            # Return k most frequent num
            return [heapq.heappop(min_heap)[1] for i in range(len(min_heap))]
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n \log k)$  
    - Counting number of appearances takes $O(n)$ time since iterating the array `nums`.
    - For min heap operations, iterate $n$ pairs and each iteration perform one or two
    heap operations. The heap operations takes $O(\log k)$ since the heap size is `k`.
    The time complexity is $O(n \log k)$.
    - Return a list from heap takes $O(k)$ since go through all `k` elements in the heap.
    - The total time complexity is $O(n) + O(n \log k) + O(k) = O(n \log k)$
- Space complexity: $O(n)$  
    - The dictionary to store number of appearances for each number takes $O(n)$ space.
    - Min heap takes $O(k)$ space since stores `k` elements.
    - The total space complexity is $O(n) + O(k) = O(n)$.

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
Approach - Heap |  $O(n \log k)$           | $O(n)$ |
Approach -  |  $O(1)$           | $O(n)$  |

## Test
