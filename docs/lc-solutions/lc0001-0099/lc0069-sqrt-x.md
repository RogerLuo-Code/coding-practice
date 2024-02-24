---
tags:
- Binary Search
---

# LC69. Sqrt(x)
## Problem Description
[LeetCode Problem 69](https://leetcode.com/problems/sqrtx/): Given a non-negative integer `x`, return _the square root of_ `x` _rounded down to the nearest integer_. The returned integer should be **non-negative** as well.

You **must not use** any built-in exponent function or operator.

- For example, do not use `pow(x, 0.5)` in c++ or `x ** 0.5` in python.

## Clarification
- non-negative
- square root of x in integer
- round it down

## Assumption

## Solution
### Approach - Binary Search
Mathematically, `i = sqrt(x)` can be viewed as `x = i * i`. The problem is to find an integer `i` in the search space `[1, x]` such that `i * i <= x` and `(i + 1) * (i + 1) > x`. If `i * i > x`, we can exclude values larger than or equal to `i`. If `i * i < x`, we can exclude the value smaller than i. With this property, we can solve this problem using binary search. There are somethings to pay attention to:
• overflow caused by `i * i` in the evaluation `i * i > x`;
• can not simply check `i == x/i` to determine whether the answer is found since there may be multiple values satisfied this equations due to integer division.

=== "Python"
    ```python
    class Solution:
        def mySqrt(self, x: int) -> int:
            left, right = 0, x

            while left < right - 1:
                mid = (left + right) // 2
                mid_square = mid * mid
                if x == mid_square:
                    return mid
                elif x < mid_square:
                    right = mid - 1
                else:
                    left = mid

            if right * right <= x:
                return right
            else:
                return left
    ```

=== "C++"
    ```c++
    class Solution {
    public:
        int mySqrt(int x) {
            if (x <= 1) {
                return x;
            }

            int left = 1;
            int right = x;
            int mid;

            while (left <= right) {
                mid = left + (right - left)/2;

                if ((mid <= x/mid) && ((mid + 1) > x/(mid + 1))) {
                    return mid;
                }
                else if (mid > x/mid) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1; 
                }
            }
            return -1;
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(\log n)$  
Since using the binary search, the time complexity is $O(\log n)$.
* Space complexity: $O(1)$  
Only use several variables.


## Test
- x <= 1 case