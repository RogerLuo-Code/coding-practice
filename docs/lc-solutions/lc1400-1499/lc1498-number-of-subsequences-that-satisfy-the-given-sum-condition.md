---
tags:
- Two Pointers
- Sorting
---

# LC1498. Number of Subsequences That Satisfy the Given Sum Condition
## Problem Description
[LeetCode Problem 1498](https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/description): You are given an array of integers `nums` and an integer `target`.

Return _the number of **non-empty** subsequences of_ `nums` _such that the sum of the minimum and maximum element on it is less or equal to_ `target`. Since the answer may be too large, return it **modulo** `109 + 7`.

## Clarification
- unsorted array
- find subsequences with min + max <= target

## Assumption

## Solution
### Approach - Sort + Two Pointers
Sorted array first and use two pointers:

- i, the index of minimum
- j, the index of maximum, j >= i

One starts from the beginning and the other starts from the end to find the first subsequence that satisfy `nums[i] + nums[j] <= target`. Then the number of sub sequences starting from `i` and before `j` that satisfy the condition is $2^{j - i}$. The number at index `i` is always included since `i + 1` will be considered when increasing `i` later. There are remaining `j - i` items to select from. Each item has two options: selected or not selected. So there are total $2^{j - i}$ options. 

Takes sequence `[3, 5, 6]` with target `9` as an example. 
```
[3  5  6]
 3  x  x  ->  3
 3  x  ✓  ->  3, 6
 3  ✓  x  ->  3, 5
 3  ✓  ✓  ->  3, 5, 6
```

=== "Python"
```python
class Solution:
    def numSubseq(self, nums: List[int], target: int) -> int:
        nums.sort()
        count = 0
        mod = 10**9 + 7

        idx_min, idx_max = 0, len(nums) - 1
        while idx_min <= idx_max:
            if nums[idx_min] + nums[idx_max] <= target:
                count += pow(2, idx_max - idx_min, mod)
                idx_min += 1
            else:
                idx_max -= 1

        return count % mod
```

#### Complexity Analysis
* Time complexity: $O(n \log n)$  
The sort function takes $O(n \log n)$ time, the while loop takes $n$ steps to go through all indices and each step may take $O(1)$ or $O(\log(\text{idx_max} - \text{idx_min}))$ for calling `pow` function.
* Space complexity: $O(1)$  
Since using in-place sort and two index variables, the time complexity is $O(1)$.
