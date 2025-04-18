# Backtracking

[Backtracking](https://en.wikipedia.org/wiki/Backtracking) is a general algorithm for
finding all (or some) solutions to some computational problems, particularly constraint
satisfaction problems. It incrementally builds candidates for solutions and abandons a
candidate ("backtracks") as soon as it determines that the candidate cannot be extended
to a valid solution.

We can view the procedure of backtracking as a tree structure, where the root node
represents the initial problem and the leaves represent the solutions. Each node in the
tree represents a candidate solution, and the edges represent the choices made to reach
that candidate. **Backtracking** reduces the search space by eliminating candidates
(i.e. pruning the tree) that are not valid solutions.

The following diagram illustrates the backtracking process:

```mermaid
graph TD
    p(Problem)
    c1(Candidate 1)
    ci(Candidate i)
    cn(Candidate n)
    c11(Candidate 1.1, Fail)
    ci1(Candidate i.j)
    cn1(Candidate n.l)
    sk(Solution k)
    sm(Solution m)
    p --> c1 --> c11
    p --> ci --> ci1 --> sk
    p --> cn --> cn1 --> sm
    c11 --Backtrack--> c1

    style c11 fill:#FF8A8A
```

## How Backtracking Works

Backtracking is a depth-first search algorithm that explores all possible solutions to a
problem. It does this by building a solution incrementally, one piece at a time, and
discarding solutions that fail to satisfy the constraints of the problem as soon as they
are detected.
The algorithm can be summarized in the following steps:

1. **Choose**: Select a candidate solution.
2. **Check**: Check if the candidate solution is valid.
3. **Complete**: If the candidate solution is complete, return it.
4. **Backtrack**: If the candidate solution is not valid, backtrack to the previous step
   and try another candidate solution.
5. **Repeat**: Repeat the process until a solution is found or all candidates have been
   exhausted.
6. **Return**: If a solution is found, return it; otherwise, return failure.

## Standard Backtracking Problems

- All permutations
- Knight's Tour
- [N-Queens](https://en.wikipedia.org/wiki/Eight_queens_puzzle)
- Rat in a Maze
- Subset Sum
- [Sudoku Solver](https://en.wikipedia.org/wiki/Sudoku)
- Graph Coloring