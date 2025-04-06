---
tags:
    - Dynamic Programming
    - Binary Search Tree
    - Math
---

# 95. Unique Binary Search Trees II

## Problem Description

[LeetCode Problem 95](https://leetcode.com/problems/unique-binary-search-trees-ii/description/):
Given an integer `n`, return all the structurally unique BST's (binary search trees),
which has exactly `n` nodes of unique values from `1` to `n`. Return the answer in any order.

## Clarification

-

## Assumption

-

## Solution

### Approach 1: Recursion

A binary search tree has the property: the left subtree contains all values less than
the root and the right subtree contains all values greater than the root.

Based on the above property, we can recursively construct all possible BSTs by

1. Choosing each number from `1` to `n` as the root node.
2. Recursively constructing all possible left subtrees using the numbers less than the root.
3. Recursively constructing all possible right subtrees using the numbers greater than the root.
4. Combining the left and right subtrees with the root node.
5. Storing the result in a memoization dictionary to avoid recomputation.
6. Returning the list of all unique BSTs.

=== "Python"
    ```python
    class Solution:
      def generateTrees(self, n: int) -> List[Optional[TreeNode]]:
          memo = {}
          return self.allPossibleBst(1, n, memo)

      def allPossibleBst(self, start: int, end: int, memo: dict[tuple, list]) -> List[Optional[TreeNode]]:
          # Base case
          if start > end:
              return [None]
          if start == end:
              return [TreeNode(start)]
          if (start, end) in memo:
              return memo[(start, end)]

          result = []
          # Iterate through all values and construct left and right subtree recursively
          for i in range(start, end + 1):
              left_sub_trees = self.allPossibleBst(start, i - 1, memo)
              right_sub_trees = self.allPossibleBst(i + 1, end, memo)

              # Loop through all left and right subtrees and connect them to ith root
              for left in left_sub_trees:
                  for right in right_sub_trees:
                      root = TreeNode(i, left, right)
                      result.append(root)

          # Store the result in memoization dictionary
          # to avoid recomputation
          # for the same range of start and end
          memo[(start, end)] = result
          return result
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(\frac{4^n}{\sqrt{n}})$  
    - **Number of trees**: The total number of unique BSTs with `n` nodes is given by the
    `n`th [Catalan number](https://en.wikipedia.org/wiki/Catalan_number) (Refer to
    [LC95](lc0095-unique-binary-search-trees-ii.md) for more details), which is
    $C_n = \frac{1}{n+1} \binom{2n}{n} \approx \frac{4^n}{n^{3/2}\sqrt{\pi}}$.
    - **Build each tree**: Each of these BSTs has $n$ nodes and takes $O(n)$ time to construct.
    - So the total time complexity is
    $O(n \cdot C_n) = O(n \cdot \frac{4^n}{n^{3/2}\sqrt{\pi}}) = O(\frac{4^n}{\sqrt{n}})$.
- Space complexity: $O(\frac{4^n}{\sqrt{n}})$  
    - **Call stack**: In the worst case, the recursion depth is $n$ (recursively called
    $n$ times), taking $O(n)$ space.
    - **Memoization**: The memoization dictionary stores the results of all possible
    BSTs for each range of `start` and `end`, which is
    $\sum_{k = 1}^n (n - k + 1) C_k k$. So the space complexity is $O(n C_n) = O(\frac{4^n}{\sqrt{n}})$.
    - **Result list**: The result list stores all unique BSTs ($C_n$ trees) and each
    tree contains $n$ nodes. So the space complexity is $O(n C_n)$.
    - **Total space complexity**: $O(n + n C_n + n C_n) = O(n C_n) = O(\frac{4^n}{\sqrt{n}})$.

### Approach 2: 

Solution

=== "python"
    ```python
    code
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(1)$  
  Explanation
- Space complexity: $O(n)$  
  Explanation

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - | $O(1)$          | $O(n)$
Approach - | $O(1)$          | $O(n)$

## Test
