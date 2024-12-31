# Prim's Algorithm

Prim's algorithm is a greedy algorithm that finds a minimum spanning tree for a **weighted undirected** graph. The algorithm operates by building the tree one vertex at a time, from an arbitrary starting vertex, at each step adding the cheapest possible connection from the tree to another vertex by using [cut property](./index.md#cut-property)

## Introduction

## Algorithm

1. Initialize a tree with a single vertex, chosen arbitrarily from the graph.
2. Grow the tree by one edge: find the vertex with the minimum edge between vertices in the tree and ones not in the tree, and transfer it to the tree
3. Repeat step 2 (until all vertices are in the tree)

### Procedures

### Complexity Analysis

