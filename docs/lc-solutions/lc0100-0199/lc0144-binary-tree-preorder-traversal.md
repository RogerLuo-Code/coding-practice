---
tags:
    - Binary Tree
---

# LC144. Binary Tree Preorder Traversal

## Problem Description

[LeetCode Problem 144](https://leetcode.com/problems/binary-tree-preorder-traversal/):
Given the `root` of a binary tree, return _the preorder traversal of its nodes' values_.

## Clarification

-

## Assumption

-

## Solution

### Approach - Recursion

We can recursively traverse the tree in pre-order by defining a new helper function
`preorder`. In the helper function,

```python
values.append(root.val)  # visit root/parent node
preorder(root.left, values)  # recursively traverse the left subtree
preorder(root.right, values)  # recursively traverse the right subtree
```

=== "Python"
    ```python
    class Solution:
        def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
            value_list = []
            self.preorder(root, value_list)
            return value_list

        def preorder(self, root: Optional[TreeNode], value_list: List[int]) -> None:
            if root is None:
                return

            value_list.append(root.val)
            self.preorder(root.left, value_list)
            self.preorder(root.right, value_list)
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
    The algorithm will visit all nodes exact once via recursive function call and
    therefore the time complexity is $O(n)$.
- Space complexity: $O(n)$  
    - Recursive function call takes $O(h)$ space for the call stack. The $h$ is the height
    of the binary tree, which could be the total number of nodes $n$ in the worst case.
    - The return list takes $O(n)$ space to save all node values.
    - The **total** space complexity is $O(n) = O(h) + O(n)$.

### Approach 2 - Iteration

We can also iteratively traverse the tree, traverse the root and left first and use
stack to store right nodes that will be visited later.

=== "python"
    ```python
    class Solution:
        def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
            value_list = []
            stack = deque()

            node = root
            while node or stack:
                if node is None:
                    node = stack.pop()

                value_list.append(node.val)
                if node.right is not None:
                    stack.append(node.right)
                node = node.left

            return value_list
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
    The algorithm access each node exact once and therefore the time complexity is $O(n)$.
- Space complexity: $O(n)$  
  The stack needs to store the right nodes which could be $n$ in the worst case.
  Therefore the space complexity is $O(n)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach             | Time Complexity | Space Complexity (Overall) | Space Complexity (Visit)
---------------------|-----------------|----------------------------|-------------------------
Approach - Recursion | $O(n)$          | $O(n)$                     | $O(n)
Approach - Iteration | $O(n)$          | $O(n)$                     | $O(n)

## Test

## References
- [Morris Inorder Tree Traversal - Tushar Roy Youtube Channel](https://www.youtube.com/watch?v=wGXB9OWhPTg&list=WL&index=5)
- [Tree traversal - wiki](https://en.wikipedia.org/wiki/Tree_traversal)
- [Binary Tree - My Notes](../../data-structure/binary-tree/binary-tree.md)
