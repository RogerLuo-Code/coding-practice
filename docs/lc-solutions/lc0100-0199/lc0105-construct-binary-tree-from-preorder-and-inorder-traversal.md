---
tags:
    - Binary Tree
    - Divide and Conquer
---

# LC105. Construct Binary Tree from Preorder and Inorder Traversal

## Problem Description

[LeetCode Problem 105](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/):
Given two integer arrays `preorder` and `inorder` where `preorder` is the preorder
traversal of a binary tree and `inorder` is the inorder traversal of the same tree,
construct and return _the binary tree_.

## Clarification

- Return root node of binary tree?

## Assumption

- Both preorder and inorder lists are for the same tree.

## Solution

### Approach - Optimized Recursion

We can follow the similar **optimized** recursion method from [LC106](./lc0106-construct-binary-tree-from-inorder-and-postorder-traversal.md)
based on the following observations:

- In the preorder list, `[root, left subtree, right subtree]`, the root node is the **first**
node.
- In the inorder list, `[left subtree, root, right subtree]`, the root node is in the **middle**.

We can find the root easily from the preorder list. The root node splits the
inorder list into left and right subtrees. We can recursively break down the lists into
left subtree, right subtree, and root. Then
link them from bottom up.

=== "Python"
    ```python
    class Solution:
        def __init__(self):
            self.inorder_index_map = {}

        def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
            self.inorder_index_map = {val: idx for idx, val in enumerate(inorder)}
            return self.build(preorder, inorder, 0, len(preorder) - 1, 0, len(inorder) - 1)

        def build(
            self,
            preorder: List[int],
            inorder: List[int],
            pre_left: int,
            pre_right: int,
            in_left: int,
            in_right: int,
        ) -> Optional[TreeNode]:
            # Base case
            if pre_left > pre_right or in_left > in_right:
                return None

            # The first value of preorder list is the root
            root_val = preorder[pre_left]
            root = TreeNode(root_val)

            # Find index of root in the inorder list
            idx_inorder_root = self.inorder_index_map[root_val]
            left_size = idx_inorder_root - in_left

            # Recursively break down the lists in two left and right subtrees
            root.left = self.build(
                preorder,
                inorder,
                pre_left + 1,
                pre_left + left_size,
                in_left,
                idx_inorder_root - 1,
            )  # `pre_left + 1` to exclude the root
            root.right = self.build(
                preorder,
                inorder,
                pre_left + left_size + 1,
                pre_right,
                idx_inorder_root + 1,
                in_right,
            )

            return root
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$
    - Building dictionary `inorder_index_map` takes $O(n)$ time.
    - Recursive calls takes $O(n)$ since each node processed onces and take $O(1)$ for
    each recursion.
    - So the total time complexity is $O(n)$.
- Space complexity: $O(n)$
    - Recursive call stack takes $O(n)$ in the worst case.
    - The dictionary `inorder_index_map` takes $O(n)$.
    - So the total space complexity is $O(n)$.

## Test

- Single-node tree (`[1]`) → Should return `TreeNode(1)`.
- right-skewed tree (`inorder == preorder`) → Handles correctly.
- Left-skewed tree → Works efficiently.
