---
tags:
- Binary Search
---

# LC410. Split Array Largest Sum
## Problem Description
[LeetCode Problem 410](https://leetcode.com/problems/split-array-largest-sum): Given an integer array `nums` and an integer `k`, split `nums` into `k` non-empty subarrays such that the largest sum of any subarray is **minimized**.

Return _the minimized largest sum of the split_.

A **subarray** is a contiguous part of the array.

## Clarification
- split `nums` into `k` subarrays
- subarray is not empty and a contiguous part
- the largest sum is minimized. what does it mean?

## Assumption

## Solution
### Approach - Binary Search
The problem can be considered as searching the  minimum largest subarray sum, that can split the array at most `k` subarrays. For a given minimum largest subarray sum, `m`,

- If the array can be split into `k` or fewer subarrays, there could be a potential solution. For fewer subarrays, we can always split them to increase the count. 
- If the array can be split more than `k` subarrays, it means `m` value is too small.

Based on these properties, we can use binary search. The search space is between maximum value of the array and sum of the array.

=== "Python"
    ```python
    class Solution:
        def splitArray(self, nums: List[int], k: int) -> int:
            ans = -1
            low, high = max(nums), sum(nums)
            while low <= high:
                mid = (low + high) // 2
                if self.is_valid(nums, k, mid):  # (1)
                    ans = mid
                    high = mid - 1
                else:
                    low = mid + 1
            return ans

        def is_valid(self, nums: List[int], k: int, max_sum_allowed: int):
            n_splits, curr_sum = 0, 0
            for num in nums:
                if curr_sum + num <= max_sum_allowed:
                    curr_sum += num
                else:
                    n_splits += 1  # (2)
                    curr_sum = num
            n_subarray = n_splits + 1  # (3)
            return n_subarray <= k
    ```

    1. Can cut into `m` sub-arrays with maximum sum of `mid`
    2. Increase the number of splits
    3. Number of subarrays is the number of splits + 1

#### Complexity Analysis
* Time complexity: $O(n \log s)$ where $n$ is the array length and $s$ is the array sum.  
The binary search space is $s$, which takes $O(\log s)$ time. During each iteration, it takes $O(n)$ time to compute number of subarrays. So the total time complexity is $O(n \log s)$.
* Space complexity: $O(1)$  
Just limited number of variables. Therefore, constant extra space. 

## Test