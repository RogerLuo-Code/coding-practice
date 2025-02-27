---
tags:
    - Binary Tree
---

# LC144. Binary Tree Postorder Traversal

## Problem Description

[LeetCode Problem 144](https://leetcode.com/problems/binary-tree-preorder-traversal/):
Given the `root` of a binary tree, return _the preorder traversal of its nodes' values_.

## Clarification

-

## Assumption

-

## Solution

### Approach - Recursion

We can recursively traverse the tree in post-order by defining a new helper function
`postorder`. In the helper function,

```python
preorder(root.left, values)  # recursively traverse the left subtree
preorder(root.right, values)  # recursively traverse the right subtree
values.append(root.val)  # visit root/parent node
```

=== "Python"
    ```python
    class Solution:
        def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
            values = []
            self.postorder(root, values)
            return values

        def postorder(self, root: Optional[TreeNode], values: list[int]) -> None:
            if root is None:
                return

            self.postorder(root.left, values)
            self.postorder(root.right,values)
            values.append(root.val)
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

### Approach 2 - Iteration (Modified Preorder Traversal)

The preorder traversal visits nodes in order of `root -> left subtree -> right subtree`.
We can modify the order to `root -> right subtree -> left subtree`. After traversing the
entire tree, we can reverse the result list to get the correct postorder sequences
`left subtree -> right subtree -> root`.

=== "python"
    ```python
    class Solution:
        def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
            values = []
            stack = deque()

            curr_node = root
            while curr_node or stack:
                if curr_node:
                    values.append(curr_node.val)
                    stack.append(curr_node)
                    curr_node = curr_node.right  # (1)
                else:
                    curr_node = stack.pop()
                    curr_node = curr_node.left  # (2)

            return values[::-1]  # (3)
    ```

    1. Change preorder order to search the **right** subtree first instead of the left subtree.
    2. Different from preorder, move to left subtree.
    3. Reverse the result list to get the correct postorder sequence.

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
    - Each node (total $n$ nodes) is pushed once to and popped once from the stack. So
    the time complexity of traversal is $O(2n) = O(n)$
    - Reverse the result takes $O(n)$ time.
    - So the **total** time complexity is $O(n) = O(n) + O(n)$.
- Space complexity: $O(n)$  
    - The stack needs to store the right nodes which could be $n$ in the worst case.
    - The return list takes $O(n)$ space to save all node values.
    - The **total** space complexity is $O(n) = O(n) + O(n)$.

### Approach 3 - Iteration

The preorder traversal visits nodes in order of `root -> left subtree -> right subtree`.
We can modify the order to `root -> right subtree -> left subtree`. After traversing the
entire tree, we can reverse the result list to get the correct postorder sequences
`left subtree -> right subtree -> root`.

=== "python"
    ```python
    class Solution:
        def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
            values = []
            stack = deque()

            last_visited = None  # Track the previously processed node
            curr_node = root
            while curr_node or stack:
                if curr_node:  # (1)
                    stack.append(curr_node)
                    curr_node = curr_node.left
                else:
                    peek = stack[-1]  # (2)
                    if peek.right is None or peek.right == last_visited:  # (3)
                        values.append(peek.val)
                        last_visited = stack.pop()  # (4)
                    else:  # (5)
                        curr_node = peek.right

            return values
    ```

    1. Explore the left subtree first.
    2. Get the top node from the stack.
    3. If no right child or the right subtree is visited.
    4. Both its left and right children (if any) are already processed. Mark it as visited so we don't visit it again.
    5. Explore the right subtree.

#### Complexity Analysis of Approach 3

- Time complexity: $O(n)$  
    Each node (total $n$ nodes) is pushed once to and popped once from the stack. So
    the time complexity is $O(n)$.
- Space complexity: $O(n)$  
    - The stack needs to store the right nodes which could be $n$ in the worst case.
    - The return list takes $O(n)$ space to save all node values.
    - The **total** space complexity is $O(n) = O(n) + O(n)$.

### Approach 4 - Morris Traversal

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
                    # (2)
                    predecessor = curr_node.left
                    while predecessor.right and predecessor.right is not curr_node:
                        predecessor = predecessor.right

                    # Two conditions out of while loops
                    if not predecessor.right:  # (3)
                        output.append(curr_node.val)  # (4)
                        predecessor.right = curr_node  # (5)
                        curr_node = curr_node.left
                    else:  # (6)
                        predecessor.right = None  # (7)
                        curr_node = curr_node.right

            return output
    ```

    1. Left is None then add node value to output and go to right since no left sub-tree to visit.
    2. Find predecessor of the current node, the rightmost node of the left sub-tree.
    3. Condition 1: `predecessor.right` is `None`. The left sub-tree is not explored.
    4. This is the root node of a sub-tree. For in-order traversal, add the root node first.
    5. Establish a temporary link from predecessor to current.
    6. Condition 2: `predecessor.right` is the `curr_node`, coming back to the current node from the predecessor. This indicate the left sub-tree has been visited.
    7. Remove the temporary link.

#### Complexity Analysis of Approach 4

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
Approach - Iteration (modified preorder) | $O(n)$          | $O(n)$                     | $O(n)
Approach - Iteration | $O(n)$          | $O(n)$                     | $O(n)

Approach - Morris    | $O(n)$          | $O(n)$                     | $O(1)

## Test

## References

- [Morris Inorder Tree Traversal - Tushar Roy Youtube Channel](https://www.youtube.com/watch?v=wGXB9OWhPTg&list=WL&index=5)
- [Tree traversal - wiki](https://en.wikipedia.org/wiki/Tree_traversal)
- [Binary Tree - My Notes](../../data-structure/binary-tree/binary-tree.md)
