---
tags:
    - Binary Search
---

# LC34. Find First and Last Position of Element in Sorted Array
## Problem Description
[LeetCode Problem 34](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/): Given an array of integers `nums` sorted in non-decreasing order, find the starting and ending position of a given `target` value.

If `target` is not found in the array, return `[-1, -1]`.

You must write an algorithm with `O(log n)` runtime complexity.

## Clarification
- array sorted, non-decreasing
- start and end position for target
- there are duplicates

## Assumption

## Solution
### Approach - Binary Search
Use binary search twice, one searches start position and the other searches the end position. 

=== "Python"
```python
class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        left, right = 0, len(nums) - 1
        if right < 0:
            return [-1, -1]

        # Find the start position
        while left < right:
            mid = (left + right) // 2
            if target == nums[mid]:
                right = mid
            elif target > nums[mid]:
                left = mid + 1
            else:
                right = mid - 1

        if nums[left] == target:
            start_pos = left
        else:
            start_pos = -1

        # Find the end position
        left, right = max(0, start_pos), len(nums) - 1

        while left < right - 1:
            mid = (left + right) // 2
            if target == nums[mid]:
                left = mid
            elif target > nums[mid]:
                left = mid + 1
            else:
                right = mid - 1

        if nums[right] == target:
            end_pos = right
        elif nums[left] == target:
            end_pos = left
        else:
            end_pos = -1

        return [start_pos, end_pos]
```

#### Complexity Analysis
* Time complexity: $O(\log n)$  
	Use binary search twice. Each binary search takes at most $\log n$ steps and total steps are at most $2 \log n$.
* Space complexity: $O(1)$  
	Only use several index variables.