---
tags:
    - Dynamic Programming
---

# 740. Delete And Earn

## Problem Description

[LeetCode Problem 740](https://leetcode.com/problems/delete-and-earn/description/):
You are given an integer array `nums`. You want to maximize the number of points you get
by performing the following operation any number of times:

- Pick any `nums[i]` and delete it to earn
`nums[i]` points. Afterwards, you must delete **every** element equal to `nums[i] - 1`
and **every** element equal to `nums[i] + 1`.

Return _the **maximum number of points** you can earn by applying the above operation
some number of times_.

## Clarification

-

## Assumption

-

## Solution

This problem can be solved using dynamic programming. It's really tricky to break down
the problem.

- **State**: `max_points[num]`, the max points collected when at a given `num`.
- **Recurrence relation**: sorted the array and go through `num` in order,
    - Choose it indicates we can't take points from `num - 1` and have to use points from `num - 2`. So it is `max_points[num - 2] + num`.
    - Skip it indicates it is the same as `max_points[num - 1]`
    - After the array sorted, no need to check `num + 1` since it will be evaluated later.
- **Base case**:
    - max_points[0] = 0
    - max_points[1] = nums[1] * occurence(nums[1])

### Approach 1: Iteration

Once figuring out the recurrence relation, we can use iteration method to solve it.

=== "Python"
    ```python
    from collections import Counter

    class Solution:

        def deleteAndEarn(self, nums: List[int]) -> int:
            points = Counter(nums)
            prev1 = 0
            prev2 = 0

            # Go through number from 0 to max(nums) in order (some of them may not exist in numbers)
            for value in range(max(points.keys()) + 1):
                curr = max(prev2 + value * points[value], prev1)  # points[value] return 0 if value doesn't exist
                prev1, prev2 = curr, prev1

            return curr
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n + m)$ where $n$ is the length of `nums` and $m$ is the max element in `nums`,
    - `Counter` takes $O(n)$ time since iterates over all $n$ elements in `nums`
    - The `for` loop iterates over all possible values of `num` from 0 to `max(nums)`
    and each iteration takes $O(1)$ time. So the whole for-loop takes $O(m)$ time.
    - So the total time complexity is $O(n + m)$.
- Space complexity: $O(n)$  
    - We use a dictionary `points` to store the points for each number in `nums`, which takes $O(n)$ space.
    - The 3 variables `prev1`, `prev2`, and `curr` used in for-loop take $O(1)$ space.
    - So the total space complexity is $O(n)$.

### Approach 2: Recursion

The problem can be solved using recursion.

=== "python"
    ```python
    from collections import Counter


    class Solution:
        def deleteAndEarn(self, nums: List[int]) -> int:
            self.cache = {}
            points = Counter(nums)
            max_number = max(points.keys())
            return self.max_points(points, max_number)

        def max_points(self, points: dict[int, int], num: int) -> int:
            # Base case
            if num == 0:
                return 0
            if num == 1:
                return points[1] * 1

            if num in self.cache:
                return self.cache[num]

            # Apply recurrence relation
            self.cache[num] = max(
                self.max_points(points, num - 1),
                self.max_points(points, num - 2) + points[num] * num,
            )
            return self.cache[num]
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n + m)$
    - `Counter` takes $O(n)$ time since iterates over all $n$ elements in `nums`
    - The recursive function call starts from `max(nums)` and down to base case 0.
    Each function call takes $O(1)$ time. So it takes $O(m)$ time.
    - So the total time complexity is $O(n + m)$.
- Space complexity: $O(n + m)$  
    - We use a dictionary `points` to store the points for each number in `nums`, which takes $O(n)$ space.
    - The recursion call stack will grow up to  `max(nums)`, which takes $O(m)$ space.
    - so the total space complexity is $O(n + m)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach 1 - Iteration | $O(n + m)$          | $O(n)$
Approach 2 - Recursion | $O(n + m)$          | $O(n + m)$

## Test

- Test inputs with just one element
- Test inputs with multiple elements and duplicates
