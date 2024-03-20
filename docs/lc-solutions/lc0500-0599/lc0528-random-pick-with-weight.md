---
tags:
- Prefix Sum
- Binary Search
---

# LC528. Random Pick with Weight
## Problem Description
[LeetCode Problem 528](https://leetcode.com/problems/random-pick-with-weight): You are given a **0-indexed** array of positive integers `w` where `w[i]` describes the **weight** of the `ith` index.

You need to implement the function `pickIndex()`, which **randomly** picks an index in the range `[0, w.length - 1]` (**inclusive**) and returns it. The **probability** of picking an index `i` is `w[i] / sum(w)`.

- For example, if `w = [1, 3]`, the probability of picking index `0` is `1 / (1 + 3) = 0.25` (i.e., `25%`), and the probability of picking index `1` is `3 / (1 + 3) = 0.75` (i.e., `75%`).

## Clarification
- positive integer
- return the index?
- Ensure returned index meets the probability of picking

## Assumption

## Solution
### Approach - Prefix Sum + Binary Search
After converting array to cumulative sum array, the width of each range represents the original value. The larger the original value is, the wider range is. For wider range, the random pick will falls into that range with higher probability.

=== "Python"
    ```python
    import random


    class Solution:

        def __init__(self, w: List[int]):
            self.w_cusum = w
            for i in range(1, len(w)):
                self.w_cusum[i] = self.w_cusum[i - 1] + w[i]

        def pickIndex(self) -> int:
            rand_val = random.randint(1, self.w_cusum[-1])  # inclusive on two ends

            left, right = 0, len(self.w_cusum) - 1
            while left < right:
                mid = (left + right) // 2
                if self.w_cusum[mid] == rand_val:
                    return mid
                elif self.w_cusum[mid] < rand_val:
                    left = mid + 1
                else:
                    right = mid

            return left
    ```

#### Complexity Analysis
* Time complexity: $O(n)$ for `init`, $O(\log n)$ for `pickIndex`  
In `init` function, it takes $O(n)$ to compute cumulative summation. In `pickIndex`, it uses binary search to find target index. So the time complexity is $O(\log n)$.
* Space complexity: $O(n)$  
Storing cumulative sum array using $O(n)$ space.

## Test