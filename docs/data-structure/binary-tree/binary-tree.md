# Binary Tree

## Introduction

A binary tree is one of the most typical tree data structure. There are at most two
children per node.

## Variations

- **Balanced binary tree**: a binary tree in which the depth of the left and right
subtrees of every node differ by 1 or less.
    - **Property**: If a tree has $n$ number of nodes, and it is **balanced**, then the
    height or level of the tree $=O(\log_2(n))$
- **Complete binary tree**: a binary tree in which every level, except possibly the
last, is completely filled, and all nodes are as far left as possible.
    - **Property**: If a tree is complete tree, then it must be a balanced tree.
- **Binary search tree (BST)**: For every single node in the tree, the values in its
left subtree are all smaller than its value, and the values in its right subtree are all
larger than its value. ^bst-definition
    - **Property**: If printing the value of the nodes in BST in in-order sequence, then
    it forms an ascending order.
    - **Question**: what if there are duplicate values? Augment every tree node to store
    count together with regular fields like key, left, and right pointers (change the
    class definition).

## Different Traversal Methods

**Tree traversal** refers to the process of visiting each node in a tree data structure,
exactly once. Since a tree may be traversed in multiple ways, the traversal is
classified by the order in which the nodes are visited. The tree traversal algorithms
can be classified into two categories:

- **Depth-First Search (DFS) Algorithm**: it starts with the root node and first visits
all nodes of one branch as deep as possible of the chosen node before going to the next
sibling. There are three popular approaches: in-order, pre-order, and post-order.
    - Pre-order traversal: visit the root first, then the left subtree, and finally the
    right subtree.
    - In-order traversal: traverse the left subtree first, then visit the root, and finally
    traverse the right subtree.
    - Post-order traversal: traverse the left subtree first, then traverse the right subtree,
    and finally visit the root.
        - When deleting nodes in a tree, it will be in post-order. Delete a node's left and
        right children before delete the node itself.
        - Post-order is widely used in mathematical expressions.
- **Breadth-First Search (BFS) Algorithm**: it starts from the root node and visits all
nodes of current depth before moving to the next depth in the tree.

Traversing a tree needs to store nodes in some way for later visiting. This is often
done via a stack (LIFO) or a queue (FIFO) or call stack (implicit during recursion).
Depth-first search is easily implemented via a stack or the call stack during recursion
while breadth-first search is easily implemented via a queue.

## References

- [Tree traversal - wiki](https://en.wikipedia.org/wiki/Tree_traversal)