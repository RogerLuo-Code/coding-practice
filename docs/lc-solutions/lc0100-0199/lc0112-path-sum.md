---
tags:
    - Binary Tree
---

# LC112. Path Sum

## Problem Description

[LeetCode Problem 112](https://leetcode.com/problems/path-sum/): Given the `root` of a
binary tree and an integer `targetSum`, return `true` if the tree has a **root-to-leaf**
path such that adding up all the values along the path equals `targetSum`.

A **leaf** is a node with no children.

## Clarification

- root-to-leaf not root-to-any-node
- leaf node definition: node with no children

## Assumption

-

## Solution

### Approach - Recursion

We can use the same `hasPathSum` function to do recursive function calls by subtracting
`targetSum` from the current node value.

=== "Python"
    ```python
    class Solution:
        def hasPathSum(self, root: Optional[TreeNode], targetSum: int) -> bool:
            if root is None:  # include empty root, empty left node, or empty right node
                return False

            targetSum -= root.val
            if root.left is None and root.right is None:  # check leaf node
                return targetSum == 0

            return self.hasPathSum(root.left, targetSum) or self.hasPathSum(root.right, targetSum)
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
    We visit each node exactly once. The number of nodes is $n$.
- Space complexity: $O(n)$  
    The space is used by recursive function call stack. The number of recursive calls is
    the height of the tree. In the worst case, the tree is linear and has the height of $n$.

### Approach 2 - Iteration

The problem can also be solved using Breadth-First Serach (BFS) by using a queue store
`(node, sum)` pairs.

=== "python"
    ```python
    from collections import deque


    class Solution:
        def hasPathSum(self, root: Optional[TreeNode], targetSum: int) -> bool:
            if root is None:  # include empty root, empty left node, or empty right node
                return False

            targetSum -= root.val
            if root.left is None and root.right is None:  # check leaf node
                return targetSum == 0

            return self.hasPathSum(root.left, targetSum) or self.hasPathSum(
                root.right, targetSum
            )

        def bfs(self, root: Optional[TreeNode], targetSum: int) -> bool:
            queue = deque()
            if root:
                queue.append((root, 0))  # (node, sum)

            while queue:
                curr_node, curr_sum = queue.popleft()

                if (
                    curr_node.left is None
                    and curr_node.right is None
                    and curr_sum == target_sum
                ):
                    return True

                if curr_node.left:
                    queue.append((curr_node.left, curr_sum + curr_node.left.val))
                if curr_node.right:
                    queue.append((curr_node.right, curr_sum + curr_node.right.val))

            return False
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
    In the worst case, it goes through all $n$ nodes.
- Space complexity: $O(n)$  
    The largest queue size is the number of nodes in the last level, which could be
    $n / 2$ in the worst case.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Recursion | $O(n)$          | $O(n)$
Approach - Iteration | $O(n)$          | $O(n)$

## Test

- Test empty root.
- Test normal case where target sum exists.
- Test a case where no target sum exists.
