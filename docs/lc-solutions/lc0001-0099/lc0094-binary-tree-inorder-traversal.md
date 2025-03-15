---
tags:
    - Binary Tree
---

# LC94. Binary Tree Inorder Traversal

## Problem Description

[LeetCode Problem 94](https://leetcode.com/problems/binary-tree-inorder-traversal/):
Given the root of a binary tree, return the inorder traversal of its nodes' values.

## Clarification

- Definition of inorder traversal

## Assumption

-

## Solution

### Approach 1 - Recursion

This problem can be solved using the classic recursive method by defining a new helper function
`preorder`. In the helper function,

```python
inorder(root.left, values)  # recursively traverse the left subtree
values.append(root.val)  # visit root/parent node
inorder(root.right, values)  # recursively traverse the right subtree
```

=== "python"
    ```python
    class Solution:
        def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
            result = []
            self.inorder(root, result)
            return result

        def inorder(self, root: Optional[TreeNode], result: List[int]):
            if not root:
                return

            self.inorder(root.left, result)
            result.append(root.val)
            self.inorder(root.right, result)
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  The algorithm visits each node exactly once for total $n$ nodes.
- Space complexity: $O(n)$  
    - In the worst case (for example, every node only has left child), the recursion
    will call $n$ times and recursion stack depth is $n$.
    - In the best case (a balanced binary tree), the recursion stack depth will be
    proportional to the height of the tree, which is $\log n$

### Approach 2 - Iteration with Stack

Instead of using recursion, we can traverse the nodes by using stack to store the nodes
and pop it up when reaching the end of the left branch.

=== "Python"
    ```python
    from collections import deque

    class Solution:
        def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
            values = []
            stack = deque()

            curr_node = root
            while curr_node or stack:
                if curr_node:
                    stack.append(curr_node)  # (1)
                    curr_node = curr_node.left
                else:
                    curr_node = stack.pop()
                    values.append(curr_node.val)  # (2)
                    curr_node = curr_node.right

            return values
    ```

    1. To return the root later.
    2. Append after all left children.

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  Each node (total $n$ nodes) is pushed once to and popped once from the stack. So the
  time complexity is $O(2n) = O(n)$.
- Space complexity: $O(n)$  
    - In the worst case (for example, every node only has left child), the stack will
    hold all $n$ nodes.
    - In the best case (a balanced binary tree), stack will hold $\log n$ nodes due to
    the height of the tree.

### Approach 3 - Morris Traversal

We can use Morris traversal which is similar to the solution in
[preorder traversal](../lc0100-0199/lc0144-binary-tree-preorder-traversal.md#approach-3-morris-traversal).
The only difference is in when to visit node after finding predecessor:

- **Preorder** traversal: visit node when `predecessor.right` is `None` (before exploring
left), since root/parent needs to be the first (root - left - right) before exploring
the left.
- **Inorder** traversal: visit node when `predecessor.right` is `curr_node` (after exploring
left), since root/parent needs to be middle (left - middle - right).

=== "python"
    ```python
    class Solution:
        def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
            output = []
            curr_node = root
            while curr_node:
                if curr_node.left:
                    # Find predecessor, the rightmost node of the left sub-tree.
                    predecessor = curr_node.left
                    while predecessor.right and predecessor.right != curr_node:
                        predecessor = predecessor.right

                    # Handle two conditions out of while loops
                    if not predecessor.right:  # (1)
                        predecessor.right = curr_node
                        curr_node = curr_node.left
                    else:  # (2)
                        output.append(curr_node.val)
                        predecessor.right = None
                        curr_node = curr_node.right
                else:
                    output.append(curr_node.val)
                    curr_node = curr_node.right

            return output
    ```

    1. Condition 1: `predecessor.right` is `None`. The left sub-tree is not explored.
    2. Condition 2: `predecessor.right` is the `curr_node`. The left sub-tree has been visited.

#### Complexity Analysis of Approach 3

- Time complexity: $O(n)$  
    We visit each node twice, one for establishing link and one for removing. Therefore
    the time complexity is $O(n)$.
- Space complexity: $O(n)$  
    - Visit nodes taking $O(1)$ space.
    - The return list takes $O(n)$ space to save all node values.
    - The **total** space complexity is $O(n) = O(1) + O(n)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different approaches:

Approach             | Time Complexity | Space Complexity (Overall) | Space Complexity (Visit)
---------------------|-----------------|----------------------------|-------------------------
Approach - Recursion | $O(n)$          | $O(n)$                     | $O(n)
Approach - Iteration | $O(n)$          | $O(n)$                     | $O(n)
Approach - Morris    | $O(n)$          | $O(n)$                     | $O(1)

## Test
