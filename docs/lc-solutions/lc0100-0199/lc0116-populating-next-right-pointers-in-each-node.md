---
tags:
    - Breadth-First Search
---

# LC116. Populating Next Right Pointers in Each Node

## Problem Description

[LeetCode Problem 116](https://leetcode.com/problems/populating-next-right-pointers-in-each-node): You are given a **perfect binary tree** where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to `NULL`.

Initially, all next pointers are set to `NULL`.

## Clarification

- Perfect binary tree
- What does it mean to populate each next pointer to point to its next right node?
  binary tree alreay uses left and right. Update the next node to point to the right node. If not exist, set it to Null

## Assumption

-

## Solution

### Approach - BFS

Solution

=== "Python"
    ```python
    class Solution:
        def connect(self, root: 'Optional[Node]') -> 'Optional[Node]':
            if not root:
                return root

            queue = deque([root])

            while queue:
                size = len(queue)
                for i in range(size):
                    node_i = queue.popleft()

                    # Update next node
                    if i < size - 1:
                        node_i.next = queue[0]

                    # Add left and right nodes to the queue
                    if node_i.left:
                        queue.append(node_i.left)
                    if node_i.right:
                        queue.append(node_i.right)

            return root
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(1)$  
  Explanation
- Space complexity: $O(n)$  
  Explanation

### Approach2 -

Solution

=== "python"
    ```python
    code
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(1)$  
  Explanation
- Space complexity: $O(n)$  
  Explanation

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach -  |  $O(1)$           | $O(n)$ |
Approach -  |  $O(1)$           | $O(n)$  |

## Test
