---
tags:
- Binary Search
- Sorting
---

# LC2300. Successful Pairs of Spells and Potions
## Problem Description
[LeetCode Problem 2300](https://leetcode.com/problems/successful-pairs-of-spells-and-potions): You are given two positive integer arrays `spells` and `potions`, of length `n` and `m` respectively, where `spells[i]` represents the strength of the `ith` spell and `potions[j]` represents the strength of the `jth` potion.

You are also given an integer `success`. A spell and potion pair is considered **successful** if the **product** of their strengths is **at least**`success`.

Return _an integer array_ `pairs` _of length_ `n` _where_ `pairs[i]` _is the number of **potions** that will form a successful pair with the_ `ith` _spell._

## Clarification
- two positive integer arrays with different size
- spells[i] * potions[j] >=  success (int)
- return pairs array
- sorted or unsorted

## Assumption
- n >= 1 and m >= 1

## Solution
### Approach - Sorting + Binary Search
Sort `portions` array and use binary search to find the first `portion[j]` meet the success condition for `spell[i]`. Then the rest of portions (j+1, j+2, ..., m-1) will also meet the success condition. The total number for `spell[i]` is `m - j`. 

=== "Python"
    ```python
    class Solution:
        def successfulPairs(self, spells: List[int], potions: List[int], success: int) -> List[int]:
            n, m = len(spells), len(potions)
            potions.sort()
            pairs = [0] * n

            for i in range(len(spells)):
                left, right = 0, m - 1
                while left < right:
                    mid = (left + right) // 2
                    if potions[mid] * spells[i] >= success:
                        right = mid
                    else:
                        left = mid + 1

                if potions[left] * spells[i] >= success:
                    pairs[i] = m - left
                else:
                    pairs[i] = m - left - 1

            return pairs
    ```

=== "Python - Simplified"
    ```python
    class Solution:
        def successfulPairs(self, spells: List[int], potions: List[int], success: int) -> List[int]:
            potions.sort()
            return [len(potions) - bisect_left(potions, (success + a - 1) // a) for a in spells] # (1)
    ```

    1. `(success + a - 1) // a` is the ceiling value of `success / spells[i]`

#### Complexity Analysis
* Time complexity: $O((n + m) \log m)$  
The sort takes $O(m \log m)$ and find all pairs with binary search takes $O(n \log m)$
* Space complexity: $O(n)$  
Return array of pairs with size n

## Test