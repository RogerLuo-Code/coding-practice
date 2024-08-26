# Dynamic Programming

## Principles of Dynamic Programming
1. Identify a small number of subproblems  
  For example, compute the max weight of $G_i$, for $i = 1, 2, 3, \cdots, n$  
2. Can quickly and correctly solve "larger" subproblems given the solution to "smaller" subproblems  
  Usually via a recursion such as `G[i] = max(G[i - 1]], G[i-2])`  
3. After solving all subproblems, can quickly compute the final solution  
  Usually, it's just the answer for the "biggest" subproblem

Dynamic programming procedure:
- Divide a complex problem into a number of simpler **overlapping subproblem**.
- Define a **recursive relation** to solve larger subproblem from smaller subproblem.
- Store solutions to each of these subproblems, solving each subproblem only once.
- Use stored solutions to solve the original problem

## Why "Dynamic Programming"



## References
- [Dynamic programming - Princeton Course](https://www.cs.princeton.edu/courses/archive/spring23/cos226/lectures/DynamicProgramming.pdf)