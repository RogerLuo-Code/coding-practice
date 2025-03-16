---
tags:
    - Binary Tree
---

# LC297. Serialize and Deserialize Binary Tree

## Problem Description

[LeetCode Problem 297](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/description/):
Serialization is the process of converting a data structure or object into a sequence of
bits so that it can be stored in a file or memory buffer, or transmitted across a
network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction
on how your serialization/deserialization algorithm should work. You just need to ensure
that a binary tree can be serialized to a string and this string can be deserialized to
the original tree structure.

Clarification: The input/output format is the same as how LeetCode serializes a binary
tree. You do not necessarily need to follow this format, so please be creative and come
up with different approaches yourself.

## Clarification

-

## Assumption

-

## Solution

### Approach 1: Preorder/Postorder Traversal

We can use either preorder or postorder method to traverse the tree and encode its
values as well as its **structure** (adding `None` nodes) into a string.

This is different from
[LC105 construct binary tree from preorder and inorder traversal](../lc0100-0199/lc0105-construct-binary-tree-from-preorder-and-inorder-traversal.md)
and [LC106 construct binary tree from inorder and postorder traversal](../lc0100-0199/lc0106-construct-binary-tree-from-inorder-and-postorder-traversal.md)
where lists don't preserve the `None` node information, so we don't have an indicator
to check if a node is in the left subtree or right subtree and 2 traversals are needed.

=== "Python"
    ```python
    class Codec:

        spliter = ","
        none_str = "x"

        def serialize(self, root):
            """Encodes a tree to a single string.

            :type root: TreeNode
            :rtype: str
            """
            str_list = []
            self.build_string(root, str_list)

            return Codec.spliter.join(str_list)

        def deserialize(self, data):
            """Decodes your encoded data to tree.

            :type data: str
            :rtype: TreeNode
            """
            val_str_list = data.split(Codec.spliter)
            queue = deque(val_str_list)
            return self.build_tree(queue)

        def build_tree(self, data_str_queue):
            curr_val_str = data_str_queue.popleft()  # (1)
            if curr_val_str == Codec.none_str:
                return None

            node = TreeNode(int(curr_val_str))
            node.left = self.build_tree(data_str_queue)
            node.right = self.build_tree(data_str_queue)  # (2)

            return node

        def build_string(self, node, str_list):
            if not node:
                str_list.append(Codec.none_str)
            else:
                str_list.append(str(node.val))  # (3)
                self.build_string(node.left, str_list)
                self.build_string(node.right, str_list)
    ```

    1. For postorder, change `popleft()` to `pop()`, since the root of postorder is the
    last node.
    2. For post order, move building right tree above building left tree. The postorder
    list is `left -> right -> root`. Since we go through the list in a reversed
    direction, it should be `left <- right <- root`.
    3. For postorder, move adding the root value to the bottom after building the right
    subtree to match the postorder `left -> right -> root`.

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$ for serialization and deserialization  
    - Serialization takes $O(n)$
        - `build_string` traverse all nodes exactly once, which takes $O(n)$ time.
        - Convert string list to string takes $O(n)$ time.
    - Deserialization takes $O(n)$
        - string split takes $O(n)$ time.
        - Add string list to queue takes $O(n)$ time.
        - `build_tree` goes through all strings, which takes $O(n)$.
- Space complexity: $O(n)$  
    - Serialization takes $O(n)$ space
        - `str_list` stores all $n$ nodes' values and additional $n - 1$ null values,
        taking $O(n)$ space. Each missing child gets an explicit null value. For a full
        binary tree with $n$ nodes, the total number of positions is $2 n - 1$. So the
        number of nulls is $2 n - 1 - n = n - 1$.
    - Deserialization takes $O(n)$
        - Convert string to list takes $O(n)$ space.
        - Add strings to queue takes $O(n)$ space.

???+ "Why does a full binary tree with $n$ nodes have $2 n - 1$ positions?"
    - Each node occupies one position.
    - Each node creates 2 child positions (except the root node).
    - So the total number of positions is $2 n - 1$. `-1` is for the root.

### Approach 2: Level Order

We can also use level order traversal for serialization/deserialization. Similarly, we
will preserve `None` nodes to encode structure information.

=== "python"
    ```python
    class Codec:

        def serialize(self, root):
            """Encodes a tree to a single string.

            :type root: TreeNode
            :rtype: str
            """
            if not root:
                return ""

            values = []
            values.append(str(root.val))
            queue = deque([root])
            while queue:
                curr_node = queue.popleft()

                if curr_node.left:
                    queue.append(curr_node.left)
                    values.append(str(curr_node.left.val))
                else:
                    values.append("null")

                if curr_node.right:
                    queue.append(curr_node.right)
                    values.append(str(curr_node.right.val))
                else:
                    values.append("null")

            return ",".join(values)

        def deserialize(self, data):
            """Decodes your encoded data to tree.

            :type data: str
            :rtype: TreeNode
            """

            # Empty string
            if not data:
                return None

            value_str_list = data.split(",")
            root = TreeNode(value_str_list[0])
            idx = 1  # index of value string list, starting from the 2nd element since the first one is created for root
            prev_level = deque([root])
            while prev_level:
                prev_node = prev_level.popleft()
                left_value_str = value_str_list[idx]
                if left_value_str != "null":
                    left_node = TreeNode(int(left_value_str))
                    prev_node.left = left_node
                    prev_level.append(left_node)

                idx += 1
                right_value_str = value_str_list[idx]
                if right_value_str != "null":
                    right_node = TreeNode(int(right_value_str))
                    prev_node.right = right_node
                    prev_level.append(right_node)

                idx += 1

            return root
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
    - Serialization: $O(n)$
        - Using queue to go through all $n$ nodes exactly once, which takes $O(n)$.
        - string join takes $O(n)$.
    - Deserialization: $O(n)$
        - string split takes $O(n)$ time.
        - Go through all $n$ nodes to build tree which takes $O(n)$ time.
- Space complexity: $O(n)$  
    - Serialization: $O(n)$
        - value list stores values of $n$ nodes and $n - 1$ `None` nodes, takes $O(n)$ space.
        - the queue size reaches the peak when storing the last level of nodes. For a
        full binary tree, the last level has $n / 2$ nodes.
    - Deserialization: $O(n)$
        - Storing slitted strings takes $O(n)$ space.
        - The `prev_queue` stores at most $n / 2$ nodes, taking $O(n)$ space.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Preorder/Postorder | $O(n)$          | $O(n)$
Approach - Level Order | $O(n)$          | $O(n)$

## Test

- Tree is empty (None).
- Tree contains only one node.
- Tree is highly unbalanced (linked list-like structure).
