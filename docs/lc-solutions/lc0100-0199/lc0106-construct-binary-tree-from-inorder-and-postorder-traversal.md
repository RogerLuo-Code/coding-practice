---
tags:
    - Binary Tree
    - Divide and Conquer
---

# LC106. Construct Binary Tre from Inorder and Postorder Traversal

## Problem Description

[LeetCode Problem 106](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/):
Given two integer arrays `inorder` and `postorder` where `inorder` is the inorder
traversal of a binary tree and `postorder` is the postorder traversal of the same tree,
construct and return _the binary tree_.

## Clarification

- Use **both** inorder and postorder list to construct the binary tree.

## Assumption

- Inorder and postorder lists are from the same tree.

## Solution

### Approach - Recursion

From observation

- In the preorder list, `[root, left subtree, right subtree]`, the root node is the **first**
node.
- In the inorder list, `[left subtree, root, right subtree]`, the root node is in the **middle**.
- In the postorder list, `[left subtree, right subtree, root]`, the root is the **last**
node.

We can find the root easily from the preorder/postorder list. The root node splits the
inorder list into left and right subtrees. Based on number of nodes in left and right
subtrees, we can also split the preorder/postorder list into left and right subtrees.

We can recursively break down the lists into left subtree, right subtree, and root. Then
link them from bottom up.

=== "Python"
    ```python
    class Solution:
        def buildTree(self, inorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
            # Base cases
            if len(inorder) == 0 and len(postorder) == 0:
                return None

            if len(inorder) == 1 and len(postorder) == 1:
                return TreeNode(inorder[0])

            # Create root from the last element of postorder list (root value)
            root_val = postorder[-1]
            root = TreeNode(root_val)

            # Based on the root, break down inorder list into left and right subtrees
            idx_root_inorder = inorder.index(root_val)
            inorder_left = inorder[0:idx_root_inorder]
            inorder_right = inorder[idx_root_inorder + 1:]

            # Based on the length of left subtree, break down the postorder list
            postorder_left = postorder[0:len(inorder_left)]
            postorder_right = postorder[len(inorder_left):-1]

            # Recursively find the root of left and right subtrees
            left_root = self.buildTree(inorder_left, postorder_left)
            right_root = self.buildTree(inorder_right, postorder_right)

            # Connect root with subtrees
            root.left = left_root
            root.right = right_root

            return root
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n^2)$
    - For each recursion
        - Search for the root index takes $O(n)$.
        - Slices the lists takes $O(k)$, where $k$ is the size of sub-list. In the worst
        case, either left or right sub-list may only reduce by $1$ each recursion.
    - In the worst case, recursion may takes up to $n$ times for a skewed tree.
        - Time complexity due to search is $O(n^2)$.
        - Time complexity due to slicing lists is
        $O(n) + O(n-1) + \cdots + O(1) = O(n^2 / 2) = O(n^2)$.
    - So the total time complexity is $O(n^2) + O(n^2 / 2) = O(n^2)$
- Space complexity: $O(n^2)$
    - Recursive call stack takes $O(n)$ space. The recursion depth is equal to the
    height of the tree. In the worst case, the
    height is $n$.
    - List slicing takes $O(n^2)$ space. Each recursion call creates new slices of
    inorder and postorder lists, which takes $O(k)$ space per level space. In the worst
    case, the size of $k$ is reduced by 1 after each recursion. So the space complexity
    is $O(n) + O(n - 1) + \cdots + O(1) = O(n^2 / 2)$.
    - So the total space complexity is $O(n^2) + O(n^2 / 2) = O(n^2)$.

### Approach 2 - Optimized Recursion

We can optimize the solution 1 by

- Uses a hashmap for quick lookup
    - A **dictionary** (`inorder_index_map`) stores the index of each node in `inorder`
    for $O(1)$ lookups, eliminating the $O(n)$ `.index` search in each recursion.
- Avoids list slicking:
    - Instead of creating new lists of `inorder_left`, `inorder_right`, etc., we
    **pass index ranges** to `build` , reducing unnecessary time and space usage.

=== "python"
    ```python
    class Solution:
        def __init__(self):
            self.inorder_index_map = {}

        def buildTree(self, inorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
            self.inorder_index_map = {val: idx for idx, val in enumerate(inorder)}  # O(n) time and O(n) space
            return self.build(inorder, postorder, 0, len(inorder) - 1, 0, len(postorder) - 1)

        def build(self, inorder: list[int], postorder: list[int], in_left: int, in_right: int, post_left: int, post_right: int) -> Optional[TreeNode]:
            # Base cases (empty list)
            if in_left > in_right or post_left > post_right:
                return None

            # Root value is the last element in postorder
            root_val = postorder[post_right]
            root = TreeNode(root_val)

            # Get index of root in inorder list
            idx_inorder_root = self.inorder_index_map[root_val]

            # Number of nodes in left subtree
            left_size = idx_inorder_root - in_left

            # Recursively construct left and right subtrees
            root.left = self.build(inorder, postorder, in_left, idx_inorder_root - 1, post_left, post_left + left_size - 1)
            root.right = self.build(inorder, postorder, idx_inorder_root + 1, in_right, post_left + left_size, post_right - 1)  # pos_right - 1 to exclude the root in the end

            return root
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$
    - Building dictionary `inorder_index_map` takes $O(n)$ time.
    - Recursive calls takes $O(n)$ since each node processed onces and take $O(1)$ for
    each recursion.
    - So the total time complexity is $O(n)$.
- Space complexity: $O(n)$
    - Recursive call stack takes $O(n)$ in the worst case.
    - The dictionary `inorder_index_map` takes $O(n)$.
    - So the total space complexity is $O(n)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Recursion | $O(n^2)$          | $O(n^2)$
Approach - Optimized Recursion | $O(n)$          | $O(n)$

## Test

- Single-node tree (`[1]`) → Should return `TreeNode(1)`.
- Left-skewed tree (`inorder == postorder`) → Handles correctly.
- Right-skewed tree → Works efficiently.
