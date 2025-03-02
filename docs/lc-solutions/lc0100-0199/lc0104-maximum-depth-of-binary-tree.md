---
tags:
    - Binary Tree
---

# LC104. Maximum Depth of Binary Tree

## Problem Description

[LeetCode Problem 104](https://leetcode.com/problems/maximum-depth-of-binary-tree/):
Given the `root` of a binary tree, return _its maximum depth_.

A binary tree's **maximum depth** is the number of nodes along the longest path from the
root node down to the farthest leaf node.

## Clarification

- maximum depth definition: number of nodes along the longest path

## Assumption

-

## Solution

### Approach - Recursion

We can find the maximum depth of the current node based on the maximum depth of left and
right subtrees.

=== "Python"
    ```python
    class Solution:
        def maxDepth(self, root: Optional[TreeNode]) -> int:
            if not root:
                return 0

            left_depth = self.maxDepth(root.left)
            right_depth = self.maxDepth(root.right)
            return max(left_depth, right_depth) + 1
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
    Each node is visited once and thus the time complexity is $O(n)$.
- Space complexity: $O(n)$  
    The function call stack goes as deep as the height of the tree. In the worst case,
    the tree depth is $n$ (e.g., each noe has only one left child node).

### Approach 2 - BFS

The problem can be solved using breadth-first search by traversing the tree level by
level. Each level corresponds to a depth in the tree. We increase the depth only when
we finish processing all nodes at a given level.

=== "python"
    ```python
    from collections import deque


    class Solution:
        def maxDepth(self, root: Optional[TreeNode]) -> int:
            queue = deque()
            if root:
                queue.append(root)

            depth = 0
            while queue:
                size = len(queue)
                for _ in range(size):
                    curr_node = queue.popleft()
                    if curr_node.left:
                        queue.append(curr_node.left)
                    if curr_node.right:
                        queue.append(curr_node.right)
                depth += 1

            return depth
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
    Each node is visited exactly once. So the time complexity is $O(n)$.
- Space complexity: $O(n)$  
    The queue doesn't hold all nodes at once, but at its **peak**, it holds the
    **widest** level of the tree, i.e., the last level. For a full binary tree, the
    total depth is $h = \log_2(n)$ and the last level contains $n / 2$ nodes. So the
    space complexity is $O(n / 2) = O(n)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach             | Time Complexity | Space Complexity
---------------------|-----------------|-----------------
Approach - Recursion | $O(n)$          | $O(n)$
Approach - BFS       | $O(n)$          | $O(n)$

## Test
