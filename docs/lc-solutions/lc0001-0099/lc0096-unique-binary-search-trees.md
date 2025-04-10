---
tags:
    - Dynamic Programming
    - Binary Search Tree
    - Math
---

# 96. Unique Binary Search Trees

## Problem Description

[LeetCode Problem 96](https://leetcode.com/problems/unique-binary-search-trees/): Given
an integer `n`, return the number of structurally unique BST's (binary search trees)
which has exactly `n` nodes of unique values from `1` to `n`.

## Clarification

-

## Assumption

-

## Solution

### Approach 1: Dynamic Programming

For a given root node `i`, the number of unique BSTs is the product of the
number of unique BSTs that from the left subtree based on subsequence
$1, 2, \cdots, i - 1$ and the right subtree based on sequence $i + 1, i + 2, \cdots, n$.

Based on this observation, we can solve the problem using dynamic programming. To do so,
we can define two functions:

- `G(n)`: the number of unique BSTs that can be formed with `n` nodes (i.e., length of
a sequence).
- `F(i, n)`: the number of unique BSTs that can be formed with `i` as the **root** node
with total $n$ nodes ($1 \leq i \leq n$).

Based on above definitions, we can derive the following equations:

- $G(n) = \sum_{i=1}^{n} F(i, n)$: sum of all unique BSTs with `i` as the root node
where `i` ranges from 1 to n.
- $F(i, n) = G(i - 1) \cdot G(n - i)$: the number of unique BSTs with root `i` is the
product of all unique number of BSTs formed with `i - 1` nodes in the left subtree and
`n - i` nodes in the right subtree.
- $G(0) = 1$, $G(1) = 1$: base case

So combine above equations together, we obtain:

$$G(n) = \sum_{i=1}^{n} G(i - 1) \cdot G(n - i)$$

=== "Python"
    ```python
    class Solution:
        def numTrees(self, n: int) -> int:
            G = [0] * (n + 1)
            G[0], G[1] = 1, 1

            for i in range(2, n + 1):
                for j in range(1, i + 1):
                    G[i] += G[j - 1] * G[i - j]

            return G[n]
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n^2)$  
  The outer loop runs `n - 1` times and the inner loop runs `i` times, where `i` ranges from
  `2` to `n`. The total number of iterations is $\sum_{i=2}^{n} i = \frac{(n+2)(n-1)}{2}$.
  So the total time complexity is $O(n^2)$.
- Space complexity: $O(n)$  
  We use an array `G` of size `n + 1` to store the number of unique BSTs for each `i`
  from `0` to `n`. So the space complexity is $O(n)$.

### Approach 2: Math

The sequence of `G(n)` is known as the **Catalan number**. The `n`th Catalan number can be
computed using the following formula:

$$C_n = \frac{1}{n + 1} \binom{2n}{n} = \frac{(2n)!}{(n + 1)!n!}$$

where $C_n$ is the `n`th Catalan number, and $\binom{2n}{n}$ is the binomial coefficient
defined as $\binom{n}{k} = \frac{n!}{k!(n - k)!}$.

=== "python"
    ```python
    class Solution:
        def numTrees(self, n: int) -> int:
            return factorial(2 * n) // (factorial(n) * factorial(n + 1))
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  The time complexity is dominated by the computation of the factorials. The
  computation of the factorials takes $O(n)$ time.
- Space complexity: $O(1)$  
  The space complexity is $O(1)$ because we are using a constant amount of space to
  store the factorials.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach                       | Time Complexity | Space Complexity
-------------------------------|-----------------|-----------------
Approach - Dynamic Programming | $O(n^2)$        | $O(n)$
Approach - Math                | $O(n)$          | $O(1)$

## Test
