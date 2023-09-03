---
tags:
    - Array
    - Two Pointers
    - Prefix Sum
    - Hash Table
---

# LC325. Maximum Size Subarray Sum Equals k
## Problem Description
[LeetCode Problem 325](https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/): Given an integer array `nums` and an integer `k`, return _the maximum length of a subarray that sums to_ `k`. If there is not one, return `0` instead.

## Clarification
- Find the maximum length of subarray with `sum == k`
- If doesn't exist, return 0
- Include both positive and negative values

## Assumption
- Sum of subarray won't cause integer overflow

## Solution
The general idea is to
- detect subarrays with sum `k` 
- find the length of the longest subarray with sum `k`
- 
The straightforward solution is using brute force with two for-loops to find all possible subarrays, which has $O(n^2)$ time complexity. A better approach is to use prefix sum and hash map to detect subarray with sum `k` more efficiently, which will reduce time complexity to $O(n)$ but will use $O(n)$ space. 

### Approach - Prefix Sum + Hash Map
A better approach to solve this problem is to use prefix sum and hash map. The [prefix sum](https://en.wikipedia.org/wiki/Prefix_sum) is the cumulative sum. The original array `nums = [1, 2, 2, 3]` can be converted to the prefix sum array `prefix = [1, 3, 5, 8]`. The prefix sum has the following properties:
- `prefix[j] - prefix[i]` represents the sum of the subarray from `i+1` to `j` , where `prefix[i]` is the sum of all the elements from `0` to `i` (inclusive). 
- If `prefixSum[i] == prefixSum[j]`, then the sum of subarray from `i+1` to `j` equals `0` 
With above mentioned property, we can
- Store previously seen prefix sums and their indices in a hash map, `map<prefixSum, index>` 
	- No need to create a prefix sum array. Instead, use an integer variable to keep track of the prefix sum
	- If running into duplicates (due to negative numbers), only update the index in the hash map when it doesn't exist (i.e., `maps.find(prefixSum) == map.end()`), which keep the index as far to the left as possible, since we want the longest subarray. 
- Check if `prefix[i] == k`, then the sum of the subarray from `0` to `i` is `k`
	- Check it directly using if statement
	- Or initialize the hash map with a key (prefix sum) of `0` corresponding to a value of `-1` (index)
- Check if `prefix[i] - k` has already been seen. If so (e.g., `prefix[i] - k = prefix[j]`), the sum of the subarray from `i+1` to `j` is `k`
- Find the length of subarray using the stored index and current index and update longest length

Note: it's better replace integer with `vector<int>::size_type` for indexing.

```cpp
class Solution {
public:
    vector<int>::size_type maxSubArrayLen(vector<int>& nums, int k) {
        typedef vector<int>::size_type vec_size;
        unordered_map<long, vec_size> sumIndexMap; 
        
        long int sum = 0;
        vec_size length = 0;
        vec_size maxLength = 0;
        
        for (vec_size i = 0; i < nums.size(); i++) {
            sum += nums[i];
            
            // Check if cumulative sum == k
            if (sum == k) {
                if (i + 1 > maxLength) {
                    maxLength = i + 1;
                }
            }
            
            // If any subarry with summmation == sum - k, update maxlenght
            if (sumIndexMap.find(sum - k) != sumIndexMap.end()) {
                length = i - sumIndexMap[sum - k];
                if (length > maxLength) {
                    maxLength = length;
                }
            }
            
            // Add the first appeared sum to hashmap for computing max length later
            if (sumIndexMap.find(sum) == sumIndexMap.end()) {
                sumIndexMap[sum] = i;
            }
        }
        
        return maxLength;
        
    }
};
```

#### Complexity Analysis
* Time complexity: $O(n)$  
	We iterate the array with one pass. Inside the for-loop, each code block is $O(1)$. All hash map operators are $O(1)$.  
* Space complexity: $O(n)$
	The hash map can potential hold as many key-value pairs as numbers in `nums`. An example of this when there are **NO** **negative** numbers in the array.
