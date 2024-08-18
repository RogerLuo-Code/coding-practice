---
tags:
- Dynamic Programming
- Binary Search
---

# LC1235. Maximum Profit in Job Scheduling
## Problem Description
[LeetCode Problem 1235](https://leetcode.com/problems/maximum-profit-in-job-scheduling): We have `n` jobs, where every job is scheduled to be done from `startTime[i]` to `endTime[i]`, obtaining a profit of `profit[i]`.

You're given the `startTime`, `endTime` and `profit` arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.

If you choose a job that ends at time `X` you will be able to start another job that starts at time `X`.

## Clarification

## Assumption

## Solution
### Approach - Dynamic Programming + Binary Search
First, sort the job by `endTime`. Then solve it using dynamic programming, where `dp[endTime] = profit` is the profit within the `endTime`, induction rule is
- Don't do the job, profit won't be changed.
- Do this job, binary search in the dp to find the largest profit before start time `s`, `dp[endTimeBeforeStart]`. Then `dp[endTime] = max(dp[prevEndTime], dp[endTimeBeforeStart]`.

The base case is `dp[0] = 0` as we make 0 profit at `time = 0`.

=== "Python"
    ```python
    class Solution:
        def jobScheduling(self, startTime: List[int], endTime: List[int], profit: List[int]) -> int:
            jobs = sorted(zip(startTime, endTime, profit), key=lambda v: v[1])  # sorted by endTime
            dp = [[0, 0]]
            for s, e, p in jobs:
                i = bisect.bisect(dp, [s + 1]) - 1  # (1)
                if dp[i][1] + p > dp[-1][1]:
                    dp.append([e, dp[i][1] + p])
            return dp[-1][1]
    ```

    1. `s+1` for search dp[i][0] >= s + 1, `-1` from search result to return `dp[i][0] <= s`

#### Complexity Analysis
* Time complexity: $O(n \log n)$  
The sorting takes $O(n \log n)$ and binary search of each job takes another $O(n \log n)$.
* Space complexity: $O(n)$  
The sorting takes $O(n)$ and `dp` also takes $O(n)$.

## Test