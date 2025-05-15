---
tags:
    - Dynamic Programming
---

# 746. Min Cost Climbing Stairs

## Problem Description

[LeetCode Problem 746](https://leetcode.com/problems/min-cost-climbing-stairs/description/):
You are given an integer array `cost` where `cost[i]` is the cost of `ith` step on a
staircase. Once you pay the cost, you can either climb one or two steps.

You can either start from the step with index `0`, or the step with index `1`.

Return _the minimum cost to reach the top of the floor_.

## Clarification

- The top of the floor is **one more step** after the last step in the array.
- Each step cost differently.
- Either climb 1 or 2 steps at a time.

## Assumption

-

## Solution

We can solve the problem using dynamic programming. The idea is to keep track of the
minimum cost to reach each step and use the relationship between steps to determine the
minimum cost to reach the top.

- Define **state**, $\text{min_cost}(i)$ the minimum cost of **reaching** `ith` step
- Find **recurrence relation**. There are two ways to reach `ith` step
    - climb 1 step from `(i-1)th` step, $\text{min_cost}(i - 1) + \text{cost}(i - 1)$
    - climb 2 steps from `(i-2)th` step, $\text{min_cost}(i - 2) + \text{cost}(i - 2)$
    - Then the recurrent relation equation is

    $$\text{min_cost}(i) = \min(\text{min_cost}(i - 1) + \text{cost}(i - 1), \text{min_cost}(i - 2) + \text{cost}(i - 2)) $$

- **Base case**: $\text{min_cost}(0) = 0$, $\text{min_cost}(1) = 0$ since either start
from the step 0 or step 1.

Note that the top of the floor is one more step after the last step in the array.

### Approach 1: Iteration

We can use iterative method to implement dynamic programming solution.

=== "Python"
    ```python
    class Solution:
        def minCostClimbingStairs(self, cost: List[int]) -> int:
            n = len(cost)
            if n < 2:
                return 0

            min_prev1 = 0
            min_prev2 = 0

            for i in range(2, n + 1):
                min_curr = min(min_prev1 + cost[i - 1], min_prev2 + cost[i - 2])
                min_prev1, min_prev2 = min_curr, min_prev1

            return min_prev1
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  We use for-loop to iterate over the array of size $n$ and each iteration takes
  constant time. So the total time complexity is $O(n)$.
- Space complexity: $O(1)$  
  Use two variables to store the minimum cost for the previous two steps. So the
  total space complexity is $O(1)$.

### Approach 2: Recursion + Memoization

We can also solve this problem using recursion with memoization based on the recurrence
relation. During recursion, there are many repeat computations. So we store the results
in a memo dictionary.

=== "python"
    ```python
    class Solution:
        def minCostClimbingStairs(self, cost: List[int]) -> int:
            self.memo = {}
            return self.min_cost(cost, len(cost))

        def min_cost(self, cost: List[int], idx: int) -> int:
            if idx < 2:
                return 0

            if idx in self.memo:
                return self.memo[idx]

            min_prev1 = self.min_cost(cost, idx - 1)
            min_prev2 = self.min_cost(cost, idx - 2)
            min_curr = min(min_prev1 + cost[idx - 1], min_prev2 + cost[idx - 2])
            self.memo[idx] = min_curr

            return min_curr
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  Each step is visited once and each visit takes constant time. So the total time
  complexity is $O(n)$.
- Space complexity: $O(n)$  
    - The memo dictionary takes $O(n)$ space to store the results.
    - The recursion stack takes $O(n)$ space since the maximum depth of the recursion is
    $n$.
    - So the total space complexity is $O(n)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Iteration | $O(n)$          | $O(1)$
Approach - Recursion + Memoization| $O(n)$          | $O(n)$

## Test

- Test array with 1 element
- Test array with 2 elements
- Test array with multiple elements and different costs
