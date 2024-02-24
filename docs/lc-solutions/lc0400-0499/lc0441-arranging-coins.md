---
tags:
- Binary Search
---

# LC441. Arranging Coins
## Problem Description
[LeetCode Problem 441](https://leetcode.com/problems/arranging-coins/): You have `n` coins and you want to build a staircase with these coins. The staircase consists of `k` rows where the `ith` row has exactly `i`coins. The last row of the staircase **may be** incomplete.

Given the integer `n`, return _the number of **complete rows** of the staircase you will build_.

## Clarification
- ith row contains i coins
- the last row may or may be incomplete

## Assumption
- n >= 1

## Solution
### Approach - Brutal Force
Follow the problem descriptions, add coins along each row until `sum >= n`.

=== "Python"
    ```python
    class Solution:
        def arrangeCoins(self, n: int) -> int:
            sum = 0
            for i_row in range(1, n + 1):
                sum += i_row
                if sum == n:
                    return i_row

                if sum > n:
                    return i_row - 1
    ```

#### Complexity Analysis
* Time complexity: $O(\sqrt{n})$  
We will go trough $k$ rows, $k \leq \sqrt{2n + 0.25}- 0.5$. Refer to the math section below.
* Space complexity: $O(1)$  
Use two variables, `sum` and `i_row`

### Approach - Binary Search
The problem can be expressed by the following equation:

$$1 + 2 + 3 + \dots + k + x = n$$

where $x$ represents the last incomplete row with range $0 <= x < (k + 1)$.

Essentially, we are trying to find $k$ that satisfies:

$$1 + 2 + 3 + \dots + k \leq n$$

which means

$$k * (k + 1) \leq 2n$$

Then we can use binary search to find $k$ effectively.

=== "Python"
    ```python
    class Solution:
        def arrangeCoins(self, n: int) -> int:
            left, right = 0, n

            while left < right - 1:
                mid = (left + right) // 2
                num = mid * (mid + 1)

                if num == 2 * n:
                    return mid
                elif num < 2 * n:
                    left = mid
                else:
                    right = mid - 1

            if right * (right + 1) <= 2 * n:
                return right
            else:
                return left
    ```

#### Complexity Analysis
* Time complexity: $O(\log n)$  
Since using the binary search to find $k$ from space `[0, n]`, the time complexity is $O(\log n)$
* Space complexity: $O(1)$  
Use 3 variables, `left`, `mid`, `right`.

### Approach - Math
The equation $k * (k + 1) \leq 2n$ can be further reduced to:

$$\begin{align} k^2 + k &\leq 2n \\ (k + 0.5)^2 &\leq 2n + 0.25 \\ k &\leq \sqrt{2n + 0.25}- 0.5 \end{align}$$

Since we want the row has full coins, we just find the floor value of $k$ in the above equation.

=== "Python"
    ```python
    class Solution:
        def arrangeCoins(self, n: int) -> int:
            return math.floor(math.sqrt(2 * n + 0.25) - 0
    ```

#### Complexity Analysis
* Time complexity: $O(1)$  
Just solve the equation directly. So the time complexity is $O(1)$.
* Space complexity: $O(1)$  

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Brutal Force |  $O(\sqrt{n})$ 	   	   	| $O(1)$  
Approach - Binary Search |  $O(\log n)$      		| $O(1)$  
Approach - Math |  $O(1)$      		| $O(1)$  

## Test