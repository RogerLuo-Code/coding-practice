---
tags:
    - Topological Sort
---

# LC310. Minimum Height Trees

## Problem Description

[LeetCode Problem 310](https://leetcode.com/problems/minimum-height-trees/description/):
A tree is an undirected graph in which any two vertices are connected by _exactly_ one
path. In other words, any connected graph without simple cycles is a tree.

Given a tree of `n` nodes labelled from `0` to `n - 1`, and an array of `n - 1` `edges`
where `edges[i] = [ai, bi]` indicates that there is an undirected edge between the two
nodes `ai` and `bi` in the tree, you can choose any node of the tree as the root. When
you select a node `x` as the root, the result tree has height `h`. Among all possible
rooted trees, those with minimum height (i.e. `min(h)`)  are called
**minimum height trees** (MHTs).

Return _a list of all **MHTs'** root labels_. You can return the answer in **any order**.

The **height** of a rooted tree is the number of edges on the longest downward path
between the root and a leaf.

## Clarification

- A tree is an undirected graph with n nodes and n−1 edges.
- The height of a tree is the number of edges in the longest path from the root to a leaf.

## Assumption

-

## Solution

A straight-forward (brutal force) way to solve the problem is to

- Start from each node and find the maximum distance between the root and the leaf node
using either BFS or DFS.
- Filter out the roots that have the minimum height.

Yet, the time complexity of this brutal force method is $O(n^2)$ where $n$ is the number
of nodes in the tree. It will results in Time Limit Exceeded exception.

### Approach - Topological Sort

The problem can be efficiently solved using a topological sort-like approach bases on
the observation: the roots of minimum height trees are at the **centers** of the tree.
The center divide the treen into substree of approximately equal height, which helps
minimize the height of the tree.

By iteratively removing leaves, the tree "shrinks" inward toward its centers. The
process stops when 1 or 2 nodes remain, which are the centers of the tree.

=== "Python"
    ```python
    from collections import defaultdict, deque

    class Solution:
        def findMinHeightTrees(self, n: int, edges: List[List[int]]) -> List[int]:
            # Edge cases
            if n <= 2:
                return [i for i in range(n)]

            # Build adjacent list and n_connections
            adj_list = defaultdict(set)
            n_connections = [0] * n
            for node_a, node_b in edges:
                if node_b not in adj_list[node_a]:
                    adj_list[node_a].add(node_b)
                    adj_list[node_b].add(node_a)
                    n_connections[node_a] += 1
                    n_connections[node_b] += 1

            # Find all leaf nodes
            # Since it is a tree, every node has at least 1 connection.
            nodes_with_1_connection = [i for i in range(n) if n_connections[i] == 1]
            queue_with_1_connection = deque(nodes_with_1_connection)

            # Trim leaf nodes iteratively
            n_processed_nodes = n
            while queue_with_1_connection:
                if n_processed_nodes <= 2:
                    return list(queue_with_1_connection)

                size = len(queue_with_1_connection)
                n_processed_nodes -= size

                for i in range(size):
                    curr_node = queue_with_1_connection.popleft()
                    for next_node in adj_list[curr_node]:
                        n_connections[next_node] -= 1
                        if n_connections[next_node] == 1:
                            queue_with_1_connection.append(next_node)

            return []  # not a tree
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
    - Building adjacent list takes $O(E)$ since iterating through all $E$ edges.
    - Finding leaf nodes takes $O(V)$ since going through all $V$ nodes and checking
    their degrees.
    - For queue operations, it will go through $V - 2$ nodes, taking $O(V)$ time.
    - For neighboring explorations, it will go through at most $E$ edges in the worst
    case, taking $O(E)$ time.
    - For a tree, $V = n$ and $E = n - 1$.
    - So the total time complexity is $O(E) + O(V) + O(V) + O(E) = O(n)$.
- Space complexity: $O(n)$  
    - Adjacent list takes $O(V + E)$ since store all nodes and their associate edges.
    - n_connection array takes $O(V)$ space since store degrees for all nodes.
    - The queue may store $V - 2$ nodes in the worst case, which takes $O(V)$ space.
    - So the total space complexity is $O(V + E) + O(V) + O(V) = O(n)$.

## Test

- Single node (`n=1`,`edges=[]`): Output is `[0]`.
- Linear tree (`n=4`,`edges=[[0,1],[1,2],[2,3]]`): Output is `[1,2]`.
- Completely balanced tree (`n=7`,`edges=[[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]`):
Output is `[0]`.
