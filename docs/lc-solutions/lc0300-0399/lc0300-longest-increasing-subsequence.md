---
tags:
- Dynamic Programming
- Binary Search
---

# LC300. Longest Increasing Subsequence

## Problem Description

[LeetCode Problem 300](https://leetcode.com/problems/longest-increasing-subsequence): Given an integer array `nums`, return _the length of the longest **strictly increasing subsequence**.

## Clarification

- strictly increasing? > not >=
- is it continuous subsequence?

## Assumption

## Solution

### Approach - Dynamic Programming

Let `dp[i]` be the length of the longest increase subsequence of `nums[0], nums[1], ..., nums[i]` which has `nums[i]` as the end element of the subsequence. `dp[i]` will be initialized to 1 since we can always pick a single element for the sequence.

=== "Python"
    ```python
    class Solution:
        def lengthOfLIS(self, nums: List[int]) -> int:
            n = len(nums)
            dp = [1] * n
            for i in range(n):
                for j in range(i):
                    if nums[i] > nums[j] and dp[i] < dp[j] + 1:
                        dp[i] = dp[j] + 1
            return max(dp)
    ```

#### Complexity Analysis

- Time complexity: $O(n^2)$  
Use two nested for-loops.

- Space complexity: $O(n)$  
`dp` array to store values.

### Approach - Binary Search

[@hiepit](https://leetcode.com/problems/longest-increasing-subsequence/solutions/1326308/c-python-dp-binary-search-bit-segment-tree-solutions-picture-explain-o-nlogn/?envType=study-plan-v2&envId=binary-search) provides a good explanations. He also mention [another useful document](https://www.cs.princeton.edu/courses/archive/spring13/cos423/lectures/LongestIncreasingSubsequence.pdf) for better understanding.

=== "Python"
    ```python
    class Solution:
        def lengthOfLIS(self, nums: List[int]) -> int:
            sub = []
            for x in nums:
                if len(sub) == 0 or sub[-1] < x:
                    sub.append(x)
                else:
                    idx = bisect_left(sub, x)  # Find the index of the first element >= x
                    sub[idx] = x  # Replace that number with x
            return len(sub)
    ```

#### Complexity Analysis

- Time complexity: $O(n \log n)$  
Go through the whole array and use binary search for each step.

- Space complexity: $O(n)$  
Need space to store sub array.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different approaches:

Approach   | Time Complexity  | Space Complexity  
------------ | ---------------  | ----------------
Approach - a |  $O(n^2)$          | $O(n)$  
Approach - Binary Search |  $O(n \log n)$        | $O(1)$

## Test
