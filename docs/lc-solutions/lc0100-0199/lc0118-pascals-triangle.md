---
tags:
    - Dynamic Programming
---

# 118. Pascal's Triangle

## Problem Description

[LeetCode Problem 118](https://leetcode.com/problems/pascals-triangle/description/):
Given an integer `numRows`, return the first numRows of **Pascal's triangle**.

In **Pascal's triangle**, each number is the sum of the two numbers directly above it as
shown:

![wiki - Pascal Triangle Animation](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)

## Clarification

- Definition of Pascal's Triangle.
- return empty list when `numRows` is 0 or negative?

## Assumption

-

## Solution

Definition of Pascal's triangle:

- `1` on both sides
- `i`th row contains `i + 1` numbers
- `f(i, j) = f(i - 1, j - 1) + f(i - 1, j)`, `1 <= i < n - 1`, excluding two ends

assuming 0-based indexing.

### Approach 1: Iteration

Based on the property off Pascal's triangle, we can compute the current row based on the
previous row. We can do it iteratively.

=== "Python"
    ```python
    class Solution:
        def generate(self, numRows: int) -> List[List[int]]:
            results = []

            for i_row in range(numRows):
                curr_row = [1] * (i_row + 1)  # initialize the current row with ones

                # Update column from 1 to n - 2 excluding two ends 0 and n - 1
                # This will naturally skip the 1st and 2nd rows.
                for j in range(1, len(curr_row) - 1):
                    prev_row = results[i_row - 1]
                    for j_col in range(1, i_row):
                        curr_row[j_col] = prev_row[j_col - 1] + prev_row[j_col]

                results.append(curr_row)

            return results
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n^2)$  
  There are nested-for loops: the outer loops runs $n$ times while the inner loop
  increases by row, from 1, 2, 3, ..., n. The total number of executions is
  $1 + 2 + \cdots + n = \frac{n (n + 1)}{2}$. So the time complexity is $O(n^2)$.
- Space complexity: $O(n^2)$  
    - `prev_row` and `curr_row` take $O(n)$ space.
    - The result list takes $O(n^2)$ space.

### Approach 2: Recursion

We can also solve the problem using recursion. Recursively compute triangle with $k - 1$
rows and add the current row after that.

=== "python"
    ```python
    class Solution:
        def generate(self, numRows: int) -> List[List[int]]:
            # Base case
            if numRows <= 0:
                return []

            if numRows == 1:
                return [[1]]

            triangle = self.generate(numRows - 1)
            prev_row = triangle[-1]
            curr_row = [1] * numRows
            for j in range(1, numRows - 1):
                curr_row[j] = prev_row[j - 1] + prev_row[j]

            triangle.append(curr_row)

            return triangle
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n^2)$  
    - The recursion will takes $n$ calls
    - For each call, it will go through all row numbers. The row number is decreasing
    from n to 1.
    - So the total execution is $n + n - 1 + \cdots + 1 = \frac{n (n + 1)}{2}$.
- Space complexity: $O(n^2)$  
    - recursion function call stack stakes $O(n)$ space.
    - `prev_row` and `curr_row` takes $O(n)$ space.
    - the result list takes $O(n^2)$ space.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Iteration | $O(n^2)$          | $O(n^2)$
Approach - Recursion | $O(n^2)$          | $O(n^2)$

## Test

- Test simple cases where `numRows` is 1 or 2.
- Test normal cases with small number of rows.
