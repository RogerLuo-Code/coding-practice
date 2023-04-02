---
tags:
    - Array
    - Two Pointers
---

# LC26. Remove Duplicates from Sorted Array
## Problem Description
[LeetCode Problem 26](https://leetcode.com/problems/remove-duplicates-from-sorted-array/): Given an integer array `nums` sorted in **non-decreasing order**, remove the duplicates [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm) such that each unique element appears only **once**. The **relative order** of the elements should be kept the **same**.

Return `k` _after placing the final result in the first_ `k` _slots of_ `nums`.

Do **not** allocate extra space for another array. You must do this by **modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm)** with O(1) extra memory.

### Similar questions:
- [LC27 Remove Element](lc0027-remove-element.md)


## Clarification
- **Sorted** integer array
- Remove duplicate **in-place**
- Keep the relative order
- Empty array?

## Assumption
Input array has at least 2 elements.

## Solution
### Approach - Two Pointers
Since the array is **sorted**, duplicates will show up together in neighbor. Take advantage of this pattern, we will use two pointers:  
- One pointer `i` to track the **index** of unique element  
- The other pointer `j` to track the index of current element  
Essentially, once an element is encountered, simply bypass its duplicates and move on to the next unique element. So  
- When `nums[i] == nums[j]`, increase `j` to skip the duplicate  
- When `nums[i] != nums[j]`,  the duplicate ends and copy the value to `nums[i+1]` and increase `i`  

=== "C++"
    ```cpp
    class Solution {
    public:
        int removeDuplicates(vector<int>& nums) {
            if (nums.size() == 0) return 0; // later j starts with 1.

            int i = 0;
            for (int j = 1; j < nums.size(); j++) { // (1)
                if (nums[i] != nums[j]) {
                    i++;
                    nums[i] = nums[j];
                }
            }

            return i + 1; // (2)
        }
    };
    ```

    1. `j` starts from 1
    2. Return number of elements instead of index

=== "Python"

    ``` python
    def removeDuplicates(self, nums: List[int]) -> int:
        j = 0
        for i in range(1, len(nums)): # (1)
            if nums[j] != nums[i]:
                j += 1
                nums[j] = nums[i]
        return j + 1 # (2)
    ```

    1. `i` starts from 1
    2. Return number of elements instead of index

#### Complexity Analysis
* Time complexity: $O(n)$  
	Iterate the whole array once.
* Space complexity: $O(1)$  
	Only use two pointers.

## Test