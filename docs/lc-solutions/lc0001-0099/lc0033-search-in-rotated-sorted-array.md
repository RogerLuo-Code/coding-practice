---
tags:
    - Binary Search
---

# LC33. Search in Rotated Sorted Array
## Problem Description
[LeetCode Problem 33](https://leetcode.com/problems/search-in-rotated-sorted-array/
): There is an integer array `nums` sorted in ascending order (with **distinct** values).

Prior to being passed to your function, `nums` is **possibly rotated** at an unknown pivot index `k` (`1 <= k < nums.length`) such that the resulting array is `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]` (**0-indexed**). For example, `[0,1,2,4,5,6,7]` might be rotated at pivot index `3` and become `[4,5,6,7,0,1,2]`.

Given the array `nums` **after** the possible rotation and an integer `target`, return _the index of_ `target` _if it is in_ `nums`_, or_ `-1` _if it is not in_ `nums`.

You must write an algorithm with `O(log n)` runtime complexity.

## Clarification
- nums sorted in ascending order
- no duplicates
- array is rotated at certain index
- find target

## Assumption

## Solution
### Approach - Binary Search
The original array is sorted in ascending order and then rotated at some pivot. So the array can be always divided into two parts: one part is sorted and the other part is unsorted, containing the pivot. It is easy to check whether the target is in the sorted part and search inside that part. If the target is in the unsorted part, we can further divide the unsorted part into two parts (again one part will be sorted and the other will be unsorted) and continue to check the sorted part. This allow us using binary search to find the target.

The search space starts from the whole array and shrinks over each iteration, using `[left, right]`` to indicate the search space. The mid is the separation point to divide the search space into two parts, one is sorted and the other is unsorted.

We need to handle the the first 3 situations below:

1. `nums[left] <= nums[mid] <= nums[right]`, the whole array is sorted
2. `nums[left] > nums[mid] <= nums[right]`,  right half is sorted
3. `nums[left] <= nums[mid] > nums[right]`,  left half is sorted
4. `nums[left] > nums[mid] > nums[right]`, impossible since array is sorted in non-decreasing

So we can compare `nums[left]` and `nums[mid]` to decide which half is sorted
- If `nums[left] <= nums[mid]`, the sub-array `[left, mid]` is sorted. This is true when an array has **no duplicates**. It is easy to check whether the target is inside this part. If not, continue to divide and search the right half.
- If `nums[left] > nums[mid]`,the right sub-array `[mid,right]` is sorted. We can check whether the target is in the right part. If not, continue to divide and search the left half.

=== "Python"
```python
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1

        while left <= right:
            mid = (left + right) // 2

            if target == nums[mid]:
                return mid
            elif nums[left] <= nums[mid]:
                # [left, mid] section is sorted
                if nums[left] <= target and target < nums[mid]:
                    right = mid - 1
                else:
                    left = mid + 1
            else:
                # [mid, right] section is sorted
                if nums[mid] < target and target <= nums[right]:
                    left = mid + 1
                else:
                    right = mid - 1

        return -1
```

#### Complexity Analysis
* Time complexity: $O(\log n)$  
	Essentially still use binary search. So the time complexity is $O(\log n)$.  
* Space complexity: $O(1)$  
	Use several index variables for binary search.  
