---
tags:
    - Dynamic Programming
---

# 198. House Robber

## Problem Description

[LeetCode Problem 198](https://leetcode.com/problems/house-robber/description/):
You are a professional robber planning to rob houses along a street. Each house has a
certain amount of money stashed, the only constraint stopping you from robbing each of
them is that adjacent houses have security systems connected and
**it will automatically contact the police if two adjacent houses were broken into on
the same night**.

Given an integer array `nums` representing the amount of money of each house, return
_the maximum amount of money you can rob tonight **without alerting the police**_.

**Example 1:**

**Input:** nums = [1,2,3,1]  
**Output:** 4  
**Explanation:** Rob house 1 (money = 1) and then rob house 3 (money = 3).  
Total amount you can rob = 1 + 3 = 4.

**Example 2:**

**Input:** nums = [2,7,9,3,1]  
**Output:** 12  
**Explanation:** Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).  
Total amount you can rob = 2 + 9 + 1 = 12.

## Clarification

- No two adjacent houses can be robbed

## Assumption

-

## Solution

To solve the problem, we need to figure out:

1. Define **state** of the problem using a function or array. We can use `rob(i)` to
represent the maximum amount of money at house `i`.
2. Find **recurrence relation** to transit between states. For house `i`, a robber has
2 options:
    1. Rob the house. It means it can't rob the house before (i.e., house `i - 1`).
    He gets all cumulative money from house `i - 2` and the money from house `i`.
    2. Do not rob the house. He gets all cumulative money from house `i - 1`.
    So we can represent the above mentioned relation in the following equation:

    $$
    \text{rob}(i) = \max(\text{rob}(i - 2) + \text{nums}[i], \text{rob}(i - 1))
    $$

3. Determine **base cases** to stop recurrence relation:
    - $\text{rob}(0) = \text{nums}[0]$
    - $\text{rob}(1) = \max(\text{nums}[0], \text{nums}[1])$


### Approach 1: Recursive + Memoization

Based on the relationship, we can use recursive method with memoization to calculate
the max amount of money for each house.

=== "Python"
    ```python
    class Solution:
    def rob(self, nums: List[int]) -> int:
        self.memo = {}
        return self.rob_i(nums, len(nums) - 1)

    def rob_i(self, nums: List[int], i: int) -> int:
        # Base case
        if i < 0:
            return 0

        # Memoization
        if i in self.memo:
            return self.memo[i]

        max_prev1 = self.rob_i(nums, i - 1)
        max_prev2 = self.rob_i(nums, i - 2)

        max_current = max(max_prev1, max_prev2 + nums[i])
        self.memo[i] = max_current  # Update memo
        return max_current
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  The recursive calls take at most $n$ times due to memoization and each call takes
  $O(1)$ time. So the time complexity is $O(n)$.
- Space complexity: $O(n)$  
    - The memoization table takes $O(n)$ space to store max amount of money for each house.
    - The recursion stack takes $O(n)$ space since the recursion depth is at most $n$.
    - The total space complexity is $O(n) + O(n) = O(n)$.

### Approach 2: Iteration

From the relationship equation, to calculate the maximum amount of money of the current
house, we only need to know the maximum amount of money of the **previous two** houses.
So we can use iteration to calculate the maximum amount of money for each house by using
two variables `prev1` and `prev2` (no need to use an array).

=== "python"
    ```python
    class Solution:
        def rob(self, nums: List[int]) -> int:
            n = len(nums)
            if n == 0:
                return 0
            prev1 = 0
            prev2 = 0
            for num in nums:
                curr = max(prev1, prev2 + num)
                prev1, prev2 = curr, prev1

            return curr
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  Go through $n$ numbers using a for-loop and each iteration takes $O(1)$ time.
  So the time complexity is $O(n)$.
- Space complexity: $O(1)$  
  Use 3 variables, `prev1`, `prev2`, and `curr`, to do the calculations. So the space
  complexity is $O(1)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach 1 - Recursion + Memoization | $O(n)$          | $O(n)$
Approach 2 - Iteration | $O(n)$          | $O(1)$

## Test

- Test empty list
- Test single house
- Test two houses
- Test multiple houses
