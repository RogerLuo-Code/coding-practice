---
tags:
    - Binary Tree
---

# LC250. Count Univalue Subtrees

## Problem Description

[LeetCode Problem 250](https://leetcode.com/problems/count-univalue-subtrees/description/):
Given the `root` of a binary tree, return _the number of **uni-value**_ _subtrees_.

A **uni-value subtree** means all nodes of the subtree have the same value.

## Clarification

- Not only direct children but all children to have the same values.
- Leaf nodes are uni-value subtree.

## Assumption

-

## Solution

### Approach - Recursion

Bases on the definition, a univalue subtree meets the following criteria:

1. The children are also uni-value subtrees.
2. The children have the same value as the current node.

**Leaf nodes** automatically meets above two conditions since it contains only that node.

We can recursively iterate through left and right children of each node to see if the
children from uni-value subtrees. We can increase the count if all children are from
uni-value subtrees and have the same value as the current node.

To facility recursively check and count, the function will return `(count, is_univalue_subtree)`.

=== "Python"
    ```python
    class Solution:
        def countUnivalSubtrees(self, root: Optional[TreeNode]) -> int:
            count, is_univalue = self.count_check_univalue_tree(root)
            return count

        def count_check_univalue_tree(self, root: Optional[TreeNode]) -> tuple[int, bool]:
            if root is None:
                return (0, True)

            if root.left is None and root.right is None:
                return (1, True)

            left_count, is_left_univalue = self.count_check_univalue_tree(root.left)
            right_count, is_right_univalue = self.count_check_univalue_tree(root.right)

            if (
                is_left_univalue
                and is_right_univalue
                and (root.left is None or root.val == root.left.val)
                and (root.right is None or root.val == root.right.val)
            ):
                return (left_count + right_count + 1, True)
            else:
                return (left_count + right_count, False)
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  Each node is visited once. The total number of nodes is $n$.
- Space complexity: $O(n)$  
  The maximum recursive function call stack would be the tree's height, which in the
  worst case would be $O(n)$ when the tree is a straight line.

## Test

- Test empty root. It should return 0.
- Test root that is also a leaf node. It should return 1.
- Test normal uni-value tree.
- Test a tree not a uni-value tree.
