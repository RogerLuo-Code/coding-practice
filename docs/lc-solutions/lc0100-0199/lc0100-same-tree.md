---
tags:
    - Binary Tree
---

# 100. Same Tree

## Problem Description

[LeetCode Problem 100](https://leetcode.com/problems/same-tree/): Given the roots of
two binary trees `p` and `q`, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical,
and the nodes have the same value.

## Clarification

- Same tree: structurally identical and nodes have the same value

## Assumption

-

## Solution

### Approach 1: Recursion

We can use the same `isSameTree` function to do recursive function calls by checking

- if the current node values are equal
- if the left and right subtrees are the same.

If both conditions are true, we can return `True`. Otherwise, we return `False`.

=== "Python"
    ```python
    class Solution:
        def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
            # Base case: if both trees are empty, they are the same
            if p is None and q is None:
                return True

            if p is None or q is None:
                return False

            if p.val != q.val:
                return False

            # Recursively check if left and right subtrees are the same
            return self.isSameTree(p.left, q.left) and self.isSameTree(p.right, q.right)
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  We visit each node exactly once. The number of nodes is $n$.
- Space complexity: $O(n)$  
  The space is used by the recursive function call stack. The number of recursive calls is
  the height of the tree. In the worst case, the tree is linear and has the height of $n$.
  In the best case, the tree is balanced and has the height of $\log n$.
  So the space complexity is $O(n)$ in the worst case and $O(\log n)$ in the best case.

### Approach 2: Iteration

The problem can also be solved using Breadth-First Search (BFS) by using a queue to store
the pairs of nodes from both trees. We will check if the nodes are the same and then
add their left children pair and right children pair to the queue.

=== "python"
    ```python
    from collections import deque

    class Solution:
        def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
            queue = deque([(p, q)])

            while queue:
                node_p, node_q = queue.popleft()
                if not self.check(node_p, node_q):
                    return False

                if node_p:  # node_q is not None as well, otherwise, it will return in previous step
                    queue.append((node_p.left, node_q.left))
                    queue.append((node_p.right, node_q.right))

            return True

        def check(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
            if p is None and q is None:
                return True

            if p is None or q is None:
                return False

            if p.val != q.val:
                return False

            return True
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  We visit each node exactly once. The number of nodes is $n$.
- Space complexity: $O(n)$  
  The space is used by the queue to store the nodes. In the worst case, the queue will
  store all nodes of one level. The number of nodes at most is $n/2$ for a complete
  binary tree.


### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Recursion | $O(n)$          | $O(n)$
Approach - Iteration | $O(n)$          | $O(n)$

## Test

- Test two empty trees or one empty tree
- Test two trees with different structures
- Test two trees with different values
- Test two trees with the same structure and values