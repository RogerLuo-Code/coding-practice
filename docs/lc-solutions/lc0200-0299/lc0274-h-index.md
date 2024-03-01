---
tags:
- Sorting
---

# LC274. H-Index
## Problem Description
[LeetCode Problem 274](https://leetcode.com/problems/h-index/): Given an array of integers `citations` where `citations[i]` is the number of citations a researcher received for their `ith` paper, return _the researcher's h-index_.

According to the [definition of h-index on Wikipedia](https://en.wikipedia.org/wiki/H-index): The h-index is defined as the maximum value of `h` such that the given researcher has published at least `h` papers that have each been cited at least `h` times.

## Clarification

## Assumption

## Solution
### Approach - Sort + Binary Search
We can sort the `citations` first. Then problem is the same as [LC275 H-Indx II](lc0275-h-index-ii.md). We can use binary search to find the solution

=== "Python"
    ```python
    class Solution:
        def hIndex(self, citations: List[int]) -> int:
            citations_sorted = sorted(citations)

            n = len(citations)
            left, right = 0, len(citations) - 1

            while left < right:
                mid = (left + right) // 2
                if citations_sorted[mid] >= n - mid:
                    right = mid
                else:
                    left = mid + 1

            if citations_sorted[right] >= n - right:
                return n - right
            else:
                return 0
    ```

#### Complexity Analysis
* Time complexity: $O(n \log n)$  
The sorting time complexity is $O(n \log n)$ and the binary search after sorting is $O(\log n)$. So the total time complexity is $O(\log n)$
* Space complexity: $O(1)$  
Only use several variables.

### Approach - Counting Sort
The result is within the range `[0, len(citations)]`, since we can't h-index > the total number of papers published from definition. So we can create an array `count` to store the counts:

- For any paper with `citations == i`, increase `count[i]` by 1
- For any paper with `citations > n`, increase `count[n]` by 1

Then iterate backwards from the highest index of `count` and add total counts. When total counts exceed the `index` of the `count`, it means that we have the `index` number of papers that have `citations >= index`.

=== "Python"
    ```python
    class Solution:
        def hIndex(self, citations: List[int]) -> int:
            n = len(citations)
            count = [0] * (n + 1)

            for c in citations:
                if c > n:
                    count[n] += 1
                else:
                    count[c] += 1

            total = 0
            for idx in range(n, -1, -1):
                total += count[idx]
                if total >= idx:
                    return idx

            return 0
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
It takes $n$ steps to fill the `count` array and at most $n + 1$ steps to go through `count`. So the time complexity is $O(n)$.
* Space complexity: $O(n)$  
It needs `count` array with $n + 1$ elements.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Sort + Binary Search |  $O(n \log n)$ 	   	   	| $O(1)$  
Approach - Counting Sort |  $O(n)$      		| $O(n)$

## Test