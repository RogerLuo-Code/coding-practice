---
tags:
    - Dynamic Programming
---

# 1137. N-th Tribonacci Number

## Problem Description

[LeetCode Problem 1137](https://leetcode.com/problems/n-th-tribonacci-number/description/):
The Tribonacci sequence Tn is defined as follows:

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given n, return the value of Tn.

## Clarification

- Definition of Tribonacci number
- n >= 0

## Assumption

-

## Solution

### Approach 1: Iteration

The problem can be solved using iteration. The idea is to keep track of the
previous three numbers and update them based on the Tribonacci sequence definition.

=== "Python"
    ```python
    class Solution:
        def tribonacci(self, n: int) -> int:
            # Base case
            if n == 0:
                return 0

            if 0 < n <= 2:
                return 1

            prev1, prev2, prev3 = 1, 1, 0

            for i in range(3, n + 1):
                curr = prev1 + prev2 + prev3
                prev1, prev2, prev3 = curr, prev1, prev2

            return prev1
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  The iteration loop iterates over the range from 3 to n+1, which takes $O(n)$ time.
- Space complexity: $O(1)$  
  Only use 4 local variables, so the space complexity is $O(1)$.

### Approach 2: Matrix Exponentiation

The Tribonacci sequence equation can be converted into a matrix equation:

$$\underbrace{\begin{bmatrix} t_{n-2} \\ t_{n-1} \\ t_{n} \\ \end{bmatrix}}_{T_n} = \underbrace{\begin{bmatrix} 0 & 1 & 0 \\ 0 & 0 & 1 \\ 1 & 1 & 1 \\ \end{bmatrix}}_{M} \underbrace{\begin{bmatrix} t_{n-3} \\ t_{n-2} \\ t_{n-1} \\ \end{bmatrix}}_{T_{n-1}}$$

Then we can calculate $T_n$ using $T_n = M T_{n-1} = M^2 T_{n-2} = \cdots = M^{n - 2} T_2$,
where $T_2 = [t_0, t_1, t_2] = [0, 1, 1]^\top$ (i.e., $n = 3$). It comes down to
compute $M^n$. We can use **matrix exponential** technique to compute $M^n$ in
$O(\log n)$ time. The idea is similar to [50. Power(x, n)](../lc0001-0099/lc0050-powx-n.md).

=== "python"
    ```python
    class Solution:
        def tribonacci(self, n: int) -> int:
            # Base case
            if n == 0:
                return 0

            if 0 < n <=2:
                return 1

            fib_matrix = np.array([[0, 1, 0], [0, 0, 1], [1, 1, 1]])
            init_vec = np.array([[0], [1], [1]])
            fib_matrix_pow = self.fastPow(fib_matrix, n - 2)
            nth_vec = fib_matrix_pow @ init_vec  # T_n = M^n T_0

            return nth_vec.item((-1, 0))

        def fastPow(self, matrix: npt.NDArray, pow: int) -> npt.NDArray:
            if pow == 1:
                return matrix

            res = np.identity(3, dtype=np.uint64)

            while pow > 0:
                # Handle odd number of pow
                if pow & 1:
                    res @= matrix
                    pow -= 1
                matrix @= matrix
                pow = pow // 2

            return res

        def fastPowRecursion(self, matrix: npt.NDArray, pow: int) -> npt.NDArray:
            if pow == 1:
                return matrix

            half = self.fastPow(matrix, pow // 2)
            res = half @ half  # matrix multiplication

            # Handle odd number of pow
            if pow & 1:
                res = res @ matrix

            return res
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(3^3 \log n)$
    - The matrix exponentiation (`fastPow` method) takes $\log n$ steps. Each step
    conducts matrix multiplication, which takes $O(m^3)$ time, where $m = 3$ for
    $3 \times 3$ matrices.
    - So the total time complexity is $O(3^3 \log n)$.
- Space complexity: $O(1)$ using iterative fast power or $O(log n)$ using recursive
fast power
    - `fastPow` takes $O(1)$ space if using iteration method and takes $O(\log n) space
    if using recursion method due to recursion stack.
    - local variables for matrices and vector take $O(1)$ space
    - so the total space complexity is $O(1)$ if using iterative fast power and
    $ \log n$ if using recursive fast power.

### Approach 3: Recursion + Memoization

The problem can also be solved using recursion based on recurrence relation from
Tribonacci equation. We will use memoization to store repeated calculations.

=== "python"
    ```python
    class Solution:
        def __init__(self):
            self.cache = {}

        def tribonacci(self, n: int) -> int:
            # Base case
            if n == 0:
                return 0
            if 0 < n <= 2:
                return 1

            if n in self.cache:
                return self.cache[n]

            self.cache[n] = self.tribonacci(n - 1) + self.tribonacci(n - 2) + self.tribonacci(n - 3)
            return self.cache[n]
    ```

#### Complexity Analysis of Approach 3

- Time complexity: $O(n)$  
  Recursively call the function for each number from 0 to n just once and each call
  takes $O(1)$ time. So the total time complexity is $O(n)$.
- Space complexity: $O(n)$  
    - The cache dictionary stores at most $n - 2$ results.
    - The recursion stack takes $O(n)$ space since the depth could be $n$.
    - So the total space complexity is $O(n)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach 1 - Iteration | $O(n)$          | $O(1)$
Approach 2 - Matrix exponential | $O(\log n)$          | $O(1)$
Approach 3 - Recursion + Memoization | $O(n)$          | $O(n)$

## Test

- Test n <= 2
- Test n > 2
- Tes very large n to check the time complexity
