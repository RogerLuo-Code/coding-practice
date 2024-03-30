---
tags:
- Sorting
- Two Pointers
- Binary Search
---

# LC1099. Two Sum Less Than K
## Problem Description
[LeetCode Problem 1099](https://leetcode.com/problems/two-sum-less-than-k): Given an array nums of integers and integer k, return the maximum sum such that there exists i < j with nums[i] + nums[j] = sum and sum < k. If no i, j exist satisfying this equation, return -1.

## Clarification

## Assumption

## Solution
### Approach - Two Pointers
Sort the array first. Then we can use two pointers, `left` pointers starts from the first element and `right` pointer starts from the last element, to go through the array.

- If `sum < k`, increase the lower pointer `left`
- If `sum >= k`, decrease the upper pointer `right`

Continue until two pointers meet. Explore and track all possible sum that < k.

=== "Python"
    ```python
    class Solution:
        def twoSumLessThanK(self, nums: List[int], k: int) -> int:
            nums.sort()  # Time: O(n \logn)
            max_sum = -1
            left, right = 0, len(nums) - 1
            while left < right:
                sum = nums[left] + nums[right]
                if (sum < k):
                    max_sum = max(max_sum, sum)
                    left += 1
                else:
                    right -= 1
            return max_sum
    ```

#### Complexity Analysis
* Time complexity: $O(n \log n)$  
Sorting the array takes $O(n \log n)$. Tracking sum using two-pointers approach takes $O(n)$. SO the total time complexity is $O(n \log n)$
* Space complexity: $O(\log n)$  or $O(n)$  
Depends on the implementation of the sorting algorithm.

### Approach - Binary Search
Instead of using two pointers, we can iterate through each element `nums[i]` and use binary search to find the a complement value `nums[j] < k - nums[i]`. 

Notice that Python `bisect_left` returns the `insert point` for the searched value, i.e., the first element >= `k - nums[i]`. Since the sum < k, we consider the element at `insert point` - 1.

=== "Python"
    ```python
    class Solution:
        def twoSumLessThanK(self, nums: List[int], k: int) -> int:
            nums.sort()

            max_sum = -1
            for left in range(len(nums)):
                right = bisect.bisect_left(nums, k - nums[left], left + 1) - 1
                if right > left:
                    max_sum = max(max_sum, nums[left] + nums[right])

            return max_sum
    ```

#### Complexity Analysis
* Time complexity: $O(n \log n)$  
Sorting takes $O(n \log n)$ and iterate with binary search takes $O(n \log n)$.
* Space complexity: $O(\log n)$ or $O(n)$  
Depend on the implementation of the sorting algorithm.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  |
------------ | --------------- 	| ---------------- |
Approach - Two Pointers |  $O(n \log n)$ 	   	   	| $O(\log)$ or $O(n)$ |
Approach - Binary Search |  $O(n \log n)$      		| $O(\log)$ or $O(n)$ |

## Test