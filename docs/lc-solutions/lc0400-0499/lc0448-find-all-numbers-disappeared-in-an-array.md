---
tags:
    - Array
    - Hash Table
---

# LC448. Find All Numbers Disappeared in an Array
## Problem Description
[LeetCode Problem 448](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/): Given an array `nums` of `n` integers where `nums[i]` is in the range `[1, n]`, return _an array of all the integers in the range_ `[1, n]` _that do not appear in_ `nums`.

## Clarification
- Can the input array be modified? Different solutions

## Assumption

## Solution
[@archit91 shares a good summary](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/discuss/1583736/C%2B%2BPython-All-6-Solutions-w-Explanations-or-Binary-Search%2B-Hashset-%2B-2x-O(1)-Space-Approachf) on different ways to solve this problem. There are two general approaches to solve this problem:   

- Use additional data structure (e.g. hashset or bool array) to store the information of whether number appears  
- Modify original array (e.g. swap or negation) to store the information of whether numbers appear  

### Approach - Hashset
Initialize a hashset with all elements from `nums` and then iterate over the range `[1, n]` and only add elements that are not present in the hashset to the `ans`. 

=== "Python"
    ```python
    class Solution:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        nums_unique = set(nums)
        return [i for i in range(1, len(nums) + 1) if i not in nums_unique]
    ```

=== "C++"
    ```cpp
    class Solution {
    public:
        vector<int> findDisappearedNumbers(vector<int>& nums) {
            unordered_set<int> s(nums.begin(), nums.end());
            vector<int> ans(nums.size() - s.size());

            // Note check range [1, n] so i strarts from 1 not 0, and <= n not < n
            for (int i = 1, j = 0; i <= nums.size(); i++) {
                if (s.count(i) == 0) {
                    ans[j++] = i;
                }
            }
            return ans;
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	It requires $O(n)$ time to insert all elements into hashset and another $O(n)$ time to iterate over range, check whether element in the hashset and insert elements not present into `ans`. Note that the average time complexity of checking existence in a hashset is O(1). So the total time complexity of $O(n) = O(n) + O(n)$.  
* Space complexity: $O(n)$
	Store at most $n$ elements in the hashset. 


### Approach - Mark as Seen by Negation
We can map each element of the range `[1, n]` to the indices of `nums` from `[0, n-1]`.  Then making the element `nums[nums[i] - 1]` negative to indicate `nums[i]` exist. Need to take care that some elements may already be negative.

=== "Python"
    ```python
    class Solution:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        # index: 0, 1, 2, ..., n - 1
        # value: 1, 2, 3, ..., n
        for i in range(len(nums)):
            idx = abs(nums[i]) - 1 # (1)
            if nums[idx] > 0:
                nums[idx] *= -1

        return [i + 1 for i in range(len(nums)) if nums[i] > 0]
    ```

    1. Add `abs`` since the value may be flipped before and negative

=== "C++"
    ```cpp
    class Solution {
    public:
        vector<int> findDisappearedNumbers(vector<int>& nums) {
            vector<int> ans;

            for (int c : nums) {
                int i = abs(c) - 1;
                if (nums[i] > 0) nums[i] *= -1;
            }

            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] > 0) ans.push_back(i+1);  // nums[i] > 0 means i+1 isn't present
            }

            return ans;
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Iterate nums twice and each takes $O(n)$ time. 
* Space complexity: $O(1)$  
	Only constant extra space is used except for the output `ans`. The original array can be easily restored by changing negative values to positive ones. 

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Hashset |  $O(n)$ 	   	   	| $O(n)$  
Approach - Masrk as Seen by Negation |  $O(n)$      		| $O(1)$

## Test
