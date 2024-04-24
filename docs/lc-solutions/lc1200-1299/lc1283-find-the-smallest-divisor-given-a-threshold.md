---
tags:
- Binary Search
---

# LC1283. Find the Smallest Divisor Given a Threshold
## Problem Description
[LeetCode Problem 1283](https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold): Given an array of integers `nums` and an integer `threshold`, we will choose a positive integer `divisor`, divide all the array by it, and sum the division's result. Find the **smallest** `divisor` such that the result mentioned above is less than or equal to `threshold`.

Each result of the division is rounded to the nearest integer greater than or equal to that element. (For example: `7/3 = 3` and `10/2 = 5`).

The test cases are generated so that there will be an answer.

## Clarification
- samllest divisor
- nearest integer greater than or equal to that element

## Assumption
- Positive numbers

## Solution
### Approach - Binary Search
If increasing divisor, sum of division decreases. We can use binary search to quickly find the divisor.

- If sum of division > threshold, it is true for all divisor < current divisor. So increase divisor to search the right part of the current divisor
- Otherwise, reduce divisor and search the left part of the current divisor

???+ note
    For integer ceiling division, we can simply add `division - 1` to the numerator, i.e., `(num + division - 1) // division`.

=== "Python"
```python
class Solution:
    def smallestDivisor(self, nums: List[int], threshold: int) -> int:
        left, right = 1, max(nums)

        while left < right:
            mid = (left + right) // 2
            division_sum = self.sumOfDivision(nums, mid)
            if division_sum <= threshold:
                right = mid
            else:
                left = mid + 1

        return left

    def sumOfDivision(self, nums: List[int], division: int) -> int:
        division_sum = 0
        for num in nums:
            division_sum += (num + division - 1) // division

        return division_sum
```

#### Complexity Analysis
* Time complexity: $O(n \log m)$, where $n$ is the number of elements and $m$ is the maximum element of the array  
    - Every time reduce the search space of possible divisors by half, $m \rightarrow m/2 \rightarrow m/4 \rightarrow \cdots \rightarrow 1$. The are $\log m$ iterations.
    - For each divisor, we iterate on the whole array to find the sum of division, which takes $O(n)$ time
    - Thus, for $\log m$ divisors, overall it takes $O(n \log m)$ time
* Space complexity: $O(1)$  
Only several variables.

## Test