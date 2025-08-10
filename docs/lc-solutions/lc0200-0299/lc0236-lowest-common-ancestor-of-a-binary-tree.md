---
tags:
    - Binary Tree
---

# LC236. Lowest Common Ancestor of a Binary Tree

## Problem Description

[LeetCode Problem 236](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/):
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the [definition of LCA on Wikipedia](https://en.wikipedia.org/wiki/Lowest_common_ancestor):
“The lowest common ancestor is defined between two nodes `p` and `q`as the lowest node
in `T` that has both `p` and `q` as descendants (where we allow
**a node to be a descendant of itself**).”

## Clarification

- lowest common ancestor definition:
    - the lowest node that has both `p` and `q` as descendants
    - a node can be descendant of itself

## Assumption

- `root`, `p`, and `q` are not None.

## Solution

### Approach 1: Recursion

We can recursively traverse the left and right subtrees and determine whether `p` and
`q` are located in relation to the current node (bottom-up approach):

1. If either `p` or `q` is found at the current node, then this node could be an LCA.
2. If both `p` and `q` are found in different subtrees of a node, then the node is the LCA.
3. If `p` and `q` are found in the same subtree, the LCA is that subtree and the other
subtree will return `None`.

=== "Python"
    ```python
    class Solution:
        def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
            # Base case
            if root is None or root == p or root == q:
                return root

            # Traverse left and right subtrees
            left = self.lowestCommonAncestor(root.left, p, q)
            right = self.lowestCommonAncestor(root.right, p, q)

            # Nodes are in different subtrees, so the current root is the lowest common ancestor.
            if left and right:
                return root

            # Handle two cases:
            # - one node is the descendant of the other
            # - not finding either p or q, return none
            return left if left else right
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  In the worse case, each node is visited once.
- Space complexity: $O(n)$  
  In the worst case (e.g., skewed trees), the recursive function call stack depth is $O(n)$.

### Approach 2: Iteration with Stack

We can use iterative solution by using a **stack** for tree traversal and a **hash table**
to store parent relationships.

1. Traverse the tree and store parent pointers for each node using a hash table.
2. Find ancestors of `p` and store them in a set.
3. Trace up from `q` until we find the first common ancestor in the set.

=== "python"
    ```python
    class Solution:
        def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
            stack = [root]  # stack for traversal
            parent = {root: None}  # node -> parent

            # Use DFS to build parent dictionary until both nodes' parents are found
            while p not in parent or q not in parent:
                node = stack.pop()
                if node.left:
                    parent[node.left] = node
                    stack.append(node.left)
                if node.right:
                    parent[node.right] = node
                    stack.append(node.right)

            # Ancestors of node p (remove duplicates)
            ancestors = set()
            curr = p
            while curr:
                ancestors.add(curr)
                curr = parent[curr]  # Move up to the parent

            # Find the first ancestor of q that appears in the p's ancestors,
            # which is the lowest common ancestor.
            curr = q
            while curr not in ancestors:
                curr = parent[curr]

            return curr
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$
    - In the worse case, traverse the tree once to build the parent mapping, which
    takes $O(n)$.
    - Find ancestors of both `p` and `q`, at most $O(h)$ (where $h$ is the tree height).
    In the worst case it is $O(n)$.
    - So the overall time complexity is $O(n) + O(n) = O(n)$.
- Space complexity: $O(n)$
    - Stack: in the worst case, it holds $n$ nodes (skewed tree).
    - Ancestor set: stores $h$ nodes, in the worst case, it stores $n$ nodes.
    - Parent hash table: stores at most $n$ nodes.
    - So the overall space complexity is $O(n) + O(n) + O(n) = O(n)$.

Note that

- Parent hash table allows efficient look of parent nodes in $O(1)$
- Ancestor set ensures fast ancestor checking in $O(1)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Recursion | $O(n)$          | $O(n)$
Approach - Iteration | $O(n)$          | $O(n)$

## Test

## References

- [Lowest Common Ancestor Binary Tree - Tushar Roy Youtube Channel](https://www.youtube.com/watch?v=13m9ZCB8gjw)
