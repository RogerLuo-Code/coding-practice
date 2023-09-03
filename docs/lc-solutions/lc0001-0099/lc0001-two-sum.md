---
tags:
    - Array
    - Hash Table
---

# LC1. Two Sum
## Problem Description
[LeetCode Problem 1](https://leetcode.com/problems/two-sum/): Given an array of integers `nums` and an integer `target`, return _indices of the two numbers such that they add up to `target`_.

You may assume that each input would have **_exactly_ one solution**, and you may not use the _same_ element twice.

You can return the answer in any order.

## Clarification
- Target and numbers can be negative
- indices: zero-based or one-based
- sorted or unsorted?
- solution exsit for a given target and only one

## Assumption

## Solution
### Approach - Brute Force
Use two nested for-loops to loop trough all possible pairs and compute sum. If `sum == target`, return indices.

=== "Python"
    ```python
    class Solution:
        def twoSum(self, nums: List[int], target: int) -> List[int]:
            for i in range(len(nums)):
                for j in range(i + 1, len(nums)):
                    if nums[i] + nums[j] == target:
                        return [i, j]
    ```

=== "C++"
    ```cpp
    class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            for (int i = 0; i < nums.size(); i++) {
                for (int j = i + 1; j < nums.size(); j++) {
                    if ((nums[i] + nums[j]) == target) {
                        return {i, j};
                    }
                }
            }
            return {};
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n^2)$  
	Since using two nested for-loops, the time complexity is $O(n^2)$.  
* Space complexity: $O(1)$  
	The space required doesn't depend on the size of the input array. So only constant space is used. 

### Approach - Two-Pass Hash Table 
To improve the runtime complexity, we can use a hash table to efficiently check whether `target - num` exists for any `num` in the array and get its index if exists. 

We can reduce the lookup time from $O(n)$ to $O(1)$ by trading space for time. Note that lookup in a hash table should be amortized $O(1)$ time as long as the hash function was chosen carefully. Otherwise, if a collision occurred, a lookup could degenerate to $O(n)$ time.

We can use two pass to solve the problem:

1. Add each element's value as a key and its index as a value to the hash table
2. Check if each element's complement, `target - num` exists in the hash table. If exists, return current index and its complement's index. **Note** that: make sure the complement is not num itself.

=== "C++"
    ```cpp
    class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            unordered_map<int, int> seen;
            for (int i = 0; i < nums.size(); i++) {
                seen[nums[i]] = i;
            }

            for (int i = 0; i < nums.size(); i++) {
                int complement = target - nums[i];
                if (seen.find(complement) != seen.end() && seen[complement] != i) {
                    return {i, seen[complement]};
                }
            }

            return {};
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	It takes $O(n)$ to update the hash map and another $O(n)$ to check whether complement exists. So the total time complexity is $O(n) = O(n) + O(n)$. 
* Space complexity: $O(n)$  
	The hash table takes at most $O(n)$ space. 

### Approach - Hash Table
We need to find 2 numbers `a` and `b` so that `a + b == target`. That means for any given `a`, we need to find `b` with `b = target - a`. To effectively find `b`, we can use a hash table to store previous `<num, index>`, using array element as key and its index as value. Then for each `a`, search for `target - a` in the table.  If it is found and is not the same element as `a`, then we are done. 

Note that each time we search for `target - a` first and then add update hash table, so we will not hit the same element twice. Even there are duplicated numbers, hash map stores the recent one, which is still the valid answer. 

=== "Python"
    ```python
    class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        value_index_map = {}
        for i in range(len(nums)):
            complement = target - nums[i]
            if complement in value_index_map:
                return [value_index_map[complement], i]

            value_index_map[nums[i]] = i # (1)
    ```

    1. If encounter the same number, stores the most recent one

=== "C++"
    ```cpp
    class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            unordered_map<int, int> seen;
            for (int i = 0; i < nums.size(); i++) {
                int complement = target - nums[i];
                if (seen.find(complement) != seen.end()) {
                    return {seen[complement], i};
                }
                seen[nums[i]] = i;
            }
            return {};
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Traverse the whole array once and each lookup in the hash table costs only $O(1)$ time. So the total time complexity is $O(n)$.  
* Space complexity: $O(n)$  
	The hash table stores at most $n$ elements. Therefore the space complexity is $O(n)$.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Brute Force |  $O(n^2)$ 	   	   	| $O(1)$  
Approach - Two-Pass Hash Table |  $O(n)$ 	   	   	| $O(n)$  
Approach - Hash Table |  $O(n)$      		| $O(n)$

## Test