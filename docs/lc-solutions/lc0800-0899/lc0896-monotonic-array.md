---
tags:
    - Array
---

# LC896. Monotonic Array
## Problem Description
[LeetCode Problem 896](https://leetcode.com/problems/monotonic-array/): An array is **monotonic** if it is either monotone increasing or monotone decreasing.

An array `nums` is monotone increasing if for all `i <= j`, `nums[i] <= nums[j]`. An array `nums` is monotone decreasing if for all `i <= j`, `nums[i] >= nums[j]`.

Given an integer array `nums`, return `true` _if the given array is monotonic, or_ `false` _otherwise_.

## Clarification
- < vs <= (strictly monotonic?)
- either increase or decrease

## Assumption

## Solution
### Approach
Start from the basic definition where 

- Monotonic increase: $nums[i + 1] >= nums[i]$ for all $i$. For strictly monotonic, use `>`.
- Monotonic decrease: $nums[i + 1] <= nums[i]$ for all $i$. For strictly monotonic, use `<`.

=== "Python"
```python
class Solution:
    def isMonotonic(self, nums: List[int]) -> bool:
        isMonotonicIncrease = True
        isMonotonicDecrease = True
        for i in range(len(nums) - 1):
            if nums[i] > nums[i + 1]:
                isMonotonicIncrease = False

            if nums[i] < nums[i + 1]:
                isMonotonicDecrease = False

            if not isMonotonicIncrease and not isMonotonicDecrease:
                break

        return isMonotonicIncrease or isMonotonicDecrease
```

#### Complexity Analysis
* Time complexity: $O(n)$  
	In the worst case, need to go through the whole array.
* Space complexity: $O(1)$  
	Use a pointer and limited local variables.

## Test