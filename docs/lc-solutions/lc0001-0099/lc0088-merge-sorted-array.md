---
tags:
    - Array
    - Two Pointers
---

# LC88. Merge Sorted Array
## Problem Description
[LeetCode Problem 88](https://leetcode.com/problems/merge-sorted-array/): You are given two integer arrays `nums1` and `nums2`, sorted in **non-decreasing order**, and two integers `m` and `n`, representing the number of elements in `nums1` and `nums2` respectively.

**Merge** `nums1` and `nums2` into a single array sorted in **non-decreasing order**.

The final sorted array should not be returned by the function, but instead be _stored inside the array_ `nums1`. To accommodate this, `nums1` has a length of `m + n`, where the first `m` elements denote the elements that should be merged, and the last `n` elements are set to `0` and should be ignored. `nums2`has a length of `n`.

## Clarification

## Assumption

## Solution
### Approach
The problem can be considered as a revert sorting problem, comparing and merging elements by iterating backwards. We can use three pointers:
- `p1` starts from the last element of nums1
- `p2` starts from the last element of nums2
- `p` starts from the last position of nums1

By iterating backwards, we compare elements at `p1` and `p2` and move the large one to `p`.

**Follow-up questions:** How to make sure that elements in `nums1` are not accidentally overwritten by iterating backwards?

**Answers**: 
- Start from the initialization `p1 + n = p` and `p2 = n-1`.
- When doing merge sorting, `p` is always decreased by 1 and either `p1` or `p2` is decreased by 1
	- When reducing `p1`, the gap between `p` and `p1` stays the same and no overwritten
	- When reducing `p2`, the gap between `p` and `p1` shrinks by 1, at most `n` times. After `n` times, `p = p1` and therefore no overwritten. 

=== "Python"
    ```python
    class Solution:
        def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
            """
            Do not return anything, modify nums1 in-place instead.
            """
            i = m - 1
            j = n - 1
            
            for k in range(m + n - 1, -1, -1):
                # k from m + n - 1 to 0
                if i < 0:
                    nums1[k] = nums2[j]
                    j -= 1
                elif j < 0:
                    nums1[k] = nums1[i]
                    i -= 1
                elif nums1[i] >= nums2[j]:
                    nums1[k] = nums1[i]
                    i -= 1
                else:
                    nums1[k] = nums2[j]
                    j -= 1
    ```

=== "C++"
    ```cpp
    class Solution {
    public:
        void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
            int i = m - 1;
            int j = n - 1;
            // int k = m + n - 1;
            
            for (int k = m + n - 1; k >= 0; k--) {
                // if (i < 0 && j < 0) {
                //     break;
                // } // no need since k < 0 and won't enter the for loop
            if (i < 0) {
                    // only nums2 elements left
                    nums1[k] = nums2[j--];
                }
                else if (j < 0) {
                    // Can be skipped and no need copy since the elements are there
                    // only nums1 elements left
                    // nums1[k] = nums1[i--]; // no need copy
                }
                else {
                    // compare elements and move the larger 
                    if (nums2[j] > nums1[i]) {
                        nums1[k] = nums2[j--];
                    }
                    else {
                        nums1[k] = nums1[i--];
                    }
                }
            }
            
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n+m)$  
	Since iterating backwards of all positions of nums1 (total `m+n`), the time complexity is $O(n+m)$.   
* Space complexity: $O(1)$  
	Only using three pointers and therefore constant space complexity.

## Test
- Two empty arrays
- One array is empty
- Normal case with smaller `m`
- Normal case with smaller `n`