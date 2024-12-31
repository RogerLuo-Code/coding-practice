# Kruskal's Algorithm

## Introduction

Kruskal's algorithm finds a minimum spanning forest of a weighted undirected graph. If the graph is connected, it finds a [minimum spanning tree](index.md). It is a greedy algorithm that in each step adds to the forest the lowest-weight edge that will not form a cycle.

## Algorithm

### Procedures

The key steps of the algorithm are sorting and the use of a [union-find data structure](../../../data-structure/union-find/union-find.md) to detect cycles.

1. **Ascending sort** all edges by their weight.
2. Add edges in the sorted into the Minimum Spanning Tree. Skip the edges that would produce cycles in the Minimum Spanning Tree.
3. Repeat step 2 until $N - 1$ edges are added.

??? node "Why only choose N - 1 edges"
    The minimum number of edges to connect all vertices in the graph is $N - 1$. Adding one will cause a cycle and reducing one will miss connection to a vertex.

### Complexity Analysis

- Time complexity: $O(E \log E)$ where $E$ represents the number of edges.
    - At first, sorting all the edges take $O(E \log E)$ time.
    - For building the minimum spanning tree, check each edge whether both vertices belong to the same connected component, which takes $O(\alpha(V))$ operation, where $\alpha$ refers to the Inverse Ackermann function. In the worst case, the tree will not be completed until reaching the last edge, so this will take $O(E \alpha(V))$ time.
    - In total, the time complexity is $O(E \log E + E \alpha(V)) = O(E \log E)$.

- Space complexity: $O(V)$ or $O(V + E)$, where $V$ represents the number of vertices.
    - Depending on sorting algorithm, sorting algorithms may use $O(\log E)$ or $O(E)$ space.
    - Keeping track of the root of every vertex in the union-find data structure requires $O(V)$ space.
    - In total, the space complexity is $O(V + \log E)$ or $O(V + E)$.