---
tags:
    - Array
    - Sliding Window
---

# LC1004. Max Consecutive Ones III
## Problem Description
[LeetCode Problem 1004](https://leetcode.com/problems/max-consecutive-ones-iii/solution/): Given a binary array `nums` and an integer `k`, return _the maximum number of consecutive_ `1`_'s in the array if you can flip at most_ `k` `0`'s.

Note integer type can be rest to 0

### Similar Questions:
- [lc0485-max-consecutive-ones](../lc0400-0499/lc0485-max-consecutive-ones.md)
- [lc0487-max-consecutive-ones-ii](../lc0400-0499/lc0487-max-consecutive-ones-ii.md)

## Clarification
- Binary tree of integer type?

## Assumption
- Integer type can cover subarray left and right indices

## Solution
### Approach - Slide Window
Use a sliding window (left and right pointers) to find the longest sequence with at most k zeros:
- **Expand** the window by moving the **right** pointer forward until reaching invalid **window**, more than `k` zeros in the current window
- **Shrink** the window by moving the **left** pointer forward until having a **valid** window, one of fewer 0's in the current window

=== "Python"
    ```python
    class Solution: # (1)
    def longestOnes(self, nums: List[int], k: int) -> int:
        left = 0

        for right in range(len(nums)):
            if nums[right] == 0:
                k -= 1

            if k < 0:
                if nums[left] == 0:
                    k += 1
                left += 1 # (2)

        return right - left + 1
    ```

    1. This solution is proposed by [lee215](https://leetcode.com/problems/max-consecutive-ones-iii/solutions/247564/java-c-python-sliding-window/) and further explained well by [hckrtst](https://leetcode.com/problems/max-consecutive-ones-iii/solutions/719833/python3-sliding-window-with-clear-example-explains-why-the-soln-works/)
    2. left and right move together when max window is found. The max window will be changed.

=== "Python - my solution"
    ```python
    class Solution:
    def longestOnes(self, nums: List[int], k: int) -> int:
        left = 0
        n_zeros = 0
        n_max_1s = 0

        for right in range(len(nums)):
            if nums[right] == 0:
                n_zeros += 1

            while n_zeros > k:
                if nums[left] == 0:
                    n_zeros -= 1
                left += 1

            n_max_1s = max(n_max_1s, right - left + 1)

        return n_max_1s
    ```

=== "C++"
    ```cpp
    class Solution {
    public:
        int longestOnes(vector<int>& nums, int k) {
            int nOneKZero = 0;
            int length = 0;
            int nZeroInWindow = 0;
            int left = 0;

            for (int right = 0; right < nums.size(); right++) {
                // When expanding to right, update number of zeros in the window
                if (nums[right] == 0) {
                    nZeroInWindow++;
                }

                // If window is invalid, shrink from left
                while (nZeroInWindow > k) {
                    if (nums[left] == 0) {
                        nZeroInWindow--;
                    }
                    left++;
                }

                // Update length
                length = right - left + 1;
                nOneKZero = max(nOneKZero, length);
            }
            return nOneKZero;
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	In the worst case, both left and right pointers iterate through the element (total twice). It is still $O(n)$ time complexity.
* Space complexity: $O(1)$  
	Only use several local variables.

## Test
