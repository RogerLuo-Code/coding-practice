---
tags:
- Binary Search
---

# LC540. Single Element in a Sorted Array
## Problem Description
[LeetCode Problem 540](https://leetcode.com/problems/single-element-in-a-sorted-array/): You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.

Return _the single element that appears only once_.

Your solution must run in `O(log n)` time and `O(1)` space.

## Clarification
- sorted array with integers
- only one element appears once

## Assumption

## Solution
### Approach - Binary Search
Based on the definition, the total number of elements is odd and the last index is an even number with zero-based indexing. The target number (appears exactly once) can only appear in even indices, e.g., `nums[0]`, `nums[2]`, ..., `nums[2*n]`. We can search array in paris, i.e., numbers with index `[2 * i, 2 * i - 1]`. For any given pair,

- If elements in a pair are the same, the single element is on the right half of the array
- Otherwise, the single element is either in the current pair or on the left half of the array

With this property, we can use binary search to speed up the search. The search space is the index of pairs, `[0, n/2]`. We want to find the first even-index number not followed by the same number. 

???+ note
    The last pair of `n/2` only has one element. In the code, use while condition `left < right` to prevent out-of-bound access using `nums[2 * mid + 1]`. When it reaches the last pair, `left == right`, it will jump out of the while loop

=== "Python"
    ```python
    class Solution:
        def singleNonDuplicate(self, nums: List[int]) -> int:
            left, right = 0, len(nums) // 2

            while left < right:
                mid = (left + right) // 2

                if nums[2 * mid] == nums[2 * mid + 1]:
                    left = mid + 1
                else:
                    right = mid

            return nums[2 * left]
    ```

#### Complexity Analysis
* Time complexity: $O(\log n)$ 
Since using binary search, the time complexity is $O(\log n)$.
* Space complexity: $O(1)$  
Only limited variables.

## Test
- Empty array
- Array with 1 element