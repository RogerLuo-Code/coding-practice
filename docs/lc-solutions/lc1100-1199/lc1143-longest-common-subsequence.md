# ---
tags:
    - Dynamic Programming
---

# 1143. Longest Common Subsequence

## Problem Description

[LeetCode Problem 1143](https://leetcode.com/problems/longest-common-subsequence/description/):
Given two strings `text1` and `text2`, return _the length of their longest
**common subsequence**._ If there is no **common subsequence**, return `0`.

A **subsequence** of a string is a new string generated from the original string with
some characters (can be none) deleted without changing the relative order of the
remaining characters.

- For example, `"ace"` is a subsequence of `"abcde"`.

A **common subsequence** of two strings is a subsequence that is common to both strings.

## Clarification

- A **subsequence** is a sequence that appears in the same relative order, but not
necessarily contiguous.

## Assumption

-

## Solution

This problem can be solved using dynamic programming:

1. **Define the State**: Let `dp(i, j)` be the length of the longest common subsequence
of `text1[0:i + 1]` (from index `0` to `i`) and `text2[0:j + 1]` (from index `0` to `j`).
2. **State Transition**:
    - If the last characters of both substrings are equal (`text1[i] == text2[j]`), then:
   `dp(i, j) = dp(i-1, j-1) + 1`.
    - If they are not equal, then: `dp(i, j) = max(dp(i-1, j), dp(i, j-1))`
3. **Base Case**: If either string is empty, the longest common subsequence is `0`.

Note that `dp(i, j)` can also be defined as the length of the longest common subsequence
of `text1[i:]` (from index `i` to end) and `text2[j:]` (from index `j` to end).

### Approach 1: Dynamic Programming (Top-Down with Memoization)

The first approach uses a top-down dynamic programming technique with memoization to
find the longest common subsequence. The function `dp` is defined recursively, and
the results are cached to avoid redundant calculations.

=== "Python"
    ```python
    class Solution:
        def longestCommonSubsequence(self, text1: str, text2: str) -> int:
            self.cache = {}
            return self.dp(text1, text2, len(text1) - 1, len(text2) - 1)

        def dp(self, text1: str, text2: str, i: int, j: int) -> int:
            # Base case
            if i < 0 or j < 0:
                return 0

            # Return cached result if exists
            if (i, j) in self.cache:
                return self.cache[(i, j)]

            # Recursively update the current result based on previous ones
            if text1[i] == text2[j]:
                self.cache[(i, j)] = self.dp(text1, text2, i - 1, j - 1) + 1
            else:
                self.cache[(i, j)] = max(self.dp(text1, text2, i - 1, j), self.dp(text1, text2, i, j - 1))

            return self.cache[(i, j)]
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(m n)$ where `m` and `n` are the lengths of `text1` and `text2`,
respectively  
  The algorithm explores all possible pairs of indices `(i, j)` for the two strings
  with $0 \leq i < m$ and $0 \leq j < n$, leading to a time complexity of $O(m n)$.
- Space complexity: $O(m n)$  
    - Memoization cache stores up to $m n$ entries.
    - The recursion stack can go up to a depth of $O(m + n)$ where no characters match
    and it alternately advance `i` or `j` one at a time.
    - Thus, the overall space complexity is $O(m n) + O(m + n) = O(m n)$.

### Approach 2: Dynamic Programming (Bottom-Up with Tabulation)
The second approach uses a bottom-up dynamic programming technique with tabulation
to find the longest common subsequence. It builds a 2D grid `dp_grid` where `dp_grid[i][j]`
represents the length of the longest common subsequence of `text1[0:i + 1]` and
`text2[0:j + 1]`. The grid is filled iteratively, starting from the last row and
last column (the smallest problem), and moving towards the first row and first column
(the largest problem).

To facilitate calculation, we add an extra row and column to the grid, initialized
to `0`, which allows us to handle the base case where one of the strings is empty.

[LeetCode Tutorial on Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/solution/)
has a good illustration of the bottom-up approach.

To optimize space, we can use two 1D arrays instead of a 2D grid. The previous row is stored
in `prev_row`, and the current row is stored in `curr_row`. After processing each row,
the `prev_row` is updated to `curr_row`, and the process continues until the first row
is reached.

=== "python"
    ```python
    class Solution:
        def longestCommonSubsequence(self, text1: str, text2: str) -> int:
            # Swap text1 and text2 if text2 is longer to optimize space (smaller arrays)
            if len(text2) > len(text1):
                text1, text2 = text2, text1

            n_row, n_col = len(text1), len(text2)
            dp_grid = [[0] * (n_col + 1) for _ in range(n_row + 1)]  # Initialize n_row x n_col grid with 0s

            # Iterate by rows and then columns, starting from the last row and last column
            prev_row = [0] * (n_col + 1)
            for i_row in range(n_row - 1, -1, -1):
                curr_row = [0] * (n_col + 1)
                for i_col in range(n_col - 1, -1, -1):
                    if text1[i_row] == text2[i_col]:
                        curr_row[i_col] = 1 + prev_row[i_col + 1]
                    else:
                        curr_row[i_col] = max(curr_row[i_col + 1], prev_row[i_col])
                prev_row = curr_row

            return prev_row[0]
    ```

=== "python - grid"
    ```python
    class Solution:
        def longestCommonSubsequence(self, text1: str, text2: str) -> int:
            n_row, n_col = len(text1), len(text2)
            dp_grid = [[0] * (n_col + 1) for _ in range(n_row + 1)]  # Initialize n_row x n_col grid with 0s

            # Iterate by rows and then columns, starting from the last row and last column
            for i_row in range(n_row - 1, -1, -1):
                for i_col in range(n_col - 1, -1, -1):
                    if text1[i_row] == text2[i_col]:
                        dp_grid[i_row][i_col] = 1 + dp_grid[i_row + 1][i_col + 1]
                    else:
                        dp_grid[i_row][i_col] = max(dp_grid[i_row + 1][i_col], dp_grid[i_row][i_col + 1])

            return dp_grid[0][0]
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(m n)$  
  The algorithm use two nested loops to iterate through the characters of `text1` and `text2`,
  leading to a time complexity of $O(m n)$ where `m` and `n` are the lengths of `text1`
  and `text2`, respectively.
- Space complexity: $O(min(m, n))$  
    The space complexity is reduced to $O(min(m, n))$ by using two 1D arrays instead of a
    2D grid. The size of the arrays is the smaller of the two strings.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach 1 - DP (Top-Down) | $O(m n)$          | $O(m n)$
Approach 2 - DP (Bottom-Up) | $O(m n)$          | $O(min(m, n))$

## Test

- Test normal cases
- Test edge cases with one or both strings empty
- Test cases with no common subsequence
- Test cases with all characters matching