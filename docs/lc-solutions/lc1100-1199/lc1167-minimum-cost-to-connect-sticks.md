---
tags:
    - Heap
---

# LC1167. Minimum Cost to Connect Sticks

## Problem Description

[LeetCode Problem 1167](https://leetcode.com/problems/minimum-cost-to-connect-sticks/description/):
You have some number of sticks with positive integer lengths. These lengths are given as
an array `sticks`, where `sticks[i]` is the length of the `ith` stick.

You can connect any two sticks of lengths `x` and `y` into one stick by paying a cost of
`x + y`. You must connect all the sticks until there is only one stick remaining.

Return _the minimum cost of connecting all the given sticks into one stick in this way_.

## Clarification

- Connect any two sticks. Two sticks are connected become a new one.
- Connect all sticks include the new ones connected in previous steps

## Assumption

- The input can be modified.

## Solution

### Approach - Heap

We can use min heap to store sticks. Always pick two of the smallest sticks to connect
and put the new one back to the heap. Continue doing this until only one stick left.

???+ question "Why Pick Two of the Smallest Sticks?"
    Let's start with a simple example of 4 sticks
    $\text{sticks} = [a_1,\, a_2,\, a_3,\, a_4]$ and go through it by its original order:

    1. After first merge, $\text{sticks} = [(a_1 + a_2),\, a_3,\, a_4]$,
    $\text{cost} = (a_1 + a_2)$.
    2. After 2nd merge, $\text{sticks} = [(a_1 + a_2 + a_3),\, a_4]$,
    $\text{cost} = (a_1 + a_2) + (a_1 + a_2 + a_3)$.
    3. Finally, $\text{sticks} = [(a_1 + a_2 + a_3 + a_4)]$,
    $\text{cost} = (a_1 + a_2) + (a_1 + a_2 + a_3) + (a_1 + a_2 + a_3 + a_4)$.

    The final cost can be re-written as: $\text{cost} = 3 a_1 + 3 a_2 + 2 a_3 + a_4$.
    From the final cost, the sticks which are connected first appear more times in the
    final cost. Therefore, it is optimal to pick smaller sticks first to get the
    smallest cost.

=== "Python"
    ```python
    import heapq

    class Solution:
        def connectSticks(self, sticks: List[int]) -> int:
            min_cost = 0
            heapq.heapify(sticks)
            # Connect two sticks using min heap
            while len(sticks) > 1:
                cost = heapq.heappop(sticks) + heapq.heappop(sticks)
                heapq.heappush(sticks, cost)
                min_cost += cost

            return min_cost
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n \log n)$  
    - `heapify` the array takes $O(n)$ time.
    - Iterate the array $n$ times and each iteration takes 3 heap operations. Each heap
    operation takes $O(\log s)$, where $s$ is the heap size, decreasing from $n$,
    $n - 1$, $\cdots$, $1$ after each iteration. So the time complexity to iterate heap is
    $O(\log n) + O(\log (n - 1)) + \cdots + O(log 2) \approx O(n \log n)$.
    - So the total time complexity is $O(n) + O(n \log n) = O(n \log n)$.
- Space complexity: $O(n)$  
    The heap stores $n$ elements.

## Test
