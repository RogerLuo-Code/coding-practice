# Leetcode Problem 34 - Find First and Last Position of Element in Sorted Array

## Problem Description  
[Leetcode Problem 34:](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.

## Clarification
* data type of array elements
* sorted or unsorted? 
* if sorted, which order? ascending or descending?
* return values? tow elements? what if target not exist
* time complexity requirement?

## Approaches
For unsorted array, we can do a linear scan to find the positions. 
* First, do a linear scan from the left and break when finding an instance of target (i.e., the first position). If not, return since no target is found.  
* Then, do a second linear scan from the right/end. The first instance of target encountered will be the last position.

For sorted array (this problem), we can use binary search twice -- one to find the first position and the other to find the last position. Pay attendtion to subtle differences in finding the first and last positions.

<table>
<tr>
  <th> Find first position </th>
  <th> Find last position </th>
</tr>

<tr>
  <td>
  <pre><code>
  private int findFirst(int[] nums, int target) {
        // Find the first position of the target
        int left = 0;
        int right = nums.length - 1; 
        if (right < 0)
            return -1;
        int middle;
        
        while (left < right - 1) {
            middle = left + (right - left)/2; 
            
            if (target < nums[middle])
                right = middle - 1;
            else if (target > nums[middle])
                left = middle + 1;
            else 
                right = middle; // different
        }
        
        // Different: check left first
        if (nums[left] == target) 
            return left;
        else if (nums[right] == target)
            return right;
        else
            return -1;
    }
  </code></pre>
  </td>

  <td>
  <pre><code>
    private int findLast(int[] nums, int target) {
        // Find the last position of the target
        int left = 0;
        int right = nums.length - 1; 
        if (right < 0)
            return -1;
        int middle;
        
        while (left < right - 1) {
            middle = left + (right - left)/2; 
            
            if (target < nums[middle])
                right = middle - 1;
            else if (target > nums[middle])
                left = middle + 1;
            else 
                left = middle;  // different
        }
        
        // Different: check right first
        if (nums[right] == target) 
            return right;
        else if (nums[left] == target)
            return left;
        else
            return -1;
    }
  </code></pre>
  </td>
</tr>
</table>


```java
class Solution {
    public int[] searchRange(int[] nums, int target) {
        int[] positions = {-1, -1};
        positions[0] = findFirst(nums, target);
        if (positions[0] == -1)
            return positions;
        positions[1] = findLast(nums, target);
        
        return positions;
    }
    
    private int findFirst(int[] nums, int target) {
        // Find the first position of the target
        int left = 0;
        int right = nums.length - 1; // -1 for zero-based indexing 
        if (right < 0)
            return -1;
        int middle;
        
        while (left < right - 1) {
            middle = left + (right - left)/2; 
            
            if (target < nums[middle])
                right = middle - 1;
            else if (target > nums[middle])
                left = middle + 1;
            else // target == a[middle]
                right = middle; // not stop, continue to search to find the first position
        }
        
        // Post-processing with two elements left
        if (nums[left] == target) 
            return left;
        else if (nums[right] == target)
            return right;
        else
            return -1;
        
        // Alernative way
        // use while (left < right) and only check one element since the end contion is left == right
        // // left == right after while (left < right)
        // if (nums[left] == target) 
        //     return left;
        // else
        //     return -1;
        
        
    }
    
    private int findLast(int[] nums, int target) {
        // Find the last position of the target
        int left = 0;
        int right = nums.length - 1; // -1 for zero-based indexing 
        if (right < 0)
            return -1;
        int middle;
        
        while (left < right - 1) {
            middle = left + (right - left)/2; 
            
            if (target < nums[middle])
                right = middle - 1;
            else if (target > nums[middle])
                left = middle + 1;
            else // target == a[middle]
                left = middle;  // not stop, continue to search to find the last position
        }
        
        // Post-processing with two elements left
        if (nums[right] == target) 
            return right;
        else if (nums[left] == target)
            return left;
        else
            return -1;
    }
}
```

## Complexity Analysis
* **Time complexity**: $\mathcal{O}(\log n)$  
The solution use binary search twice and at most have $2 \lceil \log n \rceil$ iterations. Therefore the the time complexity is $\mathcal{O}(\log n)$. 
* **Space complexity**: $\mathcal{O}(1)$
Similar to classical binary search, it uses several variables for indices. Therefore it uses $\mathcal{O}(1)$ space. 