---
tags:
    - Binary Search
---

# LC154. Find Minimum in Rotated Sorted Array II
## Problem Description
[LeetCode Problem 154](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii): Suppose an array of length `n` sorted in ascending order is **rotated**between `1` and `n` times. For example, the array `nums = [0,1,4,4,5,6,7]` might become:

- `[4,5,6,7,0,1,4]` if it was rotated `4` times.
- `[0,1,4,4,5,6,7]` if it was rotated `7` times.

Notice that **rotating** an array `[a[0], a[1], a[2], ..., a[n-1]]` 1 time results in the array `[a[n-1], a[0], a[1], a[2], ..., a[n-2]]`.

Given the sorted rotated array `nums` that may contain **duplicates**, return _the minimum element of this array_.

You must decrease the overall operation steps as much as possible.

## Clarification
- sorted and rotated
- contain duplicates
- the array can be rotated back to it original values

## Assumption

## Solution
### Approach - Binary Search
The big difference between this problem and [LC153](lc0153-find-minimum-in-rotated-sorted-array.md) is that the array may contain duplicates. So when `nums[mid] == nums[right]`, the position of minimum could be in either left or right of mid (e.g., `[3,3,3,3,1,3]`, or `[3,1,3,3,3,3]`). So

- For relationship 1, `nums[left] <= nums[mid] <= nums[right]`, `min` could be on either left half or right half when `nums[left] == nums[mid] == nums[right]`

So we need to hanlde the special case `nums[left] == nums[mid] == nums[right]`

=== "Python"
    ```python
    class Solution:
        def findMin(self, nums: List[int]) -> int:
            left, right = 0, len(nums) - 1

            while left < right:
                mid = (left + right) // 2

                if nums[mid] > nums[right]:
                    left = mid + 1
                elif nums[left] == nums[mid] and nums[mid] == nums[right]:
                    left += 1
                    right -= 1
                else:
                    right = mid

            return nums[left]
    ```

#### Complexity Analysis
* Time complexity: $O(\log n)$ for average case, $O(n)$ for the worst case  
	In the worst case, it reduce the search space by two elements at a time and takes $O(n)$ time. For the average case, the time complexity is $O(\log n)$ with the binary search.
* Space complexity: $O(1)$  
	Only use two variables for indices. 

## Test