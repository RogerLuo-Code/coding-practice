---
tags:
    - Binary Search
---

# LC704. Binary Search
## Problem Description
[LeetCode Problem 704](https://leetcode.com/problems/binary-search/): Given an array of integers `nums` which is sorted in ascending order, and an integer `target`, write a function to search `target` in `nums`. If `target` exists, then return its index. Otherwise, return `-1`.

You must write an algorithm with `O(log n)` runtime complexity.

## Clarification
- sorted, ascending order
- target may not exist
- O(logn)
- return index
- what about duplicates

## Assumption

## Solution
### Approach - Binary Search
Since the array is sorted, we can use the standard binary search to find the target. Each execution cuts one half that is guaranteed not to contain `target`.

=== "Python"
```python
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1

        while left <= right:
            mid = (left + right) // 2
            if target == nums[mid]:
                return mid
            elif target < nums[mid]:
                right = mid - 1
            else:
                left = mid + 1

        return -1
```

#### Complexity Analysis
Assume array `nums` size is `n`  

* Time complexity: $O(\log n)$  
	The search space is divided by half each time. In the worse case, we need to cut `nums` until no more element, which takes $\log n$ steps.
* Space complexity: $O(1)$  
	Only need three indices, `left`, `right`, and `mid`, which take constant space.

## Test
- Test target on two ends
