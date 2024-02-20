---
tags:
    - Binary Search
---

# LC81. Search in Rotated Sorted Array II
## Problem Description
[LeetCode Problem 81](https://leetcode.com/problems/search-in-rotated-sorted-array-ii): There is an integer array `nums` sorted in non-decreasing order (not necessarily with **distinct** values).

Before being passed to your function, `nums` is **rotated** at an unknown pivot index `k` (`0 <= k < nums.length`) such that the resulting array is `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]` (**0-indexed**). For example, `[0,1,2,4,4,4,5,6,6,7]`might be rotated at pivot index `5` and become `[4,5,6,6,7,0,1,2,4,4]`.

Given the array `nums` **after** the rotation and an integer `target`, return `true` _if_ `target` _is in_ `nums`_, or_ `false` _if it is not in_ `nums`_._

You must decrease the overall operation steps as much as possible.

## Clarification
- sorted and rotated
- have duplicates

## Assumption

## Solution
### Approach - Binary Search
This is a follow-up problem to [LC33 - Search in Rotated Sorted Array](lc0033-search-in-rotated-sorted-array.md). The difference is that it contains duplicates. We can still divide the array into a sorted part and a unsorted part and then search. Due to duplicates, 

- For situation 1 in [LC33](lc0033-search-in-rotated-sorted-array.md), `nums[left] <= nums[mid] <= nums[right]`, when `nums[left] == nums[mid] == nums[right]`, we don’t know which part (left or right) is sorted. For example, `[3,1,3,3,3,3,3]` with left part unsorted and `[3, 3, 3, 3, 3, 1, 3]` with right part unsorted. For this case, if `target != nums[mid]`, we can increase left and decrease right by 1.

=== "Python"
    ```python
    class Solution:
        def search(self, nums: List[int], target: int) -> bool:
            left, right = 0, len(nums) - 1

            while left <= right:
                mid = (left + right) // 2
                if nums[mid] == target:
                    return True
                elif nums[left] == nums[mid] and nums[mid] == nums[right]:
                    left += 1
                    right -= 1
                elif nums[left] <= nums[mid]:  # (1)
                    # [left, mid] non-decreasing
                    if nums[left] <= target and target < nums[mid]:
                        right = mid - 1
                    else:
                        left = mid + 1
                else:
                    # [mid, right] non-decreasing
                    if nums[mid] < target and target <= nums[right]:
                        left = mid + 1
                    else:
                        right = mid - 1

            return False
    ```

    1. Add `=` to handle case `left == mid``

#### Complexity Analysis
* Time complexity: $O(\log n)$ for the average, $O(n)$ for the worst case  
	In the worst case, just move left pointer by one, which needs n steps. So the time complexity is $O(n)$. For the average case, since using binary search, the time complexity is $O(\log n)$.
* Space complexity: $O(1)$  
	Only use limited variables for indices.

## Test
- Only two numbers, e.g. `[3, 1]`
- Test array with `nums[left] == nums[mid]``