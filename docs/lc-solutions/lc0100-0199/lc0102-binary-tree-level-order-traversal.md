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

### Approach 1 - BFS

We can use breadth-first search (BFS) to traverse the tree level by level. Add values
of each level to a list and append it to the result list. Remember to handle edge case:
empty root.

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

### Approach 2: DFS

We can also use depth-first search (DFS) to traverse the tree by using a helper function.
The helper function will take the current node and **the current level** as arguments. It
will recursively traverse the tree and add the values of each level to corresponding
position in the list. This approach ensures that we maintain the order of nodes at
each level.

=== "python"
    ```python
    class Solution:
        def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
            results = []
            self.levelHelper(root, 0, results)
            return results

        def levelHelper(self, node: Optional[TreeNode], height: int, results: List[List[int]]) -> None:
            # Base case
            if node is None:
                return

            # Expand results for new level
            if len(results) <= height:
                results.append([])

            results[height].append(node.val)
            self.levelHelper(node.left, height + 1, results)
            self.levelHelper(node.right, height + 1, results)
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  The algorithm visits each node exactly once, so the time complexity is $O(n)$.
- Space complexity: $O(n)$  
    - Recursion stack space is $O(h)$, where $h$ is the height of the tree. In the
    worst case, the height of the tree can be $n$ (for a skewed tree), so the space
    complexity is $O(n)$.
    - The output list `results` will contain $n$ values, so the space complexity is $O(n)$.
    - So the total space complexity is $O(n) + O(h) = O(n)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach 1 - BFS | $O(n)$          | $O(n)$
Approach 2 - DFS | $O(n)$          | $O(n)$

## Test

- Test empty tree
- Test single node tree
- Test two levels tree
