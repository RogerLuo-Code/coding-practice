---
tags:
- Binary Search
---

# LC1533. Find the Index of the Large Integer
## Problem Description
[LeetCode Problem 1533](https://leetcode.com/problems/find-the-index-of-the-large-integer/): We have an integer array `arr`, where all the integers in `arr` are equal except for one integer which is **larger** than the rest of the integers. You will not be given direct access to the array, instead, you will have an **API** `ArrayReader` which have the following functions:

- `int compareSub(int l, int r, int x, int y)`: where `0 <= l, r, x, y < ArrayReader.length()`, `l <= r and` `x <= y`. The function compares the sum of sub-array `arr[l..r]` with the sum of the sub-array `arr[x..y]` and returns:
    - **1** if `arr[l]+arr[l+1]+...+arr[r] > arr[x]+arr[x+1]+...+arr[y]`.
    - **0** if `arr[l]+arr[l+1]+...+arr[r] == arr[x]+arr[x+1]+...+arr[y]`.
    - **-1** if `arr[l]+arr[l+1]+...+arr[r] < arr[x]+arr[x+1]+...+arr[y]`.
- `int length()`: Returns the size of the array.

You are allowed to call `compareSub()` **20 times** at most. You can assume both functions work in `O(1)` time.

Return _the index of the array `arr` which has the largest integer_.

## Clarification
- arr: one integer is larger and the rest are equal
- API function return 1, 0, or -1

## Assumption
-The larger number always exist

## Solution
### Approach - Binary Search
Put the array into two halves with the same size. if both halves contain the same elements, the sum of the two halves will be the same. If one half contains the larger value, the sum of that half will be larger. So we can use binary search to compare left half and right half:

- If `left half > right half`, skip right half and search the left half
- If `left half < right half`, skip left half and search the right half
- if `left half == right half`,  the larger element is at `left + half_length * 2` when comparing `[left, left + half_length - 1]` and `[left + half_length, left + half_length * 2 - 1]`. This only happens for subarray with odd number of elements.

=== "Python"
    ```python
    class Solution:
        def getIndex(self, reader: 'ArrayReader') -> int:
            left, right = 0, reader.length() - 1

            while left < right:
                h = (right - left + 1) // 2
                status = reader.compareSub(left, left + h - 1, left + h, left + h * 2 - 1)
                if status == 0:
                    return left + h * 2
                elif status == -1:
                    left = left + h
                else:
                    right = left + h - 1

            return left
    ```

#### Complexity Analysis
* Time complexity: $O(\log n)$  
After each iteration, the search space is reduced by half by using binary search. 
* Space complexity: $O(1)$  
Only using a few variables.

## Test