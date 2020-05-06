# Leetcode Problem 34 - Find First and Last Position of Element in Sorted Array

## Problem Description  
[Leetcode Problem 34:](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.

## Analysis
* Clarification: 
  - sorted or unsorted?
  - ascending or descending order 
  - data type
  - time complexity requirement O(log n)
  - return value? 
  - what if target doesnt exist?
* Go through exmaples
* Solution:
  - Assumption
  - Input/Output: int array and int scalar as input and int array as output
  - Corner case: array is empty
  - Time/space complexity
* Coding
* Test case
  - test corner cases: zero array, target not exist, array with 0, 1, and 2 elements
  - test general cases

## Approaches
For unsorted array, we can do a linear scan to find the positions. 
* First, do a linear scan from the left and break when finding an instance of target (i.e., the first position). If not, return since no target is found.  
* Then, do a second linear scan from the right/end. The first instance of target encountered will be the last position.

For sorted array (this problem), we can use binary search twice -- one to find the first position and the other to find the last position. Pay attendtion to subtle differences in finding the first and last positions. **Improvement:** The second binary search can start from the first position found in the first binary search.

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
        if (nums == null || nums.length == 0)
            return positions;

        positions[0] = findFirst(nums, target);
        if (positions[0] == -1)
            return positions;
        positions[1] = findLast(nums, target, positions[0]);
        
        return positions;
    }
    
    private int findFirst(int[] nums, int target) {
        // Find the first position of the target
        int left = 0;
        int right = nums.length - 1; // -1 for zero-based indexing 
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
    
    private int findLast(int[] nums, int target, int start) {
        // Find the last position of the target
        int left = start;
        int right = nums.length - 1; // -1 for zero-based indexing 
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