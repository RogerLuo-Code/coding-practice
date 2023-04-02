---
tags:
    - Array
    - Two Pointers
---

# LC27. Remove Element
## Problem Description
[LeetCode Problem 27](https://leetcode.com/problems/remove-element/): Given an integer array `nums` and an integer `val`, remove all occurrences of `val` in `nums` [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm). The relative order of the elements may be changed.

Return `k` _after placing the final result in the first_ `k` _slots of_ `nums`.

Do **not** allocate extra space for another array. You must do this by **modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm)** with O(1) extra memory.

### Similar questions:
- [LC26 Remove duplicates from sorted array](lc0026-remove-duplicates-from-sorted-array.md)

## Clarification
- Remove all occurrences of val
- No change on array size
- Store the result in the first part of the array
- In-place mean? no allocation of additional array; modify the input array
- Return number of elements
- Go through examples

## Assumption
- Number of elements is within the range of integer type

## Solution
### Approach - Two Pointers With Move
Use two pointers:  
- One pointer `i` to track the **next** location to store the element that is not `val`  
- The other pointer `j` moves along the array, tracking the index of the current element  
???+ note
    Clearly understand the physical meanings of two pointers
Initialize both pointer with zeros, and  
- When `nums[j] == val`, skip this element by increasing `j`.  
- When `nums[j] != val`, copy value to `nums[i]`, i.e., `nums[i] = nums[j]`, 

=== "C++"
    ```cpp
    class Solution {
    public:
        int removeElement(vector<int>& nums, int val) {
            int i = 0;
            for (int j = 0; j < nums.size(); j++) {
                if (nums[j] != val) {
                    nums[i++] = nums[j];
                }
            }
            return i; // i already plus 1 so no need index to number of elements conversion
        }
    }; 
    ```

=== "Python"
    ```python
    def removeElement(self, nums: List[int], val: int) -> int:
        j = 0
        for i in range(len(nums)):
            if nums[i] != val:
                nums[j] = nums[i]
                j += 1
        return j
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Iterate the whole array once.   
* Space complexity: $O(1)$
	Only use two pointers.

### Approach - Two Pointers With Swap
Use two pointers:
- One pointer `i` to track the location to store the element that is not `val`
- One pointer `n`  represents the current array length, which will be reduced if `nums[i] == val`

When `nums[i] == val`, 
- Swap the current element at index `i` with the last element `n - 1`
- Reduce array size `n` 

Note that the last element at `n - 1` is swapped could be the value needs to be removed. In the next iteration, the swapped element will be checked.

Compared to previous approach, it is more efficient when the number of elements to remove is small. The drawback is that the relative order is not maintained. 

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int i = 0;
        int n = nums.size();
        
        while (i < n) {
            if (nums[i] == val) {
                nums[i] = nums[n - 1];
                n--; // reduce array size
            }
            else {
                i++;
            }
        }
        
        return i;
    }
};
```

#### Complexity Analysis
* Time complexity: $O(n)$  
	`while` condition ends at `i == n` where `i` starts from the beginning and `n` starts from the end. It traverse at most `n` steps.   
* Space complexity: $O(1)$
	Use several local variables with constant space complexity. 

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Two pointers with move |  $O(n)$ 	   	   	| $O(1)$  
Approach - Two pointers with swap |  $O(n)$      		| $O(1)$

## Test