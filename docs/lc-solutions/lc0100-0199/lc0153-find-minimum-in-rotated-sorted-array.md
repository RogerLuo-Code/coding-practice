---
tags:
    - Binary Search
---

# LC153. Find Minimum in Rotated Sorted Array
## Problem Description
[LeetCode Problem 153](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array): Suppose an array of length `n` sorted in ascending order is **rotated**between `1` and `n` times. For example, the array `nums = [0,1,2,4,5,6,7]` might become:

- `[4,5,6,7,0,1,2]` if it was rotated `4` times.
- `[0,1,2,4,5,6,7]` if it was rotated `7` times.

Notice that **rotating** an array `[a[0], a[1], a[2], ..., a[n-1]]` 1 time results in the array `[a[n-1], a[0], a[1], a[2], ..., a[n-2]]`.

Given the sorted rotated array `nums` of **unique** elements, return _the minimum element of this array_.

You must write an algorithm that runs in `O(log n) time.`

## Clarification
- sorted and rotated
- unique elements (no duplicates)
- the array can be rotated back to it original values

## Assumption

## Solution
### Approach - Binary Search
Since the array is originally sorted and rotated between 1 and n times,
there will be two potential forms after rotations:

- The whole array is sorted in the ascending order (i.e., the array rotates back to the original one );
- There is a pivot point in the array, which separate the array into two halves: one half is sorted and the other is not sorted.

So if we can detect which half is not sorted, we know that the minimum value should be in that unsorted half and ignore the sorted half. If both halves are sorted, the first left element is the minimum. If we split the array into two halves, `[left, mid]` and `[mid + 1, right]`, there are 4 kinds of relationship among `nums[left]`, `nums[mid]`, and `nums[right]`:

1. `nums[left] <= nums[mid] <= nums[right]`, `min` is `nums[left]`
2. `nums[left] > nums[mid] <= nums[right]`, `[left, mid]` is not sorted and `min` is in the left half
3. `nums[left] <= nums[mid] > nums[right]`, `[mid, right]` is not sorted and `min` is in the right half
4. `nums[left] > nums[mid] > nums[right]`, impossible since the original array is sorted in ascending order.

So we can check `nums[mid]` and `nums[right]`:

- If `nums[mid] > nums[right]`, search the right half, covering the relationship 3
- If `nums[mid] <= nums[right]`, search the left half, covering the relationship 1 and 2, since in both cases the minimum is on the left.

???+ note
    If we just check `nums[left]` and `nums[mid]`, the condition `nums[left] <= nums[mid]` can't distinguish relationship 1 and 3 which requires searching in two different directions. This requires an addition condition check on whether the whole array is sorted.

=== "Python"
    ```python
    class Solution:
        def findMin(self, nums: List[int]) -> int:
            left, right = 0, len(nums) - 1

            while left < right:
                mid = (left + right) // 2
                if nums[mid] > nums[right]:
                    left = mid + 1
                else:
                    right = mid

            return nums[left]
    ```

#### Complexity Analysis
* Time complexity: $O(\log n)$  
	Since using binary search, the time complexity is $O(\log n)$.
* Space complexity: $O(1)$  
	Only use two variables for indices. 

## Test