# Tree

A tree is a **abstract data type** that represents a hierarchical tree
structure with a set of connected nodes. Each node has a parent (except the root) and
zero or more children.

The tree defines how trees are structured and manipulated but does not dictate a specific
implementation. For example, the tree can be represented in a number of ways, including
a list of parents with
pointers to children, a list of children with pointers to parents, or a list of nodes
and a separate list of parent-child relations.

## Operations and Properties

**Operations**:

- **Insert** nodes
- **Delete** nodes
- **Traversal** (preorder, inorder, postorder, level-order)
- **Search** for a node

**Properties**:

- There are no cycles (no node can be its own ancestor).
- Each child can be treated like the root node of its own subtree.

## Common Tree-Based Data Structure

- [Binary Tree](../data-structure/binary-tree/binary-tree.md) (each node has at most two
children)
- Binary Search Tree (BST) (Ordered binary tree for efficient searching)
- [Heap Tree](../data-structure/heap/index.md) (used for priority queues)
- Trie (Prefix Tree) (used for string storage)

## Different from Tree in Graph Theory

A tree ADT is a structured way to store and manipulate hierarchical data, while a
[tree in graph theory](../algorithms/graph/tree.md) is mathematical concept of a
connected, acyclic graph.

| Feature    | Tree ADT                                      | Tree in Graph Theory               |
|------------|-----------------------------------------------|------------------------------------|
| Definition | Hierarchical data structure                   | Special type of graph              |
| Root       | Always has a root                             | May or may not have a root         |
| Direction  | Typically directed (from parents to children) | Undirected (unless specified)      |
| Cycles     | No cycles                                     | No cycles                          |
| Use Cases  | Data storage, searching                       | Network structures, spanning trees |
