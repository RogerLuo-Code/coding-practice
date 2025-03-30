---
tags:
    - Math
    - Recursion
---

# 50. Pow(x, n)

## Problem Description

[LeetCode Problem 50](https://leetcode.com/problems/powx-n/): Implement [pow(x, n)](http://www.cplusplus.com/reference/valarray/pow/),
which calculates `x` raised to the power `n` (i.e., `xn`).

## Clarification

- x or n can be negative?
- `x == 0`?
- data type of `x` and `n`?

## Assumption

-

## Solution

The straightforward approach is to use brutal force to multiple `x` by `n` times. Yet,
there is a more efficient method by [exponentiation using squaring](https://en.wikipedia.org/wiki/Exponentiation_by_squaring#Computational_complexity).

If we get the result of $x^{n/2}$, we dont' need to multiply x for another n/2 times.
Instead, we can use equation $x^{n} = (x^{n/2})^2$. So we can optimize the calculation
based on the equation below:  

$$x^n = \begin{cases}
{(x^{\frac{n}{2}})}^2 & \text{when n is even}\\
(x^{\frac{n}{2}})^2 x & \text{when n is odd}
\end{cases}$$

$$ \text{or } 
x^n = \begin{cases}
{(x^2)}^{\frac{n}{2}}  & \text{when n is even}\\
{(x^2)}^{\frac{n}{2}} x  & \text{when n is odd}
\end{cases}
$$

In all approaches, the `n < 0` case is converted to `n > 0` case by making the following
substitutions:

- `x = 1/x`
- `n = -n`.

We need to handle corner cases for these substitutions: divide by zero for $0^{-n}$
(usually is undefined and need clarifications) and integer overflow in non-Python languages.

???- "Divide by Zero for `1/x`"
    For floating point numbers, IEEE754 defines `1.0/0.0` as `Infinity`, `-1.0/0.0` as
    `-Infinity` and `0.0/0.0` as `NaN`. Many programming languages follows this and
    handle them implicitly. Yet, division by zero with `int` will throw an exception.

???- "Integer Overflow of `n = -n` in Java or C++"
    In Java, the int is represented by [two's complement form](https://en.wikipedia.org/wiki/Two%27s_complement)
    with range `[-2,147,483,648, 2,147,483,647]` or `[$-2^{31}$, $2^{31}-1$]`. We need
    to take care of over flow case for the min value: `-(-2,147,483,648) = -2,147,483,648`.
    There are two ways to deal with this case:

    - Define a 64-bit integer to hold the 32-bit value (Python automatically handle this). No overflow for 32-bit integer calculation.
    - Add if statement to check the special case `n == -2,147,483,648` and take care of it explicitly.

### Approach 1: Fast Recursion

We can recursively compute power value by reduce `n` by half.

???- "Time Complexity Differences between `myPow(x, n/2)*myPow(x, n/2)` and `halfResult = myPow(x, n/2) halfResult*halfResult`"
    - `myPow(x, n/2)*myPow(x, n/2)` will call myPow twice for each recursion. The total
    functions calls grow exponentially: $1 + 2 + 2^2 + \cdots + 2^{\log n} = 2^{\log n + 1} - 1$
    (For k-bit binary, 0~k bits are 1, $2^0 + 2^1 + \cdots + 2^k = 2^{k+1} - 1$).
    The time complexity is $\mathcal{O}(n)$ and the space complexity is
    $\mathcal{O}(\log n)$ for recursive function calls.
    ```
                2^n                     1
            /         \
        2^{n/2}         2^{n/2}         2
        /    \         /       \  
    2^{n/4} 2^{n/4} 2^{n/4} 2^{n/4}     2^2
    ...                                 ...
    ```
    - `halfResult = myPow(x, n/2) halfResult*halfResult` only call myPow function once
    for each recursion. This can be considered as memoization of above approach. The
    time complexity is $\mathcal{O}(\log n)$ and the space complexity is
    $\mathcal{O}(\log n)$ for recursive function calls.
    ```
        2^n
        |
        2^{n/2}
        |
        2^{n/4}
        |
        ...
    ```

=== "Python"
    ```python
    class Solution:
        def myPow(self, x: float, n: int) -> float:
            # Base case
            if n == 0:
                return 1.0
            if n == 1:
                return x
            if x == 0.0:
                return 0.0

            # Handle negative n
            if n < 0:
                n = -n
                x = 1 / x

            # Power by squaring
            x_half = self.myPow(x, n // 2)
            if n % 2 == 0:
                return x_half * x_half
            else:
                return x_half * x_half * x
    ```

=== "Java"
    ```java
    class Solution {
        public double myPow(double x, int n) {
            if (n < 0) {
                if (n == Integer.MIN_VALUE)
                    return myPow(x, n + 1)*(1/x); // x^n = x^(n+1)*x^(-1)
                else {
                    x = 1/x; // Divided by zero is implicitly handled by floating point division.
                    n = -n;
                }
            }

            if (n == 0) {
                return 1.0; // base case
            }

            double halfResult = myPow(x, n/2);
            if (n % 2 == 0)
                return halfResult*halfResult;
            else
                return halfResult*halfResult*x;
        }
    }
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(\log n)$  
  Each time `n` is reduced by half by using the equation $x^{n} = (x^{n/2})^2$. Thus we
  need at most $\mathcal{O}(\log n)$ computations to get the result.
- Space complexity: $O(\log n)$  
  We need to call the recursion function $\mathcal{O}(\log n)$ times and need constant
  space (store the result of $x^{n/2}$) for each computation. So the space complexity is
  $\mathcal{O}(\log n)$.

### Approach 2: Fast Iteration

By following the same idea, we can also use an iterative solution.

=== "python"
    ```python
    class Solution:
        def myPow(self, x: float, n: int) -> float:
            # Base case
            if n == 0:
                return 1.0

            # Handle negative n
            if n < 0:
                if math.isclose(x, 0.0, abs_tol=1e-9):
                    return 0.0
                n = -n
                x = 1 / x

            # Power by squaring
            result = 1.0
            while n > 0:
                if n % 2 == 1:  # (1)
                    result *= x
                    n -= 1
                x = x * x
                n = n // 2

            return result
    ```

    1. Handle two cases: (1) When `n` is odd and (2) the last step (n is odd or even), update the result.

#### Complexity Analysis of Approach 2

- Time complexity: $O(\log n)$  
  At each iteration, `n` is reduced by half. So there is total $\log n$ number of iterations.
- Space complexity: $O(1)$  
  Limited variables.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Fast Recursion | $O(\log n)$          | $O(\log n)$
Approach - Fast Iteration | $O(\log n)$          | $O(1)$

## Test

- n = 0 (should return 1)
- x = 0 (should return 0 for positive n, handle 0⁰ case)
- x = negative (ensure correct handling of odd/even n)
- n = negative (test division cases for small x)
- Very large n (ensure efficient handling)
