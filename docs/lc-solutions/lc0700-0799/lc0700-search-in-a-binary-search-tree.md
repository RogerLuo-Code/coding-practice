---
tags:
    - Binary Search Tree
---

# 700. Search in a Binary Search Tree

## Problem Description

[LeetCode Problem 700](https://leetcode.com/problems/search-in-a-binary-search-tree/description/):
You are given the `root` of a binary search tree (BST) and an integer `val`.

Find the node in the BST that the node's value equals `val`and return the subtree rooted
with that node. If such a node does not exist, return `null`.

## Clarification

- BST Definition

## Assumption

-

## Solution

Implemented solutions based on binary search tree property

- smaller keys in the left subtree
- larger keys in the right subtree

### Approach 1: Recursion

We can solve the problem using recursion.

=== "Python"
    ```python
    class Solution:
    def searchBST(self, root: Optional[TreeNode], val: int) -> Optional[TreeNode]:
        # Base case
        if root is None or root.val == val:
            return root

        # Recursively serach either left or right subtree
        if root.val < val:
            return self.searchBST(root.right, val)
        else:
            return self.searchBST(root.left, val)
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  The time complexity is $O(h)$, depends on the tree height, $h$. In the worst case, it
  is $O(n)$. On average, it could be $O(\log n)$ since every search only search half of
  the tree.
- Space complexity: $O(n)$  
  The recursion call stack takes $O(h)$ space. In the worst case, it is $O(n)$.

### Approach 2: Iteration

The problem can be solved using iteration, which will reduce space complexity to $O(1)$.

=== "python"
    ```python
    class Solution:
        def searchBST(self, root: Optional[TreeNode], val: int) -> Optional[TreeNode]:
            curr_node = root

            while curr_node:
                if curr_node.val == val:
                    return curr_node
                elif curr_node.val < val:
                    curr_node = curr_node.right
                else:
                    curr_node = curr_node.left

            return None  # not find the target value
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  Similar to recursion, the time complexity in the worst case is $O(n)$.
- Space complexity: $O(n)$  
  Only use `curr_node`.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Recursion | $O(n)$          | $O(n)$
Approach - Iteration | $O(n)$          | $O(1)$

## Test

- Test empty root.
- Test `val` in the tree.
- Test `val` not in the tree.
