---
tags:
    - Backtracking
---

# 37. Sudoku Solver

## Problem Description

[LeetCode Problem 37](https://leetcode.com/problems/sudoku-solver/description/): Write
a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy **all of the following rules**:

1. Each of the digits `1-9` must occur exactly once in each row.
2. Each of the digits `1-9` must occur exactly once in each column.
3. Each of the digits `1-9` must occur exactly once in each of the 9 `3x3` sub-boxes of
the grid.

The `'.'` character indicates empty cells.

## Clarification

-

## Assumption

-

## Solution

### Approach 1: Backtracking

We can use the backtracking algorithm to solve the Sudoku puzzle. The idea is to fill
in the empty cells one by one, checking for validity at each step. If a cell cannot be
filled, we backtrack to the previous cell and try the next possible number.

To check if a number can be placed in a cell, We can use

- **sets** to keep track of the numbers that have already been placed in each row, column,
and sub-box.
- list of **integers** with **bitwise operations** to keep track of the numbers that have
already been placed in each row, column, and sub-box.

To optimize the solution, we can use the following techniques:

- **Most Constrained Variable**: Choose the cell with the fewest possible candidates
  to fill next. This reduces the search space and speeds up the backtracking process.

=== "Python"
    ```python
    class SudokuSolver:
        def __init__(self, board: list[list[str]]):
            self.board = board
            self.rows = [set() for _ in range(9)]
            self.cols = [set() for _ in range(9)]
            self.boxes = [set() for _ in range(9)]
            self.empty_cells = []

            self._initialize()

        def _initialize(self):
            for r in range(9):
                for c in range(9):
                    val = self.board[r][c]
                    if val == ".":
                        self.empty_cells.append((r, c))
                    else:
                        self._place_number(r, c, val)

        def _place_number(self, r: int, c: int, val: str):
            self.board[r][c] = val
            self.rows[r].add(val)
            self.cols[c].add(val)
            self.boxes[(r // 3) * 3 + c // 3].add(val)

        def _remove_number(self, r: int, c: int, val: str):
            self.board[r][c] = "."
            self.rows[r].remove(val)
            self.cols[c].remove(val)
            self.boxes[(r // 3) * 3 + c // 3].remove(val)

        def _get_candidates(self, r: int, c: int) -> set:
            return set(str(d) for d in range(1, 10)) - self.rows[r] - self.cols[c] - self.boxes[(r // 3) * 3 + c // 3]

        def _select_most_constrained_cell(self) -> tuple[int, int, int, set]:
            best_cell = None
            fewest_candidates = 10
            best_candidates = set()
            for i, (r, c) in enumerate(self.empty_cells):
                candidates = self._get_candidates(r, c)
                if len(candidates) < fewest_candidates:
                    best_cell = (i, r, c)
                    best_candidates = candidates
                    fewest_candidates = len(candidates)
                if fewest_candidates == 1:
                    break  # Early exit if only one possibility
            return best_cell + (best_candidates,)

        def _backtrack(self) -> bool:
            if not self.empty_cells:
                return True

            i, r, c, candidates = self._select_most_constrained_cell()
            self.empty_cells.pop(i)

            for num in candidates:
                self._place_number(r, c, num)
                if self._backtrack():
                    return True
                self._remove_number(r, c, num)

            self.empty_cells.insert(i, (r, c))
            return False

        def solve(self):
            self._backtrack()


    class Solution:
        def solveSudoku(self, board: list[list[str]]) -> None:
            solver = SudokuSolver(board)
            solver.solve()
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(9^m)$ where $m$ is the number of empty cells.
    - Initial setup and iteration through the board takes $O(1)$ time since the board
    size is fixed with 81 cells.
    - Recursion with backtracking could explore all 9 possible values for each empty
    cell in the worst case. So the time complexity is $O(9^m)$. The number of empty
    cells is at most 81, and each cell can have 9 possible values. The upper bound of
    time complexity is $O(9^81)$, which occurs when all cells are empty.
    - In practice, the average time complexity is much lower due to the pruning effect of
    backtracking and the use of the most constrained variable heuristic.

- Space complexity: $O(m)$
    - Storage of the sets for rows, columns, and boxes takes $O(1)$ space since each of
    these sets holds a maximum of 9 elements.
    - Recursion stack space can go as deep as the number of empty cells, $m$, which is
    at most 81 for a completely empty board.

## Test

- **Empty Sudoku**
  Input: An empty Sudoku board.  
  Output: The board is filled with a valid Sudoku solution.
- **Sudoku with One Empty Cell**
  Input: A Sudoku board with only one empty cell.  
  Output: The board is filled with a valid Sudoku solution.
- **Sudoku with Multiple Empty Cells**
  Input: A Sudoku board with multiple empty cells.  
  Output: The board is filled with a valid Sudoku solution.
- **Sudoku with All Cells Empty**
  Input: A Sudoku board with all cells empty.  
  Output: The board is filled with a valid Sudoku solution.
