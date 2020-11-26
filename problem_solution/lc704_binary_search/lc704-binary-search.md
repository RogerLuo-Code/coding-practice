# Leetcode Problem 704 - Binary Search

## Problem Description
[Leetcode Problem 704:](https://leetcode.com/problems/binary-search/) Given a **sorted** (in ascending order) integer array nums of n elements and a target value, write a function to search target in nums. If target exists, then return its index, otherwise return -1.

## Analysis
* Clarifications
    - Sorted or unsorted array?
    - Ascending or descending order?
    - Data type? integer, floating point, or Generic?
    - How large is the array size? Can load it into the memory?
    - Range of each element?
    - Any duplicates? Which index to return for duplicate values?
* Go through some examples
* Solution
    - Assumptions: array size can be loaded into the memory; element range is within integer range.
    - Input/output (signature)
    - Corner cases: empty array
    - Algorithm: Binary search
    - Time/space complexity
* Coding
* Test
    - Test corner cases: null and empty array, array with 0, 1, or 2 elements. Target not exist, exists on the first or last position.
    - Test general cases
    

## Approaches
Use binary search to find a target in a **sorted** array. The implementation is not difficult but easy to make small mistakes. Pay attention to details:  
* How to choose while loop condition? `left <= right`, `left < right`, or `left < right -1`?  
* How to update left and right indices? `left = middle` or `left = middle + 1`?  
The while loop and index update are working together. The general rule is to not accidently remove the target in the search space. For this problem, if use `left = middle` together with `while(left <= rigtht)`, it will get stuck when target not exists or down to last 2 elments with target on the right. **Tip:** Easy to debug considering there is only 2 elements left.
* index: for zero-based indexing, remember `array size - 1`.
* For index calculation, use `left + (right - left)/2` instead of `(left + right)/2`, sinc the latter one may cause overflow for very arge array. 
* Array is null or empty?
* Floatting point `==` comparison?


```java
class Solution {
    public int search(int[] nums, int target) {
        if (nums == null || nums.length == 0)
            return -1;
        
        int left = 0;
        int right = nums.length - 1; // -1 for zero-based indexing
        int middle;  
        
        while (left <= right){
            middle = left + (right - left)/2;
            
            if (target < nums[middle])
                right = middle - 1;
            else if (target > nums[middle])
                left = middle + 1;
            else // equal case
                return middle;
        }
        
        // Postprocessing no return after while loop (searching all elements)
        return - 1;
        
    }
}
```

## Complexity Analysis
* **Time complexity**: $\mathcal{O}(\log n)$ -- Logarithmic Time  
Binary search is performed by dividing the existing array in half for each iteration. First $N$ becomes $N/2$, then it becomes $N/4$ and go on till the size become 1. The maximum number of iterations is $\log N$ (base 2).
* **Space complexity**: $\mathcal{O}(1)$ -- Constant Space  
Binary search just requires tracking of 3 indices for each iteration. Therefore it is $\mathcal{O}(1)$ or constant space.


