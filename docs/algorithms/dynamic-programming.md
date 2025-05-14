# Dynamic Programming

Dynamic Programming (DP) is a method for solving complex problems by breaking them down
into simpler subproblems. These problems have the following characteristics:

- **Optimal substructure**: an optimal solution can be constructed from optimal solutions
of its subproblems.
- **Overlapping subproblems**: the problem can be broken down into subproblems
which are re-used multiple times.

## Principles of Dynamic Programming

1. Identify a small number of subproblems
  For example, compute the max weight of $G_i$, for $i = 1, 2, 3, \cdots, n$
2. Can quickly and correctly solve "larger" subproblems given the solution to "smaller" subproblems
  Usually via a recursion such as `G[i] = max(G[i - 1]], G[i-2])`
3. After solving all subproblems, can quickly compute the final solution
  Usually, it's just the answer for the "biggest" subproblem

## Implementation

General idea:

- Divide a complex problem into a number of simpler **overlapping subproblem**.
- Define a **recursive relation** to solve larger subproblem from smaller subproblem.
- Store solutions to each of these subproblems, solving each subproblem only once.
- Use stored solutions to solve the original problem

Framework for implementation:

- Define a **state** (a set of variables) that sufficiently describe a scenario.
- A function or data structure that will **compute/contain the answer** to the subproblem
for every given state.
- A **recurrence relation** to transition between states. A recurrence relation is an
equation that relates different states with each other.
- **Base cases**, so that our recurrence relation doesn't go on infinitely.


There are two ways to implement dynamic programming:

- Bottom-up, also known as tabulation.
- Top-down, also known as memoization.

### Bottom-up (Tabulation)

Bottom-up is implemented with **iteration** and starts at the base case and iteratively
computes the value of each subproblem.

```pseudocode
F = array of length (n + 1)
F[0] = 0
F[1] = 1
for i from 2 to n:
    F[i] = F[i - 1] + F[i - 2]
```

### Top-down (Memoization)

Top-down is implemented with **recursion** by breaking down large problems into small subproblems,
and stores the results of each subproblem in
a memoization table.

```pseudocode
memo = hashmap
Function F(integer i):
    if i is 0 or 1:
        return i
    if i doesn't exist in memo:
        memo[i] = F(i - 1) + F(i - 2)
    return memo[i]
```

## Compare with Other Algorithms

- **Greedy algorithm**: always makes the locally optimal choice, but may not always
lead to the globally optimal solution. It does not have overlapping subproblems.
- **Divide and conquer**: divides the problem into smaller subproblems, but these
subproblems are not overlapping.

## References

- [Dynamic programming - Princeton Course](https://www.cs.princeton.edu/courses/archive/spring23/cos226/lectures/DynamicProgramming.pdf)
