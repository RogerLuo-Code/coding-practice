---
tags:
    - Binary Search
---

# LC436. Find Right Interval
## Problem Description
[LeetCode Problem 436](https://leetcode.com/problems/find-right-interval/): You are given an array of `intervals`, where `intervals[i] = [starti, endi]` and each `starti` is **unique**.

The **right interval** for an interval `i` is an interval `j` such that `startj >= endi` and `startj` is **minimized**. Note that `i` may equal `j`.

Return _an array of **right interval** indices for each interval `i`_. If no **right interval** exists for interval `i`, then put `-1` at index `i`.

## Clarification
- an array of [start_i, end_i]
- start_i is unique
- Right interval?
- Can end_i < start_i?

## Assumption

## Solution
### Approach - Sort + Binary Search
From intervals, take `(start_i, i)` to formulate a new list. Sort the list based on `start_i` value. Then find `start_i` that meets the right interval requirement and return index `i`

=== "Python"
    ```python
    class Solution:
        def findRightInterval(self, intervals: List[List[int]]) -> List[int]:
            l = sorted((e[0], i) for i, e in enumerate(intervals))
            res = []
            for e in intervals:
                r = bisect.bisect_left(l, (e[1],))
                res.append(l[r][1] if r < len(l) else -1)
            return res
    ```

#### Complexity Analysis
* Time complexity: $O(n \log n)$  
	Sort takes $O(n \log n)$ and for-loop with binary search takes another $O(n \log n)$. So overall time complexity is $O(n \log n)$
* Space complexity: $O(n)$  
	Need to store a list of `(start_i, i)` and therefore use $O(n)$ space