---
tags:
    - Binary Tree
    - Breadth-First Search
---

# LC117. Populating Next Right Pointers in Each Node II

## Problem Description

[LeetCode Problem 117](https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/):
Given a binary tree

```C
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
```

Populate each next pointer to point to its next right node. If there is no next right
node, the next pointer should be set to `NULL`.

Initially, all next pointers are set to `NULL`.

## Clarification

- Binary tree is not perfect and may miss left, right, or both nodes.

## Assumption

-

## Solution

### Approach 1: Level Order Traversal

The same level order traversal solution from [LC116](./lc0116-populating-next-right-pointers-in-each-node.md#approach-1-level-order-traversal)
can be applied here. No matter whether the binary tree is perfect or not.

### Approach 2: Using established next pointers in the upper level

We can use the same idea from [LC116](./lc0116-populating-next-right-pointers-in-each-node.md#approach-2-use-established-next-pointers-in-upper-level):
Only move on to the next level when completing establishing the next pointers for the
current level. We can use these next pointers to establish the connections for the next level.

Since the tree is not perfect, we need to have some way to find the left most node of
the next level. The `dummy` node usage from [@davidtan1890](https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/solutions/37811/simple-solution-using-constant-space/)
is a really smart way to store the left most node of
the next level without using if/else conditions check.

=== "python"
    ```python
    class Solution:
        def connect(self, root: 'Node') -> 'Node':
            if not root:
                return None

            dummy = Node(-1)  # dummy node, the next node stores the head of the next level
            prev = dummy  # the previous node on the next level
            curr = root  # current node of current level
            while curr:
                # Explore the current level first
                # Check left child
                if curr.left:
                    prev.next = curr.left
                    prev = prev.next
                # Check right child
                if curr.right:
                    prev.next = curr.right
                    prev = prev.next
                # Move to the next node of the current level
                curr = curr.next

                # Move to the next level if reaching the end of the current level
                if curr is None:
                    curr = dummy.next

                    # Reset dummy.next and prev to store for next level.
                    dummy.next = None
                    prev = dummy

            return root
    ```

=== "python - no dummy"
    ```python
    class Solution:
        def connect(self, root: 'Node') -> 'Node':
            if not root:
                return None

            left_most = None  # head of the next level
            prev = None  # the leading node on the next level
            curr = root  # current node of current level
            while curr:
                # Explore the current level first
                # Check left child
                if curr.left:
                    if prev:
                        prev.next = curr.left
                    else:
                        left_most = curr.left
                    prev = curr.left
                # Check right child
                if curr.right:
                    if prev:
                        prev.next = curr.right
                    else:
                        left_most = curr.right
                    prev = curr.right
                # Move to the next node of the current level
                curr = curr.next

                # Move to the next level if reaching the end of the current level
                if curr is None:
                    curr = left_most
                    left_most = None
                    prev = None

            return root
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
    Explore each node exactly once.
- Space complexity: $O(1)$  
    Just use limited number of variables.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Level Order Traversal | $O(n)$          | $O(n)$
Approach - Use Established Next Connections | $O(n)$          | $O(1)$

## Test
