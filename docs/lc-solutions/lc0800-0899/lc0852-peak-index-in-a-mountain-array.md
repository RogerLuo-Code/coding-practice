---
tags:
- Binary Search
---

# LC852. Peak Index in a Mountain Array
## Problem Description
[LeetCode Problem 852](https://leetcode.com/problems/peak-index-in-a-mountain-array/): An array `arr` is a **mountain** if the following properties hold:

- `arr.length >= 3`
- There exists some `i` with `0 < i < arr.length - 1` such that:
    - `arr[0] < arr[1] < ... < arr[i - 1] < arr[i]`
    - `arr[i] > arr[i + 1] > ... > arr[arr.length - 1]`

Given a mountain array `arr`, return the index `i` such that `arr[0] < arr[1] < ... < arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1]`.

You must solve it in `O(log(arr.length))` time complexity.

## Clarification

## Assumption

## Solution
### Approach - Binary Search
We can use binary search to find the peak by checking whether `arr[mid] < arr[mid + 1]`:

- true, means climbing up from left, the peak is on the right half
- false, means on the right side, peak is on the left half

=== "Python"
    ```python
    class Solution:
        def peakIndexInMountainArray(self, arr: List[int]) -> int:
            left, right = 0, len(arr) - 1

            while left < right:
                mid = (left + right) // 2

                if arr[mid] < arr[mid + 1]:
                    left = mid + 1
                else:
                    right = mid

            return left
    ```

#### Complexity Analysis
* Time complexity: $O(\log n)$  
Since using binary search, the time complexity is $O(\log n)$.
* Space complexity: $O(1)$  
Only use two index variables.

## Test