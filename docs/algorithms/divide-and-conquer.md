# Divide and Conquer

## Introduction

Divide and conquer is an algorithm design paradigm that breaks a problem into
**two or more** smaller subproblems, solves each subproblem independently, and then
combines their solutions to solve the original problem.

The divide and conquer technique is the basis of efficient algorithms for many problems,
such as sorting (e.g., quicksort, merge sort), multiplying large numbers
(e.g., Karatsuba algorithm) and computing the discrete Fourier transform (FFT).

## Implementation Steps

1. **Divide**: Split the problem into a set of smaller subproblems of the same type,
${S_1, S_2, \cdots, S_n}$ where $n \geq 2$.
2. **Conquer**: Solve each subproblem recursively. If the subproblem size is small enough,
solve it as a base case.
3. **Combine**: Merge the solutions of the subproblems to form the solution to the
original problem.

The essential part of the divide and conquer is to figure out the
**recurrence relationship**, which subsequently defines the function of **divide** and **combine**.

## Comparison with Other Methods

### Other Recursion Methods

For divide and conquer, the problem is divided into **two or more** subproblems of the
same type, while in other recursion methods, the problem is divided into **one** subproblem.

### Dynamic Programming

For divide and conquer, the subproblems are **independent**, while in
dynamic programming, the subproblems are **dependent** and share subsubproblems.
In other words, in dynamic programming, the solution to a subproblem is reused multiple
times, while in divide and conquer, each subproblem is solved independently.

### Backtracking

- Often the case, the divide-and-conquer problem has a **single** solution, while
backtracking problem has **unknown** number of solutions.

- Each step of the divide-and-conquer problem is **indispensable** to build the final
solution, while many steps of the backtracking problem are serving as **attempts** to
search for the potential solution.

- The divide-and-conquer problem has a **clear** and **predefined** path, while the
backtracking problem does not know the **exact path** in advance.
