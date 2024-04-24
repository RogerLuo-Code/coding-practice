---
tags:
- Binary Search
---

# LC1231. Divide Chocolate
## Problem Description
[LeetCode Problem 1231](https://leetcode.com/problems/divide-chocolate): You have one chocolate bar that consists of some chunks. Each chunk has its own sweetness given by the array `sweetness`.

You want to share the chocolate with your `k` friends so you start cutting the chocolate bar into `k + 1` pieces using `k` cuts, each piece consists of some **consecutive** chunks.

Being generous, you will eat the piece with the **minimum total sweetness** and give the other pieces to your friends.

Find the **maximum total sweetness** of the piece you can get by cutting the chocolate bar optimally.

## Clarification
- Sweetness is random or sorted?
- `k` cuts -> `k + 1` pieces, one for you, and the other k for friends

## Assumption

## Solution
### Approach - Binary Search
We always receive the piece with the **minimum total sweetness**. THe problem is to maximize the sweetness of the piece that we take (Note: it is still minimum sweetness compared to other pieces to our friends.).

Re-phrase in mathematical terms: the chocolate bar is represented by a non-zero integer array and the sum of a contiguous subarray stands for the sweetness of a piece. The task is to find the maximum possible minimum sum of all subarrays after dividing the array into `k + 1` contiguous subarrays with `k` cuts.

Similar to the idea used in [LC410 split array largest sum](../lc0400-0499/lc0410-split-array-largest-sum.md), we can search for minimum sweetness to cut chocolate bar. For a given minimum sweetness,

- If number of pieces `>= k + 1`, increase the minimum sweetness
- Otherwise, some friends can't get a piece of chocolate, need to decrease the minimum sweetness

Based on above mentioned properties, we can use binary search to find the minimum sweetness.

=== "Python"
    ```python
    class Solution:
        def maximizeSweetness(self, sweetness: List[int], k: int) -> int:
            ans = -1
            low, high = min(sweetness), sum(sweetness) // (k + 1)  # (1)

            while low < high:
                mid = (low + high + 1) // 2  # (2)
                if self.canBeDivided(sweetness, k, mid):
                    low = mid
                else:
                    high = mid - 1
            return high

        def canBeDivided(self, sweetness: List[int], k: int, target: int):
            count, curr_sum = 0, 0
            for value in sweetness:
                curr_sum += value
                if curr_sum >= target:
                    count += 1
                    curr_sum = 0  # (3)
            return count > k
    ```

    1. The upper bound is `sum(sweetness) // (k + 1)`. If not, any value, `x > sum(sweetness) // (k + 1)`, will lead to `x * (k + 1) > sum(sweetness)`.
    2. Due to `low = mid` and `high = mid - 1` conditions. If `low = mid + 1` and `high = mid`, use `mid = (low + high) // 2`
    3. Reset to 0 since the piece is cut and start a new piece

#### Complexity Analysis
* Time complexity: $O(n \log (s/(k + 1)))$ where $n$ is the number of chunks and $s$ is the total sweetness.  
The binary search space is `s / (k + 1)`, it takes $O(\log s/(k+1))$ by using binary search. For each iteration of binary search, we need to traverse the whole chocolate bar, which takes $O(n)$ time.
* Space complexity: $O(1)$  
Use limited variables. 

## Test