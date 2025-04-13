---
tags:
    - Binary Search Tree
---

# 98. Validate Binary Search Tree

## Problem Description

[LeetCode Problem 98](https://leetcode.com/problems/validate-binary-search-tree/description/):
Given the `root` of a binary tree, _determine if it is a valid binary search tree (BST)_.

A **valid BST** is defined as follows:

- The left subtree of a node contains only nodes with keys **less than** the node's key.
- The right subtree of a node contains only nodes with keys **greater than** the node's key.
- Both the left and right subtrees must also be binary search trees.

## Clarification

-

## Assumption

-

## Solution

### Approach 1: Validate Range

We can use either recursive or iterative method to check if the current node's value is
within the valid range.

For a binary search tree:

- Left subtree: **all** values < current node's value
- Right subtree: **all** values > current node's value

So to update the valid range:

- Only update the `high` limit when going **left**
- Only update the `low` limit when going **right**

=== "Python"
    ```python
    class Solution:
        def isValidBST(self, root: Optional[TreeNode]) -> bool:
            return self.validate_subtree(root, float("-inf"), float("inf"))

        def validate_subtree(self, node: Optional[TreeNode], low: float, high: float) -> bool:
            # Base case
            if node is None:
                return True

            # Validate the root value
            if not (low < node.val < high):
                return False

            # Recursively check left and right trees
            return self.validate_subtree(node.left, low, node.val) and \
                   self.validate_subtree(node.right, node.val, high)
    ```

=== "Python - Iteration"
    ```python
    from collections import deque
    import math

    class Solution:
        def isValidBST(self, root: Optional[TreeNode]) -> bool:
            if root is None:
                return True

            stack = deque([(root, -math.inf, math.inf)])
            while stack:
                node, low, high = stack.pop()
                if not node:
                    continue

                # Check if the current node's value is within the valid range
                if node.val <= low or node.val >= high:
                    return False

                # Push the left and right children onto the stack with updated bounds
                # update upper bound when search left
                # update lower bound when search right
                stack.append((node.left, low, node.val))
                stack.append((node.right, node.val, high))

            return True
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  We traverse each node once, so the time complexity is linear in terms of the number of
  nodes.
- Space complexity: $O(n)$  
    - For recursive approach, the space complexity is $O(h)$, where $h$ is the height of
    the tree. In the worst case, the tree can be skewed, leading to a space complexity
    of $O(n)$.
    - For iterative approach, the space complexity in the worst case is $O(n)$ due to
    the stack used for DFS traversal. For a skewed tree below, stack can hold $n / 2$ nodes.

    ```
    2
     \
      6
     /  \
    3    7
        /  \
       4    8
    ```

### Approach 2: In-Order Validation

One key property of binary search trees is that in-order traversal of a BST yields a
**strictly increasing** sequence of values.

We can use this property to validate the BST by performing an in-order traversal and
checking if the current node's value is greater than the previous node's value.

In the **recursive** approach, we need to define class property `self.prev` to store the
last visited node's value properly instead of passing `prev` as a parameter.

- `self.prev` is updated and shared across recursive calls.
- `prev` in parameter is passed by value. Each recursive call gets its own copy and the
updated value doesn't pass to the next recursive call.

???- "Difference Between Defining `self.prev` in `__init__` and `isValidBST`"
    | Location     | When is `self.prev` created?                              | Scope                                        | When is it reset?                             |
    | ------------ | --------------------------------------------------------- | -------------------------------------------- | --------------------------------------------- |
    | `__init__`   | When the object is instantiated (e.g. `sol = Solution()`) | Available to all methods in the class        | **Only reset if you explicitly do so**        |
    | `isValidBST` | Each time `isValidBST()` is called                        | Also available to other methods **once created** | **Always reset at the start of `isValidBST`** |

=== "python"
    ```python
    class Solution:
        def isValidBST(self, root: Optional[TreeNode]) -> bool:
            self.prev = -math.inf  # Reset before each new validation
            return self._inorder_validate(root)

        def _inorder_validate(self, node: Optional[TreeNode]) -> bool:
            if node is None:
                return True

            if not self._inorder_validate(node.left):
                return False

            if node.val <= self.prev:
                return False

            self.prev = node.val

            return self._inorder_validate(node.right)
    ```

=== "python - Iteration"
    ```python
    from collections import deque

    class Solution:
        def isValidBST(self, root: Optional[TreeNode]) -> bool:
            prev_val = -math.inf
            stack = deque()

            node = root
            while node or stack:
                if node:  # Explore left subtree
                    stack.append(node)
                    node = node.left
                else:  # Finish exploring left subtree and continue to right subtree
                    node = stack.pop()
                    if node.val <= prev_val:
                        return False
                    prev_val = node.val
                    node = node.right

            return True
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  We traverse each node once in both recursive and iterative approaches, so the time
  complexity is $O(n)$.
- Space complexity: $O(n)$  
  The recursive function stack depth in the recursive approach and stack size in the
  iterative approach is determined by the height of the tree, $O(h)$.
    - In the worst case (skewed tree), $h = n$.
    - In the best case (balanced tree), $h = \log n$.  
    Therefore, the space complexity is $O(n)$ in the worst case and $O(\log n)$ in the
    best case.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Validate Range (recursion or iteration) | $O(n)$          | $O(n)$
Approach - Inorder validation (recursion or iteration) | $O(n)$          | $O(n)$

## Test
