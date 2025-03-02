---
tags:
    - Binary Tree
---

# LC102. Binary Tree Level Order Traversal

## Problem Description

[LeetCode Problem 102](https://leetcode.com/problems/binary-tree-level-order-traversal/):
Given the root of a binary tree, return the level order traversal of its nodes' values.
(i.e., from left to right, level by level).

## Clarification

- level order traversal
- nodes' values
- what's the return value format?

## Assumption

-

## Solution

### Approach - BFS

We can use standard breadth-first search method to solve it. Remember to handle edge
case: empty root.

=== "Python"
    ```python
    from collections import deque


    class Solution:
        def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
            values = []
            if not root:
                return values

            queue = deque([root])
            while queue:
                size = len(queue)
                level_values = []
                for _ in range(size):
                    curr_node = queue.popleft()
                    level_values.append(curr_node.val)
                    if curr_node.left:
                        queue.append(curr_node.left)
                    if curr_node.right:
                        queue.append(curr_node.right)
                values.append(level_values)

            return values
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
    Visit $n$ nodes exact once.
- Space complexity: $O(n)$  
    - queue size is changing but with the max size reached by storing all nodes
    in the last level. The last level contains $n / 2$ nodes.
    - return output contains $n$ values, takes $O(n)$ space.
    - So the total time complexity is $O(n / 2) + O(n) = O(n)$.

## Test
