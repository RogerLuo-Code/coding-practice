---
tags:
    - Array
    - Two Pointers
    - Prefix Sum
---

# LC209. Minimum Size Subarray Sum
## Problem Description
[LeetCode Problem 209](https://leetcode.com/problems/minimum-size-subarray-sum/): Given an array of positive integers `nums` and a positive integer `target`, return the minimal length of a **contiguous subarray** `[numsl, numsl+1, ..., numsr-1, numsr]` of which the sum is greater than or equal to `target`. If there is no such subarray, return `0` instead.

## Clarification
- **Positive** integer

## Assumption
- Long int can store the sum values (i.e., sum doesn't exceed the limits of long integer)

## Solution
### Approach - Brute Force
Use two for-loops to find sum of the subarrays and update the minimal length. There are several improvements implemented :

- Break the 2nd loop early if it is find the first index `j` for a given index `i`. Since finding the minimal length, any values after `j` will have a larger length
- Define a variable `sum` to store the sum values for subarray starting from index `i`
- Initialize `length = n + 1 > n = size of nums`. When `length = n + 1`, we know minimal length is not updated and therefore return zero in the end.  

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        typedef vector<int>::size_type vec_size;
        vec_size n = nums.size();
        long int sum;
        vec_size length = n + 1; // length >= 0
            
        for (vec_size i = 0; i < n; i++) {
            sum = 0;
            for (vec_size j = i; j < n; j++) {
                sum += nums[j];
                if (sum >= target) {
                    if (j - i + 1 < length) { // j >= i, no need to worried about negative causing overflow of unsigned integer
                        length = j - i + 1; 
                    }
                    break;
                }
            }
        }
        return (length == n + 1) ? 0 : length;
    }
};
```

#### Complexity Analysis
* Time complexity: $O(n^2)$  
	Since using two for-loops to find the subarrays, the time complexity is $O(n^2)$   
* Space complexity: $O(1)$
	Only use several local variables with constant space complexity.

### Approach - Binary Search
We can improve the brute force approach by using the binary search in the 2nd for-loop. Instead of iterating linearly to find the sum that `> target`, we can use binary search to find the lower bound  of the index with value that is `cusum[i-1] + target`. Note that we add zero as the first element of cusum to compare `cusum[i] - 0` besides compare `cusum[i] - cusum[j]`. So the index will be shifted by 1. 

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        int minLength = n + 1; // n + 1 is not achievable since the max length is n, which can be used to check whether valid subarray exists
        int length;
        
        vector<int> cusum(n+1); // cumulative sum [0, n+1] with additional 0 element at the beginning
        // Compute cumulative sum
        cusum[0] = 0; // add zero to the first element for checking individual cusum values
        for (int i = 1; i <= n; i++) {
            cusum[i] = cusum[i-1] + nums[i-1];
        }
        
        // Find valid subarray via binary search and update minimal length
        for (int i = 1; i <= n; i++) {
            int toFind = cusum[i-1] + target;
            int bound = binary_search_lower_bound(cusum, i-1, n, toFind);
            
            if (bound > - 1) {
               length = bound - (i - 1);
                if (length < minLength) {
                    minLength = length;
                } 
            }
        }
        
        return (minLength == n + 1) ? 0 : minLength;
    }
    
private:
    int binary_search_lower_bound(vector<int>& nums, int start, 
                                int end, int target) {
        int left = start;
        int right = end;
        int mid;
        
        // [0, 1], target = 1
        //  l  r
        //  m
        
        while (left < right) {
            mid = left + (right - left)/2;  // while loop will ensure right >= left
            
            if (nums[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        
        return (nums[left] >= target) ? left : -1;
    }
};
```

#### Complexity Analysis
* Time complexity: $O(n \log n)$  
	It takes $O(n)$ time to compute cumulative sum and then followed by two for-loops--the first loop takes $O(n)$ for iterating over the array and the second loop takes $O(\log n)$ to find the subarray for each index using binary search. Therefore, the total time complexity is $O(n) + O(n \log n) = O(n \log n)$. 
* Space complexity: $O(n)$
	Additional $O(n)$ space for `cusum` vector.

### Approach - Slide Window
Since the array contains **only** positive elements (with the same sign), the problem can be solved using a sliding window with changing size moves along the array, increasing window size when `sum < target` and decreasing window size when `sum >= target`. The objective is to find the smallest window size with sum of values inside the window >= target. We can use two pointers to represent this slide window:

- The right pointer, `r`, represents the end position of the window. It will expand first by moving `r` forward
- The left pointer, `l`, represents the start position of the window. the window will be reduced by moving `l` forward until the sum inside the window is `< target`
The window size is `r - l + 1`. The minimal length will be update when the window expands and shrinks along the array. 


=== "Python"
    ```python
    class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        min_length = len(nums) + 1
        left = 0
        subarray_sum = 0
        for right in range(len(nums)):
            subarray_sum += nums[right]

            while subarray_sum >= target:
                min_length = min(min_length, right - left + 1)
                subarray_sum -= nums[left]
                left += 1

        if min_length > len(nums): # (1)
            return 0
        else:
            return min_length
    ```

    1. The `if/else` statement can be simplified as `return min_length % (len(nums) + 1)`


=== "C++"
    ```cpp
    class Solution {
    public:
        int minSubArrayLen(int target, vector<int>& nums) {
            typedef vector<int>::size_type vec_size;
            vec_size l = 0;
            vec_size r = 0;
            vec_size n = nums.size();
            long int sum = 0;
            vec_size length = n + 1;

            while (r < n) {
                sum += nums[r];

                while (sum >= target) {
                    if (r - l + 1 < length) {
                        length = r - l + 1; // r >= l (always)
                    }
                    sum -= nums[l++];
                }
                r++;
            }
            return (length == n + 1) ? 0 : length; // length % (n + 1)
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Each element can be visited at most twice, once by the right pointer and at most once by the left pointer. 
* Space complexity: $O(1)$  
	Only constant space is required for left, right, and sum.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Brute Force |  $O(n^2)$ 	   	   	| $O(1)$  
Approach - Binary Search |  $O(n \log n)$ 	   	   	| $O(n)$ 
Approach - Slide Window |  $O(n)$      		| $O(1)$

## Test