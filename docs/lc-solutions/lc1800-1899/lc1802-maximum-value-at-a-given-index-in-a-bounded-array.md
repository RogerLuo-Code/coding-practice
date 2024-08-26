---
tags:
- Binary Search
---

# LC1802. Maximum Value at a Given Index in a Bounded Array
## Problem Description
[LeetCode Problem 1802](https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array): You are given three positive integers: `n`, `index`, and `maxSum`. You want to construct an array `nums` (**0-indexed**) that satisfies the following conditions:

- `nums.length == n`
- `nums[i]` is a **positive** integer where `0 <= i < n`.
- `abs(nums[i] - nums[i+1]) <= 1` where `0 <= i < n-1`.
- The sum of all the elements of `nums` does not exceed `maxSum`.
- `nums[index]` is **maximized**.

Return `nums[index]` _of the constructed array_.

Note that `abs(x)` equals `x` if `x >= 0`, and `-x` otherwise.

## Clarification
- Allow duplicates
- Positive integer

## Assumption

## Solution
### Approach - Binary Search
To maximize `nums[index]`, it should be a **peak** of the array. The array will look like this with **positive** integers:

$$
\begin{matrix}
\text{index:} & 0 & 1 & \cdots & i - d & \cdots & i - 2 & i - 1 & i & i + 1 & i + 2 & \cdots & i + d & \cdots & n - 2 & n -1 \\
\text{value:} & 1 & 1 & \cdots & m - d & \cdots & m - 2 & m - 1 & m & m - 1 & m - 2 & \cdots & m - d & \cdots & 1 & 1
\end{matrix}
$$

Note that:

- The optimized solution is always reduced by the largest step `1` from the max value `m` until down to 1 due to positive integer requirement. If any two values are equal, we can always move `1` to the max value to make it higher.
- Depends on what the max value `m` and index `i` are. The value at index `0` could be either `m - i` or `1` and the right value at index `n - 1` could be either `m - (n - 1 - index)` or `1`.  
- Since numbers must be positive, we need at least `n` ones to populate the array. The array becomes

$$
\begin{matrix}
\text{index:} & 0 & 0 & \cdots & i - d & \cdots & i - 2 & i - 1 & i & i + 1 & i + 2 & \cdots & i + d & \cdots & n - 2 & n -1 \\
\text{value:} & 0 & 0 & \cdots & m - d & \cdots & m - 2 & m - 1 & m & m - 1 & m - 2 & \cdots & m - d & \cdots & 0 & 0
\end{matrix}
$$

To compute the sum of above array, we can divide it into two subarrays (left and right containing `m`): `[left, left + 1, ..., m - 1, m]` and `[m, m - 1, ..., right + 1, right]` and compute the sum of subarrays. 

The sum of `[left, left + 1, ..., m - 1, m]` or `[0, 0, 0 (left), 1, ..., m - 1, m]` is `(m + left) * (m - left + 1) / 2`.


Essentially we are trying to find the max value `m` such that `sum(array) <= maxSum`.

- If `sum(array) <= maxSum`, `m` is the potential of the max value and we can further search some values >= `m`
- Otherwise, `m` is too large, we need to search smaller ones.
Based on this, we can use binary search to find the max value `m`. 

[@lee215](https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/solutions/1119801/java-c-python-binary-search/?envType=study-plan-v2&envId=binary-search) gives an elegant solution.

=== "Python"
    ```python
    class Solution:
        def maxValue(self, n: int, index: int, maxSum: int) -> int:
            maxSum -= n  # (1)
            left, right = 0, maxSum
            while left < right:
                mid = (left + right + 1) // 2
                if self.getSum(n, index, mid) <= maxSum:
                    left = mid
                else:
                    right = mid - 1
            return left + 1  # (2)

        def getSum(self, n: int, index: int, valueMax: int) -> int:
            valueLeft = max(valueMax - index, 0)
            res = (valueMax + valueLeft) * (valueMax - valueLeft + 1) / 2
            valueRight = max(valueMax - (n - 1 - index), 0)
            res += (valueMax + valueRight) * (valueMax - valueRight + 1) / 2
            return res - valueMax  # (3)
    ```

    1. All number are positive, assign 1 to each element
    2. +1 since reducing 1 from each position at the 1st line of the code
    3. `valueMax` is added twice and needs to remove one


#### Complexity Analysis
* Time complexity: $O(\log \text{maxSum})$  
It takes $O(\log \text{maxSum})$ steps to search the max value. For `getSum` function, it takes $O(1)$ to compute. 
* Space complexity: $O(1)$  
Only use limited variables.

## Test