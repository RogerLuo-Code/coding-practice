---
tags:
    - Array
    - Math
    - Dynamic Programming
---

# LC119. Pascal's Triangle II

## Problem Description

[LeetCode Problem 119](https://leetcode.com/problems/pascals-triangle-ii/): Given an
integer `rowIndex`, return the `rowIndexth` (**0-indexed**) row of the **Pascal's triangle**.

In **Pascal's triangle**, each number is the sum of the two numbers directly above it as
shown:

![](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)

## Clarification

## Assumption

## Solution

### Approach 1 - Math

Each row (0-indexing) of Pascal's triangle is the [binomial coefficients](https://en.wikipedia.org/wiki/Binomial_coefficient):
$C(r, 0),\; C(r, 1),\; \cdots,\; C(r, r)$, where $C(r, 0) = C(r, r) = 1$ and
$C(r, k) = \frac{r!}{k! (r - k)!}$.

There are two main recurrence relation can be derived from $C(r, k)$ equation:

1. Between two rows: $C(r, k) = C(r - 1, k - 1) + C(r - 1, k)$, i.e., Pascal's triangle
2. Within a row: $C(r, k) = C(r, k - 1) \frac{r - k + 1}{k}$

??? "Derivation of between-row recurrence relation"
    $$\begin{eqnarray}
      C(r - 1, k - 1) + C(r - 1, k) &=& \frac{(r - 1)!}{(k - 1)! (r - k)!} + \frac{(r - 1)!}{k! (r - k - 1)!} \\
      &=& \frac{(r - 1)! k}{k! (r - k)!} + \frac{(r - 1)! (r - k)}{k! (r - k)!} \\
      &=& \frac{r!}{k! (r - k)!} \\
      &=& C(r, k) \\
    \end{eqnarray}$$

??? "Derivation of within-a-row recurrence relation"
    $$\begin{equation}
      \frac{C(r, k)}{C(r, k - 1)} = \frac{\frac{r!}{k! (r - k)!}}{\frac{r!}{(k - 1)! (r - k + 1)!}} = \frac{r - k + 1}{k}
    \end{equation}$$

We can use the **2nd recurrence elation** within a row to directly compute consecutive
binomial coefficients in the same row.

=== "Python"
    ```python
    class Solution:
    def getRow(self, rowIndex: int) -> List[int]:
       row = [1] * (rowIndex + 1)
       for i in range(1, rowIndex):
           row[i] = row[i - 1] * (rowIndex - i + 1) // i

       return row
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  Just use one for loop to compute row elements.
- Space complexity: $O(n)$  
  The result contains $n$ elements for $n$-th row.

### Approach 2 - Iteration

The problem can be solved by iteratively computing from $0$th to $n$th row of Pascal's
triangle by using the **first recurrence relation** shown above.

=== "Python"
    ```python
    class Solution:
      def getRow(self, rowIndex: int) -> List[int]:
         prev_row = [1]
         for i_row in range(1, rowIndex + 1):
               curr_row = [1] * (i_row + 1)
               for j_col in range(1, i_row):
                  curr_row[j_col] = prev_row[j_col - 1] + prev_row[j_col]

               prev_row = curr_row

         return prev_row  # 1st row or prev_row == curr_row
    ```

#### Complexity Analysis

- Time complexity: $O(n^2)$  
  Use two for-loops to go through each element of each row.
- Space complexity: $O(n)$  
  Stores two rows' elements.

### Approach 2 - Recursion

Based on the **first recurrence relation**, the problem can be solved by recursively call
function itself to compute the row above until reach the base cases. The base cases are
$[1]$ for $0$th row.

=== "Python"
    ```python
    class Solution:
      def getRow(self, rowIndex: int) -> List[int]:
         # Base case
         if rowIndex == 0:
               return [1]

         curr_row = [1] * (rowIndex + 1)
         prev_row = self.getRow(rowIndex - 1)
         for j in range(1, rowIndex):
               curr_row[j] = prev_row[j - 1] + prev_row[j]

         return curr_row
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n^2)$  
  The function will be recursively calling $n$ times and within each function there is a
  for-loop to go through all elements for that row. Therefore, the time complexity is $O(n^2)$.
- Space complexity: $O(n)$  
    - Recursive function call stack takes $O(n)$ space, since the depth will reach $n$.
    - Store current and previous rows takes $O(n)$.
    - So the total space complexity is $O(n) + O(n) = O(n)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different approaches:

Approach             | Time Complexity | Space Complexity
---------------------|-----------------|-----------------
Approach - Math      | $O(n)$          | $O(n)$
Approach - Iteration | $O(n^2)$        | $O(n)$
Approach - Recursion | $O(n^2)$        | $O(n)$

## Test
