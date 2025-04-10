# Divide and Conquer

## Introduction

Divide and conquer is an algorithm design paradigm that breaks a problem into
**two or more** smaller subproblems, solves each subproblem independently, and then
combines their solutions to solve the original problem.

The divide and conquer technique is the basis of efficient algorithms for many problems,
such as sorting (e.g., quicksort, merge sort), multiplying large numbers
(e.g., Karatsuba algorithm) and computing the discrete Fourier transform (FFT).

## Comparison with Other Methods

### Other Recursion Methods

The difference between divide and conquer and other recursion methods is that in divide and
conquer, the problem is divided into two or more subproblems of the same type, while in
other recursion methods, the problem is divided into one or more subproblems of different types.

### Dynamic Programming

The difference between divide and conquer and dynamic programming is that in divide and
conquer, the subproblems are independent, while in dynamic programming, the subproblems
are dependent and share subsubproblems. In other words, in dynamic programming, the
solution to a subproblem is reused multiple times, while in divide and conquer, each
subproblem is solved independently.