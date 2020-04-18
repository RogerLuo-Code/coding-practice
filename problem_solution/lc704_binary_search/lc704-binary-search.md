# Leetcode Problem 704 - Binary Search

## Problem Description
[Leetcode Problem 704:](https://leetcode.com/problems/binary-search/) Given a **sorted** (in ascending order) integer array nums of n elements and a target value, write a function to search target in nums. If target exists, then return its index, otherwise return -1.

## Clarifications
* Sorted or unsorted array?
* Ascending or descending order?
* Data type? integer, floating point, or Generic?
* How large is the array size? Can load it into the memory?
* Any duplicates? Which index to return for duplicate values?
* Go through basic examples: empty array, array with 1 element, array with 2 elements, array with more elements. And test cases target exist, not exist, in the first position, and in the last position

## Approaches
Use binary search to find a target in a **sorted** array. The implementation is not difficult but easy to make small mistakes. Pay attention to details:  
* How to choose while loop condition? `left <= right`, `left < right`, or `left < right -1`?  
* How to update left and right indices? `left = middle` or `left = middle + 1`?  
The while loop and index update are working together. The general rule is to not accidently remove the target in the search space. For this problem, if use `left = middle` together with `while(left <= rigtht)`, it will get stuck when target not exists or down to last 2 elments with target on the right. Easy to debug considering there is only 2 elements left.
* index: for zero-based indexing, remember `array size - 1`.
* For index calculation, use `left + (right - left)/2` instead of `(left + right)/2`, sinc the latter one may cause overflow for very arge array. 
* Floatting point `==` comparison?


```java
class Solution {
    public int search(int[] nums, int target) {
        int left = 0;
        int right = nums.length - 1; // -1 for zero-based indexing
        int middle;
        
        while (left <= right){
            middle = left + (right -left)/2;
            
            if (nums[middle] < target){
                left = middle + 1;
            }
            else if (nums[middle] > target){
                right = middle - 1;
            }
            else{
                return middle;
            }                
        }
        return -1;
    }
}
```

## Complexity Analysis
* Time complexity: $\mathcal{O}(\log N)$

* Space complexity: $\mathcal{O}(1)$ since it only uses 3 indexing variables.


