# LeetCode Problem 33 - Search in Rotated Sorted Array

## Problem Description
[LeetCode Problem 33](https://leetcode.com/problems/search-in-rotated-sorted-array/): Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand. (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]). You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array. Your algorithm's runtime complexity must be in the order of O(log n).

## Analysis
* Clarification:
  - sorted vs. unsorted?
  - ascending order vs. descending order?
  - rotated mean?
  - duplicates?
  - data type?
  - time complexity requirement
* Go through examples
* Solution:
  - Assumption:
  - Input/Output:
    Input: int array, int scalar
    Output: int scalar
  - Corner case:two elements [2, 1], target at the pivot point
  - Algorithm: variation of binary search
* Coding
* Test
  - Test corner cases: one element, 2 elements
  - Test general cases

## Approach
Since the problem requires $\mathcal{O}(\log n)$ time complexity and the array is rotated sorted, we can find ways to use binary search somehow. 
1. Use bineary search twice: find the rotation index first and search in the left or right part splitted by rotation index. 
2. Use binary search once with modified compare conditions

### Approach 1 - Use binary search twice

#### Algorithm
Use bineary search twice:   
* Find a rotation index use binary search 
    -  condition for rotation index is `nums[mid] > nums[mid + 1]`.
    -  move to the right if `nums[mid] >= nums[left]`. since the subarray from left to mid is sorted and no drop (no rotation index). 
    - move to the left if `nums[mid] < nums[left]`, since there is a drop and the rotation index should be between left and mid.
* Split array into two parts based on rotation index and identify which part includes the target  
* Perform classic bineary search on the chose part

![rotated array](https://leetcode.com/problems/search-in-rotated-sorted-array/Figures/33/33_small_mid.png)

#### Implementation
Special considerations:
* When doing compare `nums[mid] > nums[mid + 1]`, need to consider the corner case where `mid + 1` is out of bounds
* In finding rotation index, `>=` is used (NOT `>`) in the comparison `nums[mid] >= nums[left]`. Using `>` will fail for the case where `mid == left` and rotation index is on the right side of mid (e.g., array: [8, 9, 2, 3, 4], target: 9).  

```java
// Algorithm: 
//  - Use binary search to find the pivot 
//    - condition for pivot: nums[mid] > nums[mid + 1]; corner case: mid + 1 exceed the array length
//    - move to right: nums[mid] > nums[left]
//    - move to left: other conditions
//  - Use binary search to search left or right half

class Solution {
    public int search(int[] nums, int target) {
        if (nums == null || nums.length == 0)
            return -1;
        
        int pivotIdx = findRotateIndex(nums);
        
        if (target >= nums[0] &&  target <= nums[pivotIdx])
            return binarySearch(nums, 0, pivotIdx, target);
        else
            return binarySearch(nums, pivotIdx + 1, nums.length - 1, target);
    }
    
    public int findRotateIndex(int[] nums) {
        int left = 0; 
        int right = nums.length - 1; // -1 for zero-based indexing
        int mid; 
        
        while (left <= right) {
            mid = left + (right - left)/2;
            
            if (mid + 1 < nums.length && nums[mid] > nums[mid + 1]) {
                return mid; // find the pivot at mid
            }
            else if (nums[mid] >= nums[left]) 
                left = mid + 1;
            else 
                right = mid - 1;
        }
        return 0;
    }
    
    public int binarySearch(int[] nums, int left, int right, int target) {
        int mid;
        
        while (left <= right) {
            mid = left + (right - left)/2;
            
            if (target == nums[mid])
                return mid;
            else if (target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }
        
        return -1;
    }
}
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(\log n)$  
The first binary search takes $\log n$ steps and the second binary search also takes $\log n$ steps. The total are $\log n + \log n$ and therefore the time complexity is $\mathcal{O}(\log n)$ .
* **Space complexity**: $\mathcal{O}(1)$  
It only use limit varaitions to save indices and therefore the space complexity is $\mathcal{O}(1)$.

### Approach 2 - Use binary search once

#### Algorithm
Use binary search idea to reduce search space by half based on the properterty of rotated sorted array (some subarray is sorted). For each search, the array could be seprated by rotated subarray and non-rotated subarrray. Move to left or right based on whether the target is in the non-rotated subarray. There are two situations to consider:
* The subarray from left to mid is non-rotated (i.e., sorted). It is easy to check whether the target is in the non-rotated subarray.
* The subarray from left to mid is rotated. We can easily check whether the target is on the other subarray from mid to right since it is non-rotated. 

#### Implementation
Note that when doing `nums[mid] >= nums[left]`, it needs to use `>=` instead of `>`. Otherwise, it will fail on the simple 2-element case (array: [5, 4], target: 4).

```java
class Solution {
    public int search(int[] nums, int target) {
        if (nums == null || nums.length == 0)
            return -1;
        
        int left = 0;
        int right = nums.length - 1; // -1 for zero-based indexing
        int mid; 
        
        while (left <= right) {
            mid = left + (right - left)/2;
            
            if (target == nums[mid])
                return mid;
            else if (nums[mid] >= nums[left]) { // must be >=; non-rotated subarray from left to mid; pivot point on the right of mid
                if (target >= nums[left] && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            } 
            else { // non-rotated subarray from mid to right; pivot point on the right
                if (target > nums[mid] && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        
        return -1;
    }
}
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(\log n)$  
Since it uses binary search once, the time complexity is $\mathcal{O}(\log n)$.
* **Space complexity**: $\mathcal{O}(1)$  


### Complexity Summary
|     | Time Complexity | Space Complexity  
| ----- | ----- | ----- |  
| Approach 1 | $\mathcal{O}(\log n)$ | $\mathcal{O}(1)$ |  
| Approach 2 | $\mathcal{O}(\log n)$ | $\mathcal{O}(1)$ | 


