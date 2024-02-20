---
tags:
    - Binary Search
---

# LC278. First Bad Version
## Problem Description
[LeetCode Problem 278](https://leetcode.com/problems/first-bad-version/): You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have `n` versions `[1, 2, ..., n]` and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API `bool isBadVersion(version)` which returns whether `version` is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

## Clarification
- [1, 2, ..., n] versions
- find out the first bad version
- requirement: minimize the number of calls to the API

## Assumption

## Solution
### Approach - Binary Search
Each version in [1, 2, ..., n] has its status in good ($0$) or bad ($1$):

$$\begin{bmatrix}1 & 2 & \cdots & i & i + 1 & \cdots n \\ 0 & 0 & \cdots & 0 & 1 & \cdots & 1 \end{bmatrix}$$

The status array consists of just two statuses and is sorted. So we can use binary search to find the first bad version effectively.

=== "Python"
    ```python
    class Solution:
        def firstBadVersion(self, n: int) -> int:
            left, right = 0, n

            while left < right:
                mid = (left + right) // 2

                if isBadVersion(mid):
                    right = mid
                else:
                    left = mid + 1

            return left
    ```

#### Complexity Analysis
* Time complexity: $O(\log n)$  
	Since using binary search, the time complexity is $O(\log n)$.
* Space complexity: $O(1)$  
	Only use two index variables.

## Test