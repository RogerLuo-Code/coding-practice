---
tags:
- Binary Search
- Sorting
---

# LC354. Russian Doll Envelopes
## Problem Description
[LeetCode Problem 354](https://leetcode.com/problems/russian-doll-envelopes/): You are given a 2D array of integers `envelopes` where `envelopes[i] = [wi, hi]` represents the width and the height of an envelope.

One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.

Return _the maximum number of envelopes you can Russian doll (i.e., put one inside the other)_.

**Note:** You cannot rotate an envelope.

## Clarification
- 2d array
- fit, w_i < w_i_out and h_i < h_i_out and no rotation
- return max number of envelops

## Assumption
- width and height > 0

## Solution
### Approach - Sorting + Binary Search
Since the problem involves a 2D array, the general idea is to sort the array and reduce the problem into a 1D array, which is similar to [LC300 - Longest Increasing Subsequences](lc0300-longest-increasing-subsequence.md).

1. Sort the array in increasing order of width. And if two widths are the same, sort height in decreasing order. The reason to sort height in decreasing order to handle unfit cases where widths are the same. For example, `[[3, 3], [3, 4], [3, 5]]` vs. `[[3, 5], [3, 4], [3, 3]]`. Refer to [@rhythm_varshney's explanations](https://leetcode.com/problems/russian-doll-envelopes/solutions/2071477/c-java-python-best-explanation-with-pictures/?envType=study-plan-v2&envId=binary-search).
2. Find longest increasing subsequence along the height. Similar to [LC300 - Longest Increasing Subsequences](lc0300-longest-increasing-subsequence.md).

=== "Python"
    ```python
    class Solution:
        def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
            envelopes.sort(key=lambda x: (x[0], -x[1]))  # (1)
            sub = []
            for (w, h) in envelopes:
                if not sub or sub[-1] < h:
                    sub.append(h)
                else:
                    idx = bisect_left(sub, h)
                    sub[idx] = h
            return len(sub) 
    ```

    1.  Sorted by width and then by height. Since `height > 0`, use `-height` will sort height decreasingly. 

#### Complexity Analysis
* Time complexity: $O(n \log n)$  
Go through all envelops and use binary search for each step. 
* Space complexity: $O(n)$  
Use an array to store longest increasing subsequences. The worst case could be the whole array.

## Test