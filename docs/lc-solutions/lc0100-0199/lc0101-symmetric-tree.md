---
tags:
    - Binary Tree
---

# LC101. Symmetric Tree

## Problem Description

[LeetCode Problem 101](https://leetcode.com/problems/symmetric-tree/): Given the `root`
of a binary tree, _check whether it is a mirror of itself_ (i.e., symmetric around its center).

## Clarification

- Mirror definition:
    - symmetric around its center/root (values are symmetric).
    - left subtree is a mirror reflection of the right subtree.
- What to return for an empty root? Return true.

## Assumption

-

## Solution

### Approach - Iteration

We can check mirroring by using two queues:

- **left queue** to store nodes in the left
subtree with pushing order like left - > right.
- **right queue** to store nodes in the right subtree with **reversed** pushing order
(right -> left).

Then we can compare nodes one at a time from both queues. if any node is empty or values
are not equal, the tree is not symmetric.

=== "Python"
    ```python
    from collections import deque


    class Solution:
        def isSymmetric(self, root: Optional[TreeNode]) -> bool:
            left_queue = deque()
            right_queue = deque()

            if not root:
                return False

            left_queue.append(root.left)
            right_queue.append(root.right)

            while left_queue and right_queue:
                left_size = len(left_queue)
                right_size = len(right_queue)

                if left_size != right_size:
                    return False

                for _ in range(left_size):
                    left_node = left_queue.popleft()
                    right_node = right_queue.popleft()

                    if left_node is None and right_node is None:
                        continue

                    if (
                        left_node is None
                        or right_node is None
                        or (left_node.val != right_node.val)
                    ):
                        return False

                    # For left queue, pushing order is left -> right
                    left_queue.append(left_node.left)
                    left_queue.append(left_node.right)

                    # For right queue, reverse pushing order to right -> left for symmetric comparison
                    right_queue.append(right_node.right)
                    right_queue.append(right_node.left)

            return True
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
    Traverse the entire tree with $n$ nodes.
- Space complexity: $O(n)$  
    The total size of two queues is the number of nodes in the last level. In the worst
    case, there are $n / 2$ nodes in the last level. Som the space complexity is $O(n)$.

### Approach 2 - Recursion

A tree is symmetric if the left subtree is a mirror reflection of the right subtree. Two
trees are a mirror reflection of each other if:

1. Their two roots have the same value.
2. The right subtree of each tree is a mirror reflection of the left subtree of the
other tree.

We can use recursive method to check mirroring.

=== "python"
    ```python
    class Solution:
        def isSymmetric(self, root: Optional[TreeNode]) -> bool:
            return self.is_mirror(root, root)

        def is_mirror(self, t1: Optional[TreeNode], t2: Optional[TreeNode]) -> bool:
            if t1 is None and t2 is None:
                return True

            if t1 is None or t2 is None:
                return False

            return (
                t1.val == t2.val
                and self.is_mirror(t1.left, t2.right)
                and self.is_mirror(t1.right, t2.left)
            )
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
    It traverses the entire input tree with $n$ nodes in the worst case.
- Space complexity: $O(n)$  
  The space is used by recursive function call stack. The number of recursive class is
  bounded by the height of the tree. In the worst case, the tree is linear and the
  height is $O(n)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Iteration | $O(n)$          | $O(n)$
Approach - Recursion | $O(n)$          | $O(n)$

## Test

- Test empty root
- Tes simple case, root with same left and right and different left and right.
- Test simple case where root is symmetric
- Test simple case where root is not symmetric but have the same node values
