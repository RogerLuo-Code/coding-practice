# Binary Tree

## Introduction

A binary tree is one of the most typical tree data structure. It constrains the number
of children for each parent to at most two.

## Different Traversal Methods

- Pre-order traversal: visit the root first, then the left subtree, and finally the
right subtree.
- In-order traversal: traverse the left subtree first, then visit the root, and finally
traverse the right subtree.
- Post-order traversal: traverse the left subtree first, then traverse the right subtree,
and finally visit the root.
    - When deleting nodes in a tree, it will be in post-order. Delete a node's left and
    right children before delete the node itself.
    - Post-order is widely used in mathematical expressions.
