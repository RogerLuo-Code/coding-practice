---
tags:
    - Binary Tree
---

# LC144. Binary Tree Postorder Traversal

## Problem Description

[LeetCode Problem 144](https://leetcode.com/problems/binary-tree-postorder-traversal/):
Given the `root` of a binary tree, return _the postorder traversal of its nodes' values_.

## Clarification

-

## Assumption

-

## Solution

### Approach - Recursion

We can recursively traverse the tree in post-order by defining a new helper function
`postorder`. In the helper function,

```python
postorder(root.left, values)  # recursively traverse the left subtree
postorder(root.right, values)  # recursively traverse the right subtree
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
    3. Append root value when no right child or the right subtree is visited.
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

We can use Morris traversal similar to what used in
[preorder traversal](lc0144-binary-tree-preorder-traversal.md#approach-3-morris-traversal)
but with two main changes:

- **Create a dummy root** to ensure the root node is processed.
    - In postorder traversal, the root is processed last.
    - In Morris traversal, the node is processed when removing the
temporary link from its predecessor but the real root has no predecessor.
- Need to **reverse the path** before appending values.
    - Morris traversal ensures we visit the left subtree before processing the root and right.
    - When collecting the right subtree, Morris traversal naturally returns the right
    subtree in `root -> right` order.
    - So need to reversing the collected right subtree order to `right -> root`. Since
    `left` is added early, the proper post traversal order, `left -> right -> root`, is maintained.

=== "python"
    ```python
    class Solution:
        def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:

            # (1)
            dummy = TreeNode(-1)
            dummy.left = root
            curr_node = dummy
            values = []

            while curr_node:
                if curr_node.left:  # (2)
                    # (3)
                    predecessor = curr_node.left
                    while predecessor.right and predecessor.right != curr_node:
                        predecessor = predecessor.right

                    if not predecessor.right:  # (4)
                        predecessor.right = curr_node  # (5)
                        curr_node = curr_node.left
                    else:  # (6)
                        predecessor.right = None  # (7)
                        values.extend(node.val for node in reverse_path(curr_node.left, predecessor))  # (8)
                        curr_node = curr_node.right
                else:
                    curr_node = curr_node.right

            return values

    def reverse_path(start_node: TreeNode, end_node: TreeNode) -> list[TreeNode]:
        """Reverse a path from start node to end node."""
        nodes = []
        while start_node != end_node:
            nodes.append(start_node)
            start_node = start_node.right
        nodes.append(end_node)
        nodes.reverse()
        return nodes
    ```

    1. Add a dummy node to ensure the root is properly processed.
    2. Explore the left tree first.
    3. Find predecessor of the current node, the rightmost node of the left subtree.
    4. Condition 1: `predecessor.right` is `None`. The left sub-tree is not explored.
    5. Establish a temporary link from predecessor to current.
    6. Condition 2: `predecessor.right` is the `curr_node`, coming back to the current node from the predecessor. This indicate the left sub-tree has been visited.
    7. Remove the temporary link.
    8. Reverse the node order from `root -> right` to `right -> root`. Then append to values where `left` is already in. So they are in right postorder.

#### Complexity Analysis of Approach 4

- Time complexity: $O(n)$  
    - We visit each node twice, one for establishing link and one for removing. So the
    time complexity of traversal is $O(n)$.
    - The reversing is done only on subtree, it is $O(h) << O(n)$.
    - So the total time complexity is $O(n)$.
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
