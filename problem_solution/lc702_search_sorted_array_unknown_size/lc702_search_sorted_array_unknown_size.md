# LeetCode Problem 702 - Search in a Sorted Array of Unknown Size

## Problem Description
[LeetCode Problem 702](https:leetcode.com/problems/search-in-a-sorted-array-of-unknown-size/) Given an integer array sorted in ascending order, write a function to search target in nums.  If target exists, then return its index, otherwise return -1. However, the array size is unknown to you. You may only access the array using an ArrayReader interface, where ArrayReader.get(k) returns the element of the array at index k (0-indexed).

You may assume all integers in the array are less than 10000, and if you access the array out of bounds, ArrayReader.get will return 2147483647.

## Analysis
* Clairification:
  - Data type? integer
  - Sorted vs. unsorted?
  - Ascending order or descending order?
  - ArrayReader question:
      - What value to return when element doesn't exist?
      - zero-based indexing?
  - How large the array size could be? Exceed the max value allowed of integer?
  - Any duplicates? what to return if target has duplicates
* Go through exampels
* Solution: 
  - Assumption: the array size < Integer.MAX_VALUE
  - Input/output: 
      - Input: ArrayReader, int
      - output: int
  - Corner case: empty array, array size > Integer.MAX_VALUE, target doesn't exist
  - Algorithm: Find search boundary and then use binary search
  - Time/space complexity
* Coding
* Test
  - Test corner case
  - Test general case


## Approach
### Algorithm
Since the array is **sorted**, we can 
* Find left and right boundaries  
If target is outside the boundaries, then it should be on the right and extend the boundaries `left = right` and `right = right * 2`. Some considerations:  
    - End the search when `reader.get(right) >= target` or access the array out of bounds
    - `right = right * 2` vs. `right = right * 10`
* Perform classic binary search within the boundaries  


### Implementation
```java
class Solution {
    public int search(ArrayReader reader, int target) {
        int left = 0;
        int right = 1;
        
        // Search boundaries [Left, Right] to include target
        while ((reader.get(right) < target)) {
            if (reader.get(right) == 2147483647)
                return -1;
            
            left = right;
            if (right < Integer.MAX_VALUE/2)   
                right *= 2;  // or right <<= 1, double right until finding the right boundary (i.e., right > target)
            else{
                right = Integer.MAX_VALUE;
                break;
            }
        }
        // left = right/2;
        
        int mid;
        int val;  // value of reader.get(mid)
        // classic bineary search
        while (left <= right) {
            mid = left + (right - left)/2;
            
            val = reader.get(mid);
            if (val == 2147483647)
                right = mid - 1;
            else if (target < val)
                right = mid - 1;
            else if (target > val)
                left = mid + 1;
            else 
                return mid;
        }
        
        return -1; 
    }
}
```
### Complexity Analysis
* **Time complexity**: $\mathcal{O}(\log T)$, where $T$ is an index of target value   
There are two operations:
  - Find search boundaries: the boundary is $2^k < T \leq 2^{k+1}$ and needs $k = \log T$ steps to find the boundaries 
  - Binaries search within the boundaries: There are $2^{k+1} - 2^k = 2^k = 2^{\log T} = T$ elements. It takes $\log T$ steps for bineary search.  
The total steps are $\log T + \log T$. Therefore, the time complexity is $\mathcal{O}(\log T)$  

* **Space complexity**: $\mathcal{O}(1)$, since it only update serveral variables in finding boundaries and performing bineary search. 

**Alternative**: use `right *= 10` instead of `right *= 2`  
- Find search boundaries: the boundary is $10^k < T \leq 10^{k+1}$ and needs $k = \log_{10} T$ steps to find the boundaries    
- Binaries search within the boundaries: There are $10^{k+1} - 10^k = 9*10^k = 9*10^{\log_{10} T} = 9T$ elements. It takes $\log_2 9T$ steps for bineary search.  

Comparison between `right *= 2` and `right *= 10`:  
|   | Find Boundaries  |  Binary Search  
|------|------|-----  
| right *= 2 | $\log_2 T$ | $\log_2 T$  
| right *= 10 | $\log_{10} T$ | $\log_2 9T$ 

Which one is better? When $T > 23$, 10 times update is faster. However, even T is really big (e.g. $10^{30}$), the  difference between 10 times and 2 times is still small (69 steps less). So using either one in implementation is fine.

10 times - 2 times   
= $\log_{10} T + log_2 9T - \log_2T - \log_2 T$  
= $\log_{10} T - \log_2T + log_2 9T - \log_2 T$  
= $\log_{10} T - \log_2T + log_2 9$

$\log_{10} 24 - \log_2 24 + log_2 9 = - 0.035$
$\log_{10} 10^{30} - \log_2 10^{30} + log_2 9 = - 68.81$
