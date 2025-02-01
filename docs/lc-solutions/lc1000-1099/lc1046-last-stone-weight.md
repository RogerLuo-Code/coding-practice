---
tags:
    - Heap
---

# LC1046. Last Stone Weight

## Problem Description

[LeetCode Problem 1046](https://leetcode.com/problems/last-stone-weight/description/):
You are given an array of integers `stones` where `stones[i]` is the weight of the `ith` stone.

We are playing a game with the stones. On each turn, we choose the
**heaviest two stones** and smash them together. Suppose the heaviest two stones have
weights `x` and `y` with `x <= y`. The result of this smash is:

- If `x == y`, both stones are destroyed, and
- If `x != y`, the stone of weight `x` is destroyed, and the stone of weight `y` has new
weight `y - x`.

At the end of the game, there is **at most one** stone left.

Return _the weight of the last remaining stone_. If there are no stones left, return `0`.

## Clarification

- Choose the two heaviest stones
- Can the input be modified?

## Assumption

-

## Solution

### Approach - Heap

Use Max Heap to heapify the stones array and pop up two stones at a time to smash until
only one stone left:

- if two stones equal, continue
- if two stones different, push the diff to the max heap

Return stone if max heap has one stone otherwise 0

=== "Python"
    ```python
    import heapq


    class Solution:
        def lastStoneWeight(self, stones: List[int]) -> int:
            stones_negative = [-1 * w for w in stones]
            heapq.heapify(stones_negative)  # (1)

            # Smash two stones at a time until there is one or no stone left
            while len(stones_negative) > 1:
                weight_a = heapq.heappop(stones_negative)
                weight_b = heapq.heappop(stones_negative)
                if weight_a != weight_b:
                    heapq.heappush(stones_negative, weight_a - weight_b)  # (2)

            return -heapq.heappop(stones_negative) if len(stones_negative) > 0 else 0  # (3)
    ```

    1. Since python implements min heap, store negative weights to achieve max heap.
    2. `weight_a - weight_b` is negative since `weight_a < weight_b` based on sequence of
    popping from min heap.
    3. Convert the negative weight back to normal.

#### Complexity Analysis of Approach 1

- Time complexity: $O(1)$  
    - Heapifying the array takes $O(n)$ time.
    - It will iterating total $n$ stones. Each iteration will perform at most 3 heap
    operations. The heap operation takes $\log s$ where $s$ is the heap size. The heap
    size is reduced by one from $n$ to $1$ after each iteration. So the time complexity
    is $O(\log n) + O(\log (n - 1)) + \cdots + O(\log 1) \approx O(n \log n - n + 1) =
    O(n \log n)$.
    - So the total time complexity is $O(n) + O(n \log n) = O(n \log n)$.
- Space complexity: $O(n)$  
    - Define a new array takes $O(n)$.
    - The heap initially takes $O(n)$ space and becomes 0 in the end.
    - So the total space complexity is $O(n) + O(n) = O(n)$.

???+ "How to evaluate $\log n!$"
    From the definition of factorial, we know $\log n! = \log (1 \times 2 \times \cdots
    \times n) = \log 1 + \log 2 + \cdots + \log n = \sum_{k = 1}^n \log k$.

    Approximating the sum as an integral: $\sum_{k = 1}^n \log k \approx \int_1^n \log x
    \mathop{dx}$

    Computing the integral by using integration by parts: $\int \log x \mathop{dx} = x
    \log x - \int x \mathop{d \log x} = x
    \log x - \int x \frac{\mathop{d \ln x}}{\ln 10} = x \log x - \int x \frac{1}{x}
    \frac{1}{\ln 10} \mathop{dx} = x \log x - \frac{x}{\ln 10}$

    So $\sum_{k = 1}^n \log k \approx \int_1^n \log x \mathop{dx} = (n \log n -
    \frac{n}{\ln 10}) - (1 \log 1 - \frac{1}{\ln 10}) = n \log n - \frac{n - 1}{\ln 10}
    \approx n \log n$.

## Test
