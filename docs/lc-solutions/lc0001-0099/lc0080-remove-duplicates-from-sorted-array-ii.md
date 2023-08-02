---
tags:
    - Array
    - Two Pointers
    - Sliding  Window
---

# LC80. Remove Duplicates from Sorted Array II
## Problem Description
[LeetCode Problem 80](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/): Given an integer array `nums` sorted in **non-decreasing order**, remove some duplicates [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm)such that each unique element appears **at most twice**. The **relative order** of the elements should be kept the **same**.

Since it is impossible to change the length of the array in some languages, you must instead have the result be placed in the **first part** of the array `nums`. More formally, if there are `k` elements after removing the duplicates, then the first `k` elements of `nums` should hold the final result. It does not matter what you leave beyond the first `k` elements.

Return `k` _after placing the final result in the first_ `k`_slots of_ `nums`.

Do **not** allocate extra space for another array. You must do this by **modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm)**with O(1) extra memory.

### Similar Questions:
- [LC26 Remove duplicates from sorted array](lc0026-remove-duplicates-from-sorted-array.md)

## Clarification
- `num` is **sorted** in **non-decreasing** order
- Remove duplicate number > 2 times
- Keep the relative order

## Assumption
* Number of elements is within the range of integer type (Python integer type doesn't have this problem)

## Solution
Both solutions provided below can be extended to the case with at most `k` duplicates.  
### Approach - Two Pointers
The idea is to simply overwrite the duplicate elements that are unwanted instead of actually remove elements. To achieve this, a two-pointer approach will be used, where
- one pointer `i` tracks the index of the last valid element, and `i+1` is the next location that can be overwritten
- the other pointer `j` iterates over the array
Additional variable `nAppears` is used to track the count of  a particular element in the array. Note that `nAppears` is initialized and reset with `1`, since for any element itself counts appearing once. If `nAppears <= 2`, we can move the element from index `j` to index `i++`

=== "C++"
    ```cpp
    class Solution {
    public:
        int removeDuplicates(vector<int>& nums) {
            if (nums.empty()) return 0;
            
            int i = 0;
            int nAppears = 1; 
            
            for (int j = 1; j < nums.size(); j++) {
                if (nums[i] != nums[j]) {
                    nAppears = 1;
                }
                else {
                    nAppears++;
                }
                
                if (nAppears <= 2) {
                    i++;
                    nums[i] = nums[j];
                }
            }
            return i+1;
        }
    }; 
    ```

=== "Python"

    ```python
    class Solution:
        def removeDuplicates(self, nums: List[int]) -> int:
            i = 0
            n_appear = 1
            for j in range(1, len(nums)):
                if nums[i] == nums[j]:
                    n_appear += 1
                else:
                    n_appear = 1 # (1)
                
                if n_appear <= 2:
                    i += 1
                    nums[i] = nums[j]
            return i + 1
    ```

    1. if number itself, it appears once

#### Complexity Analysis
* Time complexity: $O(n)$  
	The for loop iterates the each element once. 
* Space complexity: $O(1)$  
	Use two pointers and `nAppears`. 

### Approach - Sliding Window
For better understanding, assume there is a sliding window of size `2` with `i` at the right boundary of the window, indicating  the next position that can be overwritten, `|nums[i-2], nums[i-1]| nums[i]`. So the sliding windows contains elements `nums[i-2]` and `nums[i-1]`. Then we can compare the new element `nums[i]` with `nums[i-2]`, if they are equal, we have 3 duplicates (using the property: array is sorted and nondecreasing) and therefore should skip this element. Otherwise, we can copy the new element to the location of index `i`.  

=== "C++"
    ```cpp
    class Solution {
    public:
        int removeDuplicates(vector<int>& nums) {
            int i = 0;
            for (int num : nums) {
                if (i < 2 || num > nums[i - 2]) {
                    nums[i++] = num;
                }
            }
            return i;
        }
    };
    ```

=== "Python"
    ```python
    i = 0
    for num in nums:
        if i < 2 or num > nums[i - 2]:
            nums[i] = num
            i += 1

    return i
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Since it iterates the whole array, the time complexity is $O(n)$.
* Space complexity: $O(1)$  
	Use one pointer. 

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  |
------------ | --------------- 	| ---------------- |
Approach - Two Pointers |  $O(n)$ 	   	   	| $O(1)$ |
Approach - Two Pointers + Sliding Window |  $O(n)$      		| $O(1)$ |

## Test