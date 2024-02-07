---
tags:
    - Binary Search
---

# LC35. Search Insert Position
## Problem Description
[LeetCode Problem 35](https://leetcode.com/problems/search-insert-position/): Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You must write an algorithm with `O(log n)` runtime complexity.

## Clarification
- sorted array
- distinct integers (no duplicates)
- find insert position (index?)

## Assumption

## Solution
### Approach - Binary Search
Since the array is sorted, the problem can be solved by using Binary Search. The key part is to understand what is searching for. Here is the insert position (not the target). The Search range is the range of array, $[0, n − 1]$. [@Zhengguan Li](https://leetcode.com/problems/search-insert-position/solutions/249092/Come-on-forget-the-binary-search-patterntemplate!-Try-understand-it!/) provide some good explanations.

- If `nums[mid] == target`, return `mid`.
- If `target > nums[mid]`, `mid` is not the potential insert position while
`mid + 1` is. so `left = mid + 1`.
- If `target < nums[mid]`, `mid` is the potential insert position and `right = mid`.

To determine the while loop condition, we can use two-element case
to test our left/right operations: `left = mid + 1` and `right = mid`. We can see that it can be safely reduced to one element but not zero. So we need end the while loop when there is only one element left, i.e., `while(left < right)`.

=== "Python"
    ```python
    class Solution:
        def searchInsert(self, nums: List[int], target: int) -> int:
            left, right = 0, len(nums) - 1

            while left < right:
                mid = (left + right) // 2

                if target == nums[mid]:
                    return mid
                elif target < nums[mid]:
                    right = mid  # (1)
                else:
                    left = mid + 1

            if nums[left] < target:
                return left + 1
            else:
                return left
    ```

    1. Not mid - 1, since mid could be a potential insert position

=== "C++"
    ```c++
    class Solution {
    public:
        int searchInsert(vector<int>& nums, int target) {
            if (nums.empty()) {
                return -1;
            }

            int left = 0;
            int right = nums.size() - 1;
            int mid;

            while (left < right) {
                mid = left + (right - left)/2;

                if (target == nums[mid]) {
                    return mid;
                }
                else if (target > nums[mid]) {
                    left = mid + 1;
                }
                else {
                    right = mid;
                }
            }

            // 1 element left at the end
            // post-processing
            return nums[left] < target ? left + 1 : left;
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(\log n)$  
	Since using binary search, the time complexity is $O(\log n)$  
* Space complexity: $O(1)$  
	Only use limited variables for binary search.

## Test