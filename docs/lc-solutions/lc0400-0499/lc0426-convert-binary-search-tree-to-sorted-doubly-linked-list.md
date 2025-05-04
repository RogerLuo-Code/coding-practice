---
tags:
    - Binary Search Tree
    - Doubly-Linked List
---

# 426. Convert Binary Search Tree to Sorted Doubly Linked List

## Problem Description

[LeetCode Problem 426](https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/description/):
Convert a **Binary Search Tree** to a sorted **Circular Doubly-Linked List** in place.

You can think of the left and right pointers as synonymous to the predecessor and
successor pointers in a doubly-linked list. For a circular doubly linked list,
the predecessor of the first element is the last element, and the successor of the last
element is the first element.

We want to do the transformation **in place**. After the transformation, the left
pointer of the tree node should point to its predecessor, and the right pointer should
point to its successor. You should return the pointer to the smallest element of the
linked list.

## Clarification

-

## Assumption

-

## Solution

### Approach 1: Standard In-order Traversal

This problem can be solved using the standard in-order traversal. The in-order
traversal of a binary search tree (BST) visits the nodes in sorted order. We can use
this property to build a doubly linked list.

Following the in-order traversal (`left -> node -> right`), we can explore the
left -> build links between prev and curr -> explore the right.

To facilitate the link building:

- Use a `dummy` node to keep track of the head of the doubly linked list.
- Use a `prev` pointer to keep track of the previous node in the traversal. This will
be used to connect the current node with the previous node.

After the in-order traversal, connect the head (`dummy.right`) and tail (`prev`) of
the doubly linked list to make it circular.

=== "Python"
    ```python
    class Solution:
        def treeToDoublyList(self, root: 'Optional[Node]') -> 'Optional[Node]':
            if root is None:
                return None

            dummy = Node(-1)
            self.prev = dummy
            self._inorder_conversion(root)

            # Connect head (dummy.right) and tail (self.prev)
            self.prev.right = dummy.right
            dummy.right.left = self.prev

            return dummy.right

        def _inorder_conversion(self, curr: 'Optional[Node]') -> None:
            if curr is None:
                return

            # Explore left subtree
            self._inorder_conversion(curr.left)

            # Build connections between prev and curr
            self.prev.right = curr
            curr.left = self.prev
            self.prev = curr

            # Explore right subtree
            self._inorder_conversion(curr.right)
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  The algorithm visits each node exactly once for total $n$ nodes.
- Space complexity: $O(n)$  
  The space complexity is due to the recursion stack, which can go as deep as the
  height of the tree. In the worst case (for example, every node only has left child),
  the recursion stack takes $O(n)$ space. In the best case (a balanced binary tree),
  the recursion stack takes $O(\log n)$ space.

### Approach 2: Morris In-order Traversal

This problem can be solved using Morris in-order traversal. The Morris traversal adds a
link from the rightmost node of the left subtree to the current node. By leveraging this:

- Keep this link (not remove it like the original Morris traversal)
- Add a link from the current node to the rightmost node of the left subtree. So we can
build the doubly linked list in place.
- Store `prev` node whenever we move to the right subtree. This will be used to connect
the leftmost node of the right subtree to the current node.

=== "python"
    ```python
    class Solution:
        def treeToDoublyList(self, root: 'Optional[Node]') -> 'Optional[Node]':
            if root is None:
                return root

            # Find head
            node = root
            while node.left is not None:
                node = node.left
            head = node

            # Find tail
            node = root
            while node.right is not None:
                node = node.right
            tail = node

            # Use morris in-order traversal to build links
            prev = None
            curr = root
            while curr is not None:
                if curr.left is None:
                    # Finish exploring the left tree, explore the right
                    if prev is not None:
                        curr.left, prev.right = prev, curr
                    prev = curr  # Update prev when moving to right
                    curr = curr.right
                else:
                    predecessor = curr.left

                    # Find the right most node of the left subtree
                    while predecessor.right is not None and predecessor.right is not curr:
                        predecessor = predecessor.right

                    # Two conditions after while loop
                    # 1) predecessor.right is None
                    # 2) left subtree is explored

                    if predecessor.right is None:
                        predecessor.right = curr
                        curr = curr.left
                    else:
                        prev = curr  # store this node and will be connected with left most node of right subtree
                        curr.left = predecessor  # Keep predecessor.right link and add link back from the current
                        curr = curr.right

            # Build connection between head and tail
            head.left, tail.right = tail, head

            return head
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  We visit each node twice, once for establishing the link and once for exploring it.
  Therefore, the time complexity is $O(n)$.
- Space complexity: $O(1)$  
  We use constant space for the pointers `prev`, `curr`, and `predecessor` to build the
  list in place.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach 1 - Standard In-order Traversal | $O(n)$          | $O(n)$
Approach 2 - Morris In-Order Traversal | $O(n)$          | $O(1)$

## Test

- Test empty tree
- Test single node tree
- Test two nodes tree
- Test normal tree with more than two nodes and both left and right subtrees
- Test normal tree with more than two nodes and only left subtree
- Test normal tree with more than two nodes and only right subtree
