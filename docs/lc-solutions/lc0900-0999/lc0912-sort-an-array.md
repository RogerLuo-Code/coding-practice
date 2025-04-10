---
tags:
    - Sorting
---

# 912. Sort an array

## Problem Description

[LeetCode Problem 912](https://leetcode.com/problems/sort-an-array/description/): Given
an array of integers `nums`, sort the array in ascending order and return it.

You must solve the problem **without using any built-in** functions in `O(nlog(n))` time
complexity and with the smallest space complexity possible.

## Clarification

- Can we modify the input array?

## Assumption

-

## Solution

### Approach 1: Merge Sort (Top-Down)

We can use the merge sort algorithm to sort the array. The merge sort algorithm
is a divide-and-conquer algorithm that divides the array into two halves, sorts each half
recursively, and then merges the two sorted halves.

In this approach, we will use top-down merge sort.

=== "Python"
    ```python
    class Solution:
        def sortArray(self, nums: List[int]) -> List[int]:
            nums_copy = nums[:]  # Assump the input can't be chnaged
            aux = [0] * len(nums)  # Allocate auxiliary array for merge sort
            self.sortSubArray(nums_copy, aux, 0, len(nums) - 1)
            return nums_copy

        def sortSubArray(self, nums: list[int], aux: list[int], lo: int, hi: int) -> None:
            # Base Case
            if lo >= hi:
                return

            mid = (lo + hi) // 2
            self.sortSubArray(nums, aux, lo, mid)
            self.sortSubArray(nums, aux, mid + 1, hi)
            self.merge(nums, aux, lo, mid, hi)

        def merge(self, nums: list[int], aux: list[int], lo: int, mid: int, hi: int) -> None:
            aux[lo : hi+1] = nums[lo : hi+1]  # Refresh aux (current window) with partially sorted values in nums

            i, j = lo, mid + 1  # Pointers to left and right halves
            for k in range(lo, hi + 1):
                if i > mid:  # Left half exhausted
                    nums[k] = aux[j]
                    j += 1
                elif j > hi:  # Right half exhausted
                    nums[k] = aux[i]
                    i += 1
                elif aux[j] < aux[i]:  # Right element smaller
                    nums[k] = aux[j]
                    j += 1
                else:  # Left element smaller or equal
                    nums[k] = aux[i]
                    i += 1
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n \log n)$  
    - The array is recursively split in half --> $O(\log n)$ levels of recursion.
    - At each level, merging multiple two halves, taking $O(n)$ time across the
    **entire** level.
- Space complexity: $O(n)$  
    - Auxiliary array of size $n$ is used to store the merged result.
    - The space complexity of the recursive stack is $O(\log n)$ in a balanced case,
    but it is $O(n)$ in the worst case.
    - The overall space complexity is $O(n) + O(n) = O(n)$.

### Approach 2: Merge Sort (Bottom-Up)

We can also sort the array using bottom-up merge sort.

=== "python"
    ```python
    class Solution:
        def sortArray(self, nums: List[int]) -> List[int]:
            n = len(nums)
            aux = [0] * n  # Auxiliary array for merging

            size = 1
            while size < n:
                for lo in range(0, n - size, size * 2):
                    mid = lo + size - 1
                    hi = min(lo + size * 2 - 1, n - 1)
                    self.merge(nums, aux, lo, mid, hi)
                size *= 2

            return nums

        def merge(self, nums: list[int], aux: list[int], lo: int, mid: int, hi: int) -> None:
            # Refersh aux with partially sorted nums
            aux[lo : hi + 1] = nums[lo : hi + 1]

            i, j = lo, mid + 1
            for k in range(lo, hi + 1):
                if i > mid:
                    nums[k] = aux[j]
                    j += 1
                elif j > hi:
                    nums[k] = aux[i]
                    i += 1
                elif aux[j] < aux[i]:
                    nums[k] = aux[j]
                    j += 1
                else:
                    nums[k] = aux[i]
                    i += 1
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n \log n)$  
    - Doubling subarray size in the main loop leads to $\log n$ levels of merging.
    - At each level, all $n$ elements are processed, resulting in a total of $O(n)$
    work per level.
    - The overall time complexity is $O(n \log n)$.
- Space complexity: $O(n)$  
  An auxiliary array of size $n$ is used to store the merged result.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach 1 - Merge Sort (Top-Down) | $O(n \log n)$          | $O(n)$
Approach 2 - Merge Sort (Bottom-Up) | $O(n \log n)$          | $O(n)$

## Test
