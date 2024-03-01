---
tags:
- Binary Search
---

# LC275. H-Index II
## Problem Description
[LeetCode Problem 275](https://leetcode.com/problems/h-index-ii/): Given an array of integers `citations` where `citations[i]` is the number of citations a researcher received for their `ith` paper and `citations` is sorted in **ascending order**, return _the researcher's h-index_.

According to the [definition of h-index on Wikipedia](https://en.wikipedia.org/wiki/H-index): The h-index is defined as the maximum value of `h` such that the given researcher has published at least `h` papers that have each been cited at least `h` times.

You must write an algorithm that runs in logarithmic time.

## Clarification
- citations is sorted in ascending order
- h-index definition

## Assumption

## Solution
### Approach - Binary Search
Since the citation array is sorted in **ascending** order, for index `i` (0-based), it has `citations[i]` and `n - i` (if `i` is 1-based index, it will be `n - i + 1`) papers with `citations[j] >= citations[i]`, where `j >= i`. Essentially, the problem is to find the **first** index where 

$$\text{citations}[i] >= n - i$$

Note that if $\text{citations}[i] >= n - i$, then any `j` with `j > i` also satisfies the equation, $\text{citations}[j] >= \text{citations}[j] >= n - i > n - j$.


=== "Python"
    ```python
    class Solution:
        def hIndex(self, citations: List[int]) -> int:
            n = len(citations)
            left, right = 0, n - 1

            '''
            1 2 3 4 5
            0 1 2 3 4
            [0 1 3 5 6]
                l
                r 
                    r
            '''
            while left < right:
                mid = (left + right) // 2
                if citations[mid] >= n - mid:
                    right = mid
                else:
                    left = mid + 1

            if n - right <= citations[right]:
                return n - right
            else:
                return 0
    ```

    1. Handle empty array or array with only 1 element

#### Complexity Analysis
* Time complexity: $O(\log n)$  
Since using the binary search, so the time complexity is $O(\log n)$.
* Space complexity: $O(1)$  
Only use two index variables.

## Test
- Empty array
- Array with 1 element