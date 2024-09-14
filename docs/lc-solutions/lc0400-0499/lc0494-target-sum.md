---
tags:
    - Breadth-First Search
---

# LC494. Target Sum

## Problem Description

[LeetCode Problem 494](https://leetcode.com/problems/target-sum/description/): You are given an integer array `nums` and an integer `target`.

You want to build an **expression** out of nums by adding one of the symbols `'+'` and `'-'` before each integer in nums and then concatenate all the integers.

- For example, if `nums = [2, 1]`, you can add a `'+'` before `2` and a `'-'` before `1`and concatenate them to build the expression `"+2-1"`.

Return the number of different **expressions** that you can build, which evaluates to `target`.

## Clarification

-

## Assumption

-

## Solution

### Approach 1 - Brutal Force

Recursively calling the find function until reach the end of array. It will return `1` if `sum == target` or 0 otherwise in the end. At each node, return values from function calls of `+` and `-` elements will be added.

A small **trick**: instead of add an argument of `sum`, send `remain_target` by adding or subtracting values from `target` in each recursive function call.

=== "Python"
    ```python
    class Solution:
        def findTargetSumWays(self, nums: List[int], target: int) -> int:
            return self.find(nums, 0, target)

        def find(self, nums: List[int], depth: int, remain_target: int) -> int:
            if depth == len(nums):
                return remain_target == 0

            return self.find(nums, depth + 1, remain_target + nums[depth]) \
                + self.find(nums, depth + 1, remain_target - nums[depth])
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(2^n)$  
  Each recursive call will leads **two** sub-recursive call. Since the recursive call depth is $n$ (number of array elements), so the time complexity is $O(2^n)$.
- Space complexity: $O(n)$  
  The function recursive call stack with the depth of $n$.

### Approach 2 - Memoization

In the brutal force method, there are many redundant functional call during the recursion for the same `(indx, sum)` pair. These values can be stored and re-used.

=== "python"
    ```python
    class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        mem = {}
        return self.find(nums, 0, target, mem)

    def find(self, nums: List[int], depth: int, remain_target: int, mem: dict[int, int]) -> int:
        if depth == len(nums):
            return remain_target == 0

        if (depth, remain_target) in mem:
            return mem[(depth, remain_target)]

        mem[(depth, remain_target)] = self.find(nums, depth + 1, remain_target + nums[depth], mem) \
            + self.find(nums, depth + 1, remain_target - nums[depth], mem)

        return mem[(depth, remain_target)]
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n \times \text{sum}(\text{nums}))$  
  Each state `(index, sum)` is computed only once. The number of unique states is proportional to $O($n \times \text{sum}(\text{nums}))$, where `n` is the length of `nums` and `sum(nums)` is the maximum possible absolute sum.
- Space complexity: $O(n \times \text{sum}(\text{nums}))$  
  The total space complexity is combination of memoization table and recursion stack space, $O(n \times \text{sum}(\text{nums})) + O(n) = O(n \times \text{sum}(\text{nums}))$.  
  
    - Recursion stack space due to recursion function call of depth $n$, which requires $O(n)$ space
    - Memoization table: stores results of each pair `(index, sum)` where `index` ranges from `0` to `n` with $n + 1$ possible values and `sum` ranges from $-\text{sum}(\text{nums})$ to $\text{sum}(\text{nums}) with $2 \times \text{sum}(\text{nums}) + 1$ possible values. 

  

### Approach 3 - DP

The problem can be solved using bottom-up (iterative) dynamic programming. Each step is to compute the number of ways to achieve new sum based on `sum_so_far` and `count` in previous step. A list of dictionaries, `dp`, is introduced. `dp[i]` keeps track of number of ways to achiever different sums using the first `i` numbers of the `nums` array.

Note that, the DP array has aa size of `n + 1` instead of `n` to account for the base case where no elements from the `nums` array have been processed yet (i.e., the "0-th" step).

- `dp[i]` represents the possible sums you can get by using the first `i` numbers of `nums`.
- `dp[0]` represents the base case before processing any numbers. `dp[0][0] = 1` indicates there is exactly **1 way** to have a sum of `0` before processing any numbers.

=== "Python"
    ```python
    class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        # dp[i] stores the number of ways to make a sum with the first i elements
        dp = [{} for _ in range(n + 1)]
        dp[0][0] = 1  # there is one way to get sum of 0 using 0 element

        for i in range(n):
            for sum_so_far, count in dp[i].items():
                if sum_so_far + nums[i] not in dp[i+1]:
                    dp[i+1][sum_so_far + nums[i]] = 0
                if sum_so_far - nums[i] not in dp[i+1]:
                    dp[i+1][sum_so_far - nums[i]] = 0

                dp[i+1][sum_so_far + nums[i]] += count
                dp[i+1][sum_so_far - nums[i]] += count

        if target in dp[n]:
            return dp[n][target]
        else:
            return 0
    ```

#### Complexity Analysis of Approach 3

- Time complexity: $O(n \times \text{sum}(\text{nums}))$  
  - Outer loop: we iterate through each element in `nums`, so the outer loop runs $n$ times.
  - Inner loop: at each step `i`, go through every possible sums that can be achieved using the first `i` elements. The number of possible sums at step `i` is constrained by $-\text{sum}(\text{nums})$ and $+\text{sum}(\text{nums})$ and up to $2 \times \text{sum}(\text{nums}) + 1$. So the total time complexity is $O(n \times (2 \times \text{sum}(\text{nums}))) = O(n \times \text{sum}(\text{nums}))$.
- Space complexity: $O(n \times \text{sum}(\text{nums}))$  
  We define a list of hashmaps `dp` with size of $n + 1$. Each `dp[i]` is a dictionary that can store up to $2 \times \text{sum}(\text{nums}) + 1$.

### Approach 4 - DP with Linear Space

In the DP approach, we only need to use the results for the current and previous states. The space can be optimized to use only two such dictionaries instead of the full list.

=== "Python"
    ```python
    class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        # dp stores the number of ways to make a sum with the first i elements in previous step i
        dp_prev = {} 
        dp_prev[0] = 1 # base case: there is one way to get sum of 0 using 0 element 

        for i in range(n):
            dp_curr = {}
            for sum_so_far, count in dp_prev.items():
                if sum_so_far + nums[i] not in dp_curr:
                    dp_curr[sum_so_far + nums[i]] = 0
                if sum_so_far - nums[i] not in dp_curr:
                    dp_curr[sum_so_far - nums[i]] = 0

                dp_curr[sum_so_far + nums[i]] += count
                dp_curr[sum_so_far - nums[i]] += count

            dp_prev = dp_curr.copy()

        if target in dp_curr:
            return dp_curr[target]
        else:
            return 0
    ```

#### Complexity Analysis of Approach 4

- Time complexity: $O(n \times \text{sum}(\text{nums}))$  
  See previous analysis of DP approach.
- Space complexity: $O(\text{sum}(\text{nums}))$  
  The previous or current dictionary stores at most $2 \times \text{sum}(\text{nums}) + 1$ entries. So the space complexity is $O(2 \times \text{sum}(\text{nums}) + 1) = O(\text{sum}(\text{nums})$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach 1 -  |  $O(2^n)$           | $O(n)$  |
Approach 2 -  |  $O(n \times \text{sum}(\text{nums}))$           | $O(n \times \text{sum}(\text{nums}))$  |
Approach 3 -  |  $O(n \times \text{sum}(\text{nums}))$           | $O(n \times \text{sum}(\text{nums}))$  |
Approach 4 -  |  $O(n \times \text{sum}(\text{nums}))$           | $O(\text{sum}(\text{nums}))$  |

## Test
