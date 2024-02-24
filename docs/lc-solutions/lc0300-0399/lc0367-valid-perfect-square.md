---
tags:
- Binary Search
---

# LC367. Valid Perfect Square
## Problem Description
[LeetCode Problem xx](https://leetcode.com/problems/valid-perfect-square/): Given a positive integer num, return `true` _if_ `num` _is a perfect square or_ `false` _otherwise_.

A **perfect square** is an integer that is the square of an integer. In other words, it is the product of some integer with itself. For example, $16 = 4 \times 4$.

You must not use any built-in library function, such as `sqrt`.

## Clarification

## Assumption

## Solution
### Approach - Binary Search
The problem can be transformed to find an integer `i` in the search space `[1, num]` such that `i * i == num`.

- If `i * i > num`, no need to search right (i.e., i+1, i+2, ···), since square of these values will also be larger than num.
- If `i * i < num`, no need to search left, since square of these values will also be smaller than num.
- If `i * i == num`, find the answer

With these properties, we can use binary search. Due to potential overflow of using `i * i == num` in C++ or Java, we convert it into integer division `i == num/i`. In order to check the equality of integer division, we need to check both division (`i == num/i`) and reminder (`num%i == 0`) since multiple integers may satisfy the equality condition `i == num/i` (e.g., `3 == 9/3`, `3 == 10/3`).

=== "Python"
    ```python
    class Solution:
        def isPerfectSquare(self, num: int) -> bool:
            left, right = 0, num

            while left <= right:
                mid = (left + right) // 2
                mid_square = mid * mid
                if num == mid_square:
                    return True
                elif num > mid_square:
                    left = mid + 1
                else:
                    right = mid - 1

            return False
    ```

=== "Java"
    ```java
    class Solution {
        public boolean isPerfectSquare(int num) {
            int left = 1;
            int right = num;
            int mid;
            int res;
            int remain;

            while (left <= right) {
                mid = left + (right - left)/2;
                res = num / mid;
                remain = num % mid;

                if (res == mid && remain == 0)
                    return true;
                else if (res > mid)  // (1)
                    left = mid + 1;
                else
                    right = mid - 1;
            }

            return false;
        }
    }
    ```

    1. Due to integer division, 16, 17 may satisfy `num/mid == mid`. Due to integer round down, none perfect square will always > the perfect square

#### Complexity Analysis
* Time complexity: $O(\log n)$  
The time complexity is $O(\log n)$ with the binary search. 
* Space complexity: $O(1)$  
Only use limited variables.

## Test

## Math
$1 + 3 + \cdots + (2n - 1) = (2n - 1 + 1) * n / 2 = n^2$

## References
- [multiple solutions from @fhqpizj](https://leetcode.com/problems/valid-perfect-square/solutions/83874/a-square-number-is-1-3-5-7-java-code/)