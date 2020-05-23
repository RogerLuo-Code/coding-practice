# LeetCode Problem 81 - Search in Rotated Sorted Array II 

## Problem Description
[LeetCode Problem 81](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/): Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand. (i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]). You are given a target value to search. If found in the array return true, otherwise return false.

## Analysis
This problem is similar to [LeetCode Problem 33](https://leetcode.com/problems/search-in-rotated-sorted-array/) ([solution](../lc33_search_rotated_sorted_array/lc33_search_rotated_sorted_array.md)) except the corner case: `nums[left] == nums[mid] == nums[right]`.

## Approach
### Algorithm
Use binary search but need to consider the corner case where `nums[left] == nums[mid] == nums[right]` and  don't know which side is in ascending order. When that happens we move left and right pointers by one position, `left++` and `right--`, to remove duplicates.  

### Implementation
```java
class Solution {
    public boolean search(int[] nums, int target) {
        if (nums == null || nums.length == 0)
            return false;
        
        int left = 0;
        int right = nums.length - 1;
        int mid;
        
       // [s s s s s e e e e b b b s s s s]
       //                ^ 
        while (left <= right) {
            mid = left + (right - left)/2;
            
            if (target == nums[mid])
                return true;
            else if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
                left++;
                right--;
            } 
            else if (nums[mid] >= nums[left]) { // sorted subarray from left to mid
                if (target >= nums[left] && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else { // sorted subarray from mid to right
                if (target > nums[mid] && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        return false;
    }
}
```

### Complexity Analysis 
* **Time complexity**: Average: $\mathcal{O}(\log n)$; Worse: $\mathcal{O} (n)$
* In the worse case, just move left and right pointers by one position, which needs $n/2$ steps. So the time complexity is $\mathcal{O} (n)$. 
* In the average case, binary search needs $\log n$ steps. So the time complexity is $\mathcal{O} (\log n)$. 
* **Space complexity**: $\mathcal{O}(1)$ as only using some index variables
