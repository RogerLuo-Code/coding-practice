---
tags:
- Binary Search
---

# LC1539. Kth Missing Positive Number
## Problem Description
[LeetCode Problem 1539](https://leetcode.com/problems/kth-missing-positive-number/): Given an array `arr` of positive integers sorted in a **strictly increasing order**, and an integer `k`.

Return _the_ `kth` _**positive** integer that is **missing** from this array._

## Clarification

## Assumption

## Solution
### Approach - Binary Search
The array `arr` can be transformed into a missing positive array, `arr_miss` with conversion `arr[i] - (i + 1)`. For example,
```
index, i:  0  1  2  3
arr:      [1  3  4  6]
arr_miss: [0  1  1  2]
```
`arr_miss[i]` represents how many missing positive so far at index `i`. So the question can be solved by the following two steps:

1. Find the smallest index, `idx`, of `arr_miss` such that `arr_miss[idx] >= k`
2. Obtain the `kth` missing positive integer

For step 1, we can use binary search to find the index. 

For step 2, `idx + k` is the `kth` positive integer. 
```
arr_miss[idx] + idx + 1 == arr[idx], not missing
arr_miss[idx] + idx, is the arr_miss[idx]th missing integer
k + idx, is the kth missing integer
```
Or another way to think about, the result is

$$\underbrace{arr[idx - 1]}_{\text{largest non-missing number} < \text{kth missing number}} + \underbrace{k - arr\_miss[idx - 1]}_{\text{offset, how far from kth missing number}} = arr[idx - 1] + k - (arr[idx - 1] - idx) = idx + k$$


=== "Python"
    ```python
    class Solution:
        def findKthPositive(self, arr: List[int], k: int) -> int:
            left, right = 0, len(arr)  # (1)

            while left < right:
                mid = (left + right) // 2

                if arr[mid] - (mid + 1) < k:
                    left = mid + 1
                else:
                    right = mid

            return left + k
    ```

    1. Need to cover the case where all missing numbers from arr < k. `len(arr) - 1` doesn't work

#### Complexity Analysis
* Time complexity: $O(\log)$  
Use binary search to find the index
* Space complexity: $O(1)$  
Use limited variables

## Test
- Array missing numbers < $k$