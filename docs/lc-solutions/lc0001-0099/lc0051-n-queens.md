---
tags:
    - Backtracking
---

# 51. N-Queens

## Problem Description

[LeetCode Problem 51](https://leetcode.com/problems/): The **n-queens** puzzle is the
problem of placing `n` queens on an `n x n` chessboard such that no two queens attack
each other.

Given an integer `n`, return _all distinct solutions to the **n-queens puzzle**_.
You may return the answer in **any order**.

Each solution contains a distinct board configuration of the n-queens' placement,
where `'Q'` and `'.'` both indicate a queen and an empty space, respectively.

## Clarification

-

## Assumption

-

## Solution

### Approach 1: Backtracking

The solution is similar to the [N-Queens II problem](lc0052-n-queens-ii.md).
The only difference is that we need to return all
distinct solutions instead of just counting them. We can do this by storing the valid
solutions in a list and returning that list at the end.

=== "Python"
    ```python
    class Solution:
        def solveNQueens(self, n: int) -> List[List[str]]:
            self.ans = []
            empty_board = [["."] * n for _ in range(n)]
            self.solve(n, 0, set(), set(), set(), empty_board)
            return self.ans

        def solve(
            self,
            n: int,
            i_row: int,
            cols: set[int],
            diagonals: set[int],
            anti_diagonals: set[int],
            state,
        ) -> None:
            if i_row == n:  # Find valid solution
                self.ans.append(self._create_board(state))
                return

            for i_col in range(n):
                curr_diagonal = i_row - i_col
                curr_anti_diagonal = i_row + i_col

                # Check whether the queen is placeable
                if (
                    i_col in cols
                    or curr_diagonal in diagonals
                    or curr_anti_diagonal in anti_diagonals
                ):
                    continue

                # Add the queen to the board
                cols.add(i_col)
                diagonals.add(curr_diagonal)
                anti_diagonals.add(curr_anti_diagonal)
                state[i_row][i_col] = "Q"

                # Move on to the next row with the updated state
                self.solve(n, i_row + 1, cols, diagonals, anti_diagonals, state)

                # Remove the queen since we have already explored all valid paths
                cols.remove(i_col)
                diagonals.remove(curr_diagonal)
                anti_diagonals.remove(curr_anti_diagonal)
                state[i_row][i_col] = "."

        def _create_board(self, state: list[list[str]]):
            board = []
            for row in state:
                board.append("".join(row))
            return board
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n!)$
    - It takes $O(n!)$ to find all possible solutions. For each row, we have $n$ choices,
    and for each choice, we have $n-1$ choices for the next row, and so on.
    - To build each valid solution, it takes $O(n^2)$. Yet, the number of valid solutions,
    $s_n$ is much smaller than $n!$, $s_n << n$.
    - So the overall time complexity is $O(n! + s_n \cdot n^2) = O(n!)$.

- Space complexity: $O(n)$  
    - The recursion stack takes $O(n)$ space, since it goes up to $n$ levels deep
    (number of rows).
    - The hashsets `cols`, `diagonals`, and `anti_diagonals` take $O(n)$ since they
    store one value for each row.
    - The board takes $O(n^2)$ space since it is a 2D array of size $n \times n$.
    - The list `ans` takes $O(n^2)$ space since it stores all valid solutions.
    - So the overall space complexity is $O(n) + O(n) + O(n) + O(n^2) + O(n^2) = O(n^2)$.

## Test
