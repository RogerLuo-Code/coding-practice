---
tags:
    - Array
    - Two Pointers
    - Sliding Window
---

# LC487. Max Consecutive Ones II
## Problem Description
[LeetCode Problem 487](https://leetcode.com/problems/max-consecutive-ones-ii/): Given a binary array `nums`, return _the maximum number of consecutive_ `1`_'s in the array if you can flip at most one_ `0`.

**Follow up:** What if the input numbers come in one by one as an infinite stream? In other words, you can't store all numbers coming from the stream as it's too large to hold in memory. Could you solve it efficiently?

### Similar questions
- [lc0485-max-consecutive-ones](lc0485-max-consecutive-ones.md)
- [lc1004-max-consecutive-ones-iii](../lc1000-1099/lc1004-max-consecutive-ones-iii.md)

## Clarification
- Binary array: data type is bool or integer?
- Re-phrase the question: find the sequence with most 1s but with at most one 0

## Assumption
- The maximum number of consecutive 1 can be represented by an integer instead of unsigned integer.  

## Solution
There are two different ways to solve the problem efficiently: 
- Use **two number**, one stores number of consecutive 1s and the other store a sequence with at most 1 zero, and update them to find the largest value.
- Use **sliding window** to find the longest sequence with at most 1 zero.
- 
### Approach - Two Number
[@sunnyleevip](https://leetcode.com/problems/max-consecutive-ones-ii/discuss/451116/C%2B%2B-one-pass-or-O(1)-space-or-concise) shared a method using two numbers:
- One stores the current consecutive 1s 
- The other stores the case of only a 0 between 1s
Update these two numbers:
- When `num == 1`,  increase both numbers
- When `num == 0`, set `nOnesAndZero = nOnes + 1` and reset `nOnes`. This is a really smart way to do. My initial submission has to use two addition bool variables and logics to achieve the similar results.

```cpp
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int nOnesMax = 0;
        int nOnes = 0; // number of consecutive ones
        int nOnesAndZero = 0; // number of consecutive ones + 1 zero

        for (int num : nums) {
            if (num == 1) {
                nOnes++;
                nOnesAndZero++;
            }
            else {
                nOnesAndZero = nOnes + 1;
                nOnes = 0;
            }

            if (nOnesAndZero > nOnesMax) {
                nOnesMax = nOnesAndZero;
            }
        }
        return nOnesMax;
    }
};
```

My initial submission achieves the similar results but using a little complicated logics using two bool variables. 
```cpp
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int nMaxOne = 0;
        int nOneP1 = 0;
        int nOneP2 = 0;
        bool flipP1 = true; // true: flip from zero to one for pointer 1
        bool flipP2 = false; // true: flip from zero to one for pointer 2

        for (int num : nums) {
            if (num == 1) {
                nOneP1++;
                nOneP2++;
            }
            else {
                if (flipP1) {
                    // 0 --> 1
                    nOneP1++;
                }
                else {
                    if (nOneP1 > nMaxOne) {
                        nMaxOne = nOneP1;
                    }
                    nOneP1 = 0; 
                }

                if (flipP2) {
                    // 0 --> 1
                    nOneP2++;
                }
                else {
                    if (nOneP2 > nMaxOne) {
                        nMaxOne = nOneP2;
                    }
                    nOneP2 = 0;
                }

                flipP1 = !flipP1;
                flipP2 = !flipP2;
            }
        }

        if (nOneP1 > nMaxOne) {
            nMaxOne = nOneP1;
        }

        if (nOneP2 > nMaxOne) {
            nMaxOne = nOneP2;
        }

        return nMaxOne;
    }
};
```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Iterate all elements of the array once.   
* Space complexity: $O(1)$
	Only use 3 local variables and therefore constant space complexity. 

### Approach - Sliding Window
Use a sliding window (left and right pointers) to find the longest sequence with at most 1 zero:
- **Expand** the window by moving the **right** pointer forward until reaching invalid **window**, more than one zero in the current window
- **Shrink** the window by moving the **left** pointer forward until having a **valid** window, one of fewer 0's in the current window

=== "Python"
    ```python
    class Solution:
    def findMaxConsecutiveOnes(self, nums: List[int]) -> int:
        idx_left = 0
        n_max = 0
        n_zero = 0

        for idx_right in range(len(nums)):
            if nums[idx_right] == 0:
                n_zero += 1

            while n_zero >= 2:
                if nums[idx_left] == 0:
                    n_zero -= 1

                idx_left += 1

            n_max = max(n_max, idx_right - idx_left + 1)

        return n_max
    ```

=== "C++"
    ```cpp
    class Solution {
    public:
        int findMaxConsecutiveOnes(vector<int>& nums) {
            int nMaxOnes = 0;
            int left = 0;
            int right = 0;
            int nZerosWindow = 0; // number of zeros within a window
            int nElementsWindow = 0;

            // Keep window in bounds
            while (right < nums.size()) {

                // When expanding to right, update number of zeros in the window
                if (nums[right] == 0) {
                    nZerosWindow++;
                }

                // If window is invalid, contract from left
                while (nZerosWindow == 2) {
                    if (nums[left] == 0) {
                        nZerosWindow--;
                    }
                    left++;
                }

                // Update result
                nElementsWindow = right - left + 1;
                if (nElementsWindow > nMaxOnes) {
                    nMaxOnes = nElementsWindow;
                }

                // Expand window to right
                right++;
            }
            return nMaxOnes;
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Both left and right pointers only move forward and traverse at most $n$ steps. Therefore, the time complexity is $O(n)$.  
* Space complexity: $O(1)$
	Only use several variables (pointers and variables to store numbers). The number of variables are constant and do not change with the size of the input.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity 
------------ | --------------- 	| ---------------- 
Approach - two number |  $O(n)$ 	   	   	| $O(1)$     | 
Approach - sliding window |  $O(n)$      	| $O(1)$   |

## Test