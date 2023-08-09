---
tags:
    - Array
    - Two Pointers
    - Sliding Window
---

# LC485. Max Consecutive Ones
## Problem Description
[LeetCode Problem 485](https://leetcode.com/problems/max-consecutive-ones/): Given a binary array `nums`, return _the maximum number of consecutive_ `1`_'s in the array_.

### Similar questions
- [lc0487-max-consecutive-ones-ii](lc0487-max-consecutive-ones-ii.md)
- [lc1004-max-consecutive-ones-iii](../lc1000-1099/lc1004-max-consecutive-ones-iii.md)

## Clarification
- Binary array: bool or int data type? - Find the maximum number of consecutive 1's

## Assumption

## Solution
### Approach - One Pass
We keep a count of the number of 1's encountered.
- Increase the count when encountering 1  
- Reset to 0 when encountering 0
update max count accordingly.

=== "Python"
    ```python
    class Solution:
    def findMaxConsecutiveOnes(self, nums: List[int]) -> int:
        n_consecutive_1s = 0
        max_n_consecutive_1s = 0

        for num in nums:
            if num == 1:
                n_consecutive_1s += 1
            else:
                n_consecutive_1s = 0

            max_n_consecutive_1s = max(max_n_consecutive_1s, n_consecutive_1s)

        return max_n_consecutive_1s
    ```

=== "C++"
    ```c++
    class Solution {
    public:
        int findMaxConsecutiveOnes(vector<int>& nums) {
            int count = 0;
            int maxCount = 0;

            for (int num : nums) {
                if (num == 1) {
                    count++;
                }
                else {
                    count = 0;
                }
                maxCount = max(count, maxCount);
            }

            return maxCount;
        }
    };
    ```

### Approach - Sliding Window
=== "Python"
    ```python
    class Solution:
    def findMaxConsecutiveOnes(self, nums: List[int]) -> int:
        idx_left = 0
        max_n_consecutive_1s = 0

        for idx_right in range(len(nums)):
            if nums[idx_right] == 1:
                n_consective_1s = idx_right - idx_left + 1
                max_n_consecutive_1s = max(n_consective_1s, max_n_consecutive_1s)
            else:
                idx_left = idx_right + 1

        return max_n_consecutive_1s
    ```

=== "C++"
    ```cpp
    class Solution {
    public:
        int findMaxConsecutiveOnes(vector<int>& nums) {
            typedef vector<int>::size_type vec_size;
            vec_size n = nums.size();
            vec_size left = 0; // left pointer of the sliding window
            vec_size right = 0;  // right pointer of the sliding window
            vec_size nZeroInWindow = 0; // number of zeros in the window 
            vec_size count = 0; // number of consecutive 1s in a sliding window
            vec_size maxCount = 0; // max number of consecutive 1s

            while (right < n) {
                if (nums[right] == 0) {
                    nZeroInWindow++;
                }

                while (nZeroInWindow > 0) {
                    if (nums[left] == 0) {
                        nZeroInWindow--;
                    }
                    left++;
                }

                if (right >= left) {
                    count = right - left + 1;
                    if (count > maxCount) {
                        maxCount = count;
                    }
                }

                right++;
            }

            return maxCount;

        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Iterate the array once.  
* Space complexity: $O(1)$
	Only use two variables