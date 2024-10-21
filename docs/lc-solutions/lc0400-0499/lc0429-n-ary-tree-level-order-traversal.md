---
tags:
    - Breadth-First Search
---

# LC429. N-ary Tree Level Order Traversal

## Problem Description

[LeetCode Problem 429](https://leetcode.com/problems/n-ary-tree-level-order-traversal/): Given an n-ary tree, return the _level order_ traversal of its nodes' values.

_Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples)._

## Clarification

- Does the node always have a valid value?

## Assumption

-

## Solution

### Approach - BFS

Use Breadth-First Search (BFS) to traverse the n-ary tree. No need to use visited since it is a n-ary tree and traversing level by level.

=== "Python"
    ```python
    class Solution:
        def levelOrder(self, root: 'Node') -> List[List[int]]:
            results = []
            if not root:
                return results

            queue = deque([root])
            while queue:
                level = []
                for _ in range(len(queue)):
                    node = queue.popleft()
                    level.append(node.val)
                    queue.extend(node.children)

                results.append(level)  # (1)

            return results
    ```

    1. Can also use for-loop as well.
    ```
    for child in node.children:
        queue.append(child)
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  Process total $n$ nodes exact once and each node takes $O(1)$ time. So the total time complexity is $O(n)$. 
- Space complexity: $O(n)$  
  In the worst case, most of nodes ($n-1$) are in one level, so the time complexity is $O(n)$.

## Test
