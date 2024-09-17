---
tags:
    - Binary Tree
    - Recursion
    - Depth-First Search
---

# LC94. Binary Tree Inorder Traversal

## Problem Description

[LeetCode Problem 94](https://leetcode.com/problems/binary-tree-inorder-traversal/): Given the root of a binary tree, return the inorder traversal of its nodes' values.

## Clarification

- Definition of inorder traversal

## Assumption

-

## Solution

### Approach 1 - Iteration with Stack

Instead of using recursion, we can traverse the nodes by using stack to store the nodes and pop it up when reaching the end of the left branch.

=== "Python"
    ```python
    from collections import deque

    class Solution:
        def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
            result = []
            stack = deque()
            curr = root

            while stack or curr:
                while curr:
                    stack.append(curr)
                    curr = curr.left

                curr = stack.pop()
                result.append(curr.val)
                curr = curr.right

            return result
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  The algorithm visits each node exactly once for total $n$ nodes.
- Space complexity: $O(n)$  

    - In the worst case (for example, every node only has left child), the stack will hold all $n$ nodes.
    - In the best case (a balanced binary tree), stack will hold $\log n$ nodes due to the height of the tree.

### Approach 2 - Recursive

This problem can be solved using the classic recursive method.

=== "python"
    ```python
    class Solution:
        def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
            result = []
            self.inorderTraversalInternal(root, result)
            return result

        def inorderTraversalInternal(self, root: Optional[TreeNode], result: List[int]):
            if root:
                self.inorderTraversalInternal(root.left, result)
                result.append(root.val)
                self.inorderTraversalInternal(root.right, result)
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  The algorithm visits each node exactly once for total $n$ nodes.
- Space complexity: $O(n)$  
    - In the worst case (for example, every node only has left child), the recursion will call $n$ times and recursion stack depth is $n$.
    - In the best case (a balanced binary tree), the recursion stack depth will be proportional to the height of the tree, which is $\log n$

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach - Iteration |  $O(n)$           | $O(n)$ |
Approach - Recursion |  $O(n)$           | $O(n)$  |

## Test
