---
tags:
    - Array
	- Two Pointers
	- Sliding Window
    - Hash Table
---


# LC167. Two Sum II - Input Array Is Sorted
## Problem Description
[LeetCode Problem 167](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/): Given a **1-indexed** array of integers `numbers` that is already **_sorted in non-decreasing order_**, find two numbers such that they add up to a specific `target` number. Let these two numbers be `numbers[index1]` and `numbers[index2]` where `1 <= index1 < index2 < numbers.length`.

Return _the indices of the two numbers,_ `index1` _and_ `index2`_, **added by one** as an integer array_ `[index1, index2]` _of length 2._

The tests are generated such that there is **exactly one solution**. You **may not** use the same element twice.

Your solution must use only constant extra space.

## Clarification
- Sorted array
- there is **exactly one solution**
- `0-indexed` or `1-indexed`

## Assumption

## Solution
### Approach - Sliding Window
Since the array is sorted, the sum of two numbers from left half < the sum of two numbers from right. We can use sliding window to find the target by 

- Move closer to the right if current sum < target  
- Move closer to the left if current sum > target

??? tip

    Initialize sliding window left pointer with the first position and right pointer with the last position of the array

=== "Python"
    ```python
    class Solution:
        def twoSum(self, numbers: List[int], target: int) -> List[int]:
            left = 0
            right = len(numbers) - 1

            while left < right:
                sum = numbers[left] + numbers[right]
                if sum == target:
                    return [left + 1, right + 1] # (1)
                elif sum < target:
                    left += 1
                else:
                    right -= 1

            return [-1, -1] # (2)
    ```

    1. Add one for `1-indexed` array
    2. This is for the general case, the solution doesn't exist. It can be removed for this problem, since there is **exactly one solution**

#### Complexity Analysis
* Time complexity: $O(n)$  
	Go through the array at most once.
* Space complexity: $O(1)$  
	Just use two index variables

### Approach - Binary Search
Since the array is sorted, we can use binary search to effectively find `target - val` if exists for any given `val`. Iterate through the array and use binary search to find `target - val`.

=== "Python"
    ```python
    class Solution:
        def twoSum(self, numbers: List[int], target: int) -> List[int]:
            for i, num in enumerate(numbers):
                j = bisect.bisect_left(numbers, target - num, lo=i+1, hi=len(numbers)-1)
                if j != len(numbers) and numbers[j] == target - num:
                    return [i + 1, j + 1] # (1)
    ```

    1. Convert from 0-indexed to 1-indexed number

#### Complexity Analysis
* Time complexity: $O(n \log n)$  
    Iterate through the array once.  
* Space complexity: $O(1)$  
	Only using two index variables.

### Approach - Hash Map
Iterate through the array and store the `(value, index)`` in hash map. For any new value, check whether `target - value` exists in the hashmap. If exists, return indices.
=== "Python"
    ```python
    class Solution:
        def twoSum(self, numbers: List[int], target: int) -> List[int]:
            value_index_map = {}

            for i, num in enumerate(numbers):
                if target - num in value_index_map:
                    return [value_index_map[target - num] + 1, i + 1]

                value_index_map[num] = i
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
    Iterate through the array once.  
* Space complexity: $O(n)$  
	Use hashmap to store at most $n-1$ items


### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Sliding Window |  $O(n)$ 	   	   	| $O(1)$  
Approach - Binary Search |  $O(n \log n)$      		| $O(1)$
Approach - Hash Map |  $O(n)$      		| $O(n)$

## Test