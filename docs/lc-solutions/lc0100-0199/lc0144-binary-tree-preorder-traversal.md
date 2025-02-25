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
    - The stack needs to store the right nodes which could be $n$ in the worst case.
    - The return list takes $O(n)$ space to save all node values.
    - The **total** space complexity is $O(n) = O(n) + O(n)$.

### Approach 3 - Morris Traversal

We can use Morris Traversal to visit nodes by using temporary links instead of using
recursion and stack. It modifies the tree temporarily. The general idea is to

- Before exploring the left tree, find the **rightmost** node in the **left** tree.
That's also the **last** node to visit in the left tree.
- Establish a **temporary** link between the rightmost node and the current node. So it can
come back after exploring the left tree.
- Then explore the left tree (use similar approach). When it comes back to the current
node with the temporary link, it indicates the left sub-tree has visited.

=== "python"
    ```python
    class Solution:
        def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
            output = []
            curr_node = root
            while curr_node:
                if not curr_node.left:  # (1)
                    output.append(curr_node.val)
                    curr_node = curr_node.right
                else:
                    # Find predecessor of the current node.
                    predecessor = curr_node.left  # (2)
                    # (3)
                    while predecessor.right and predecessor.right is not curr_node:
                        predecessor = predecessor.right

                    if not predecessor.right:
                        output.append(curr_node.val)
                        predecessor.right = curr_node  # (4)
                        curr_node = curr_node.left
                    else:  # (5)
                        predecessor.right = None  # (6)
                        curr_node = curr_node.right

            return output
    ```

    1. Left is None then add node value to output and go to right.
    2. Go to the left first.
    3. Find the rightmost node in the left sub-tree.
    4. Establish a temporary link from predecessor to current.
    5. Comes back to the current node from the predecessor. This indicate the left tree is already visited.
    6. Remove the temporary link.

#### Complexity Analysis of Approach 3

- Time complexity: $O(n)$  
    We visit each node twice, one for establishing link and one for removing. Therefore
    the time complexity is $O(n)$.
- Space complexity: $O(n)$  
    - Visit nodes taking $O(1)$ space.
    - The return list takes $O(n)$ space to save all node values.
    - The **total** space complexity is $O(n) = O(1) + O(n)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach             | Time Complexity | Space Complexity (Overall) | Space Complexity (Visit)
---------------------|-----------------|----------------------------|-------------------------
Approach - Recursion | $O(n)$          | $O(n)$                     | $O(n)
Approach - Iteration | $O(n)$          | $O(n)$                     | $O(n)
Approach - Morris    | $O(n)$          | $O(n)$                     | $O(1)

## Test

## References

- [Morris Inorder Tree Traversal - Tushar Roy Youtube Channel](https://www.youtube.com/watch?v=wGXB9OWhPTg&list=WL&index=5)
- [Tree traversal - wiki](https://en.wikipedia.org/wiki/Tree_traversal)
- [Binary Tree - My Notes](../../data-structure/binary-tree/binary-tree.md)
