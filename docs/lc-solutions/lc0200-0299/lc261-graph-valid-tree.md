---
tags:
    - Breadth-First Search
    - Depth-First Search
    - Union Find
    - Graph
---

# LC261. Graph Valid Tree

## Problem Description

[LeetCode Problem 261](https://leetcode.com/problems/graph-valid-tree/): You have a
graph of `n` nodes labeled from `0` to `n - 1`. You are given an integer n and a list of
`edges` where `edges[i] = [ai, bi]`indicates that there is an undirected edge between
nodes `ai` and `bi` in the graph.

Return `true` _if the edges of the given graph make up a valid tree, and_ `false` 
_otherwise_.

## Clarification

- Undirected graph
- Definition of valid tree

## Assumption

-

## Solution

There are different solutions based on the definition of a valid tree. In general, there
are two kinds of definitions:

- Basic
    - The graph is fully connected.
    - The graph contains no cycle.
- Advanced
    - The graph is fully connected.
    - The graph has exactly $n - 1$ edges. Any less, it can't possibly be fully
    connected. Any more, it contains cycles.


### Approach 1 - Basic Graph Theory + DFS/BFS

Start from the basic definition,

- Check whether the graph is fully connected, `len(visited) == n`
- Detect a cycle
    - Since it is an **undirected** graph, we need to exclude a trivia cycle,
    `A - B - A`. Check whether `next_node == parent of current node`
    - Detect a real cycle, `next node is in visited`

We can use depth-first search (DFS) or breadth-first search (BFS) to traverse the graph
and mark visited node. If detect a cycle or not able to visited all nodes, return False.

=== "Python - DFS"
    ```python
    class Solution:
        def validTree(self, n: int, edges: List[List[int]]) -> bool:

            adjacent_list = [[] for _ in range(n)]
            for edge in edges:
                adjacent_list[edge[0]].append(edge[1])
                adjacent_list[edge[1]].append(edge[0])
            parent = {0: -1}  # (1)

            return self.dfs(0, adjacent_list, parent) and len(parent) == n

        def dfs(self, current_node: int, adjacent_list: List[List[int]], 
                parent: Dict[int, int]) -> bool:
            for next_node in adjacent_list[current_node]:
                if next_node == parent[current_node]:  # (2)
                    continue
                if next_node in parent:  # (3)
                    return False
                # The node is not visited or parent node
                parent[next_node] = current_node
                if not self.dfs(next_node, adjacent_list, parent):  #(4)
                    return False

            return True
    ```

    1. key: current node, value: parent node.
    2. Exclude trivia cycle `A -> B -> A`. The key, current_node, is already in the
    parent before calling dfs function. Otherwise, need to use `parent.get(current_node, -1)`.
    3. If the node is visited, there is a cycle.
    4. Early termination.

=== "Python - DFS - Visited"
    ```python
    class Solution:
    def validTree(self, n: int, edges: List[List[int]]) -> bool:

        adjacent_list = [[] for _ in range(n)]
        for edge in edges:
            adjacent_list[edge[0]].append(edge[1])
            adjacent_list[edge[1]].append(edge[0])
        visited = set([0])
        return self.dfs(0, -1, adjacent_list, visited) and len(visited) == n

    def dfs(self, current_node: int, parent_node: int, adjacent_list: List[List[int]], 
            visited: Set[int]) -> bool:  # (1)
        for next_node in adjacent_list[current_node]:
            if next_node == parent_node:
                continue
            if next_node in visited:
                return False
            # The node is not visited or parent node
            visited.add(next_node)
            if not self.dfs(next_node, current_node, adjacent_list, visited):
                return False

        return True
    ```

    1. Use two parameters, `visited` and `parent_node`, instead of one `parent`
    dictionary

=== "Python - BFS"
    ```python
    from collections import deque

    class Solution:
        def validTree(self, n: int, edges: List[List[int]]) -> bool:

            adjacent_list = [[] for _ in range(n)]
            for edge in edges:
                adjacent_list[edge[0]].append(edge[1])
                adjacent_list[edge[1]].append(edge[0])
            parent = {}
            return self.bfs(0, adjacent_list, parent) and len(parent) == n

        def bfs(self, node: int, adjacent_list: List[List[int]], 
                parent: Dict[int, int]) -> bool:
            queue = deque([node])
            parent[node] = -1  # (1)
            while queue:
                current_node = queue.popleft()
                for next_node in adjacent_list[current_node]:
                    if next_node == parent[current_node]:  # (2)
                        continue
                    if next_node in parent:  # (3)
                        return False
                    # The node is not visited or parent node
                    parent[next_node] = current_node
                    queue.append(next_node)

            return True
    ```

    1. Set parent of root node to `-1`, indicating no parent node.
    2. Exclude trivia cycle `A -> B -> A`. The key, current_node, is already in the 
    parent before calling dfs function. Otherwise, need to use `parent.get(current_node, -1)`.
    3. If the node is visited, there is a cycle.

=== "Python - BFS - Visited"
    ```python
    from collections import deque

    class Solution:
        def validTree(self, n: int, edges: List[List[int]]) -> bool:

            adjacent_list = [[] for _ in range(n)]
            for edge in edges:
                adjacent_list[edge[0]].append(edge[1])
                adjacent_list[edge[1]].append(edge[0])
            visited = set()
            return self.bfs(0, adjacent_list, visited) and len(visited) == n

        def bfs(self, node: int, adjacent_list: List[List[int]], visited: Set[int]) -> bool:
            queue = deque([(node, -1)])  # (1)
            visited.add(node)
            while queue:
                current_node, parent_node = queue.popleft()
                for next_node in adjacent_list[current_node]:
                    if next_node == parent_node:
                        continue
                    if next_node in visited:
                        return False
                    # The node is not visited or parent node
                    visited.add(next_node)
                    queue.append((next_node, current_node))

            return True
    ```

    1. Store `(current_node, parent_node)` pair in the queue and therefore can use 
    `visited` set instead of `parent` dictionary.

#### Complexity Analysis of Approach 1

- Time complexity: $O(V + E)$ where $V$ is number of vertices and $E$ is number of edges  
  The total time complexity consists of
    - Initialize the adjacent list, taking $O(V)$
    - Convert from edges to adjacent list, taking $O(E)$
    - For traversing, the outer loop will run $V$ times to go through each node exact
    once even the node has no neighbors. The inner loop, it iterates over the adjacent
    edges once. In total, all $E$ edges are iterated over once by the inner loop.
    Therefore, this gives $O(V + E)$ for traversing.    
  so the total time complexity is $O(V) + O(E) + O(V + E) = O(V + E)$.
- Space complexity: $O(V + E)$  
    - The adjacent list is a list of length $V$ (stores all nodes) with inner lists with
    lengths that are added to a total of $E$ (edges), which takes $O(V + E)$.
    - `visited` or `parent` stores all nodes in the worst takes, taking $O(V)$
    - The recursive `dfs` calls takes at most $V$ times or the `queue` stores all $V$
    nodes in the worst case, which takes $O(V)$.  
  So the total space complexity is $O(V + E) + O(V) + O(V) = O(V + E)$.

### Approach 2 - Advanced Graph Theory + DFS/BFS

Start from advanced definition of tree:

- The graph is fully connected -> check whether traverse all nodes from one node
- The graph has exactly $n - 1$ edges -> Check whether there are $n - 1$ edges

We can use either DFS or BFS to traverse the graph to check the connectivity.

=== "Python - DFS"
    ```python
    class Solution:
    def validTree(self, n: int, edges: List[List[int]]) -> bool:
        if len(edges) != n - 1:  # (1)
            return False

        adjacent_list = [[] for _ in range(n)]
        for edge in edges:
            adjacent_list[edge[0]].append(edge[1])
            adjacent_list[edge[1]].append(edge[0])
        visited = set()
        self.dfs(0, adjacent_list, visited)
        return len(visited) == n

    def dfs(self, node: int, adjacent_list: List[List[int]], visited: Set[int]) -> None:
        visited.add(node)
        for next_node in adjacent_list[node]:
            if next_node in visited:  # (2)
                continue
            self.dfs(next_node, adjacent_list, visited)
    ```

    1. Check the condition 2 of advanced conditions
    2. prevent from stucking in an infinite loop if there are indeed cycles (or prevent
    from looping on the trivial cycles)

=== "Python - BFS"
    ```python
    from collections import deque

    class Solution:
        def validTree(self, n: int, edges: List[List[int]]) -> bool:
            if len(edges) != n - 1:  # (1)
                return False

            adjacent_list = [[] for _ in range(n)]
            for edge in edges:
                adjacent_list[edge[0]].append(edge[1])
                adjacent_list[edge[1]].append(edge[0])
            visited = set()
            self.bfs(0, adjacent_list, visited)
            return len(visited) == n

        def bfs(self, node: int, adjacent_list: List[List[int]], visited: Set[int]) -> None:
            queue = deque([node])
            visited.add(node)
            while queue:
                current_node = queue.popleft()
                for next_node in adjacent_list[current_node]:
                    if next_node in visited:  # (2)
                        continue
                    visited.add(next_node)
                    queue.append(next_node)
    ```

    1. Check the condition 2 of advanced conditions
    2. prevent from stucking in an infinite loop if there are indeed cycles (or prevent
    from looping on the trivial cycles)

#### Complexity Analysis of Approach 2

- Time complexity: $O(V)$ where $V$ is the number of nodes  
  Note that $O(E) = O(V)$ this time since `number of edges == number of nodes - 1`.
  The total time complexity consists of
    - Initialize the adjacent list, taking $O(V)$
    - Convert from edges to adjacent list, taking $O(E) = O(V)$.
    - For traversing, the outer loop will run $V$ times to go through each node exact
    once even the node has no neighbors. The inner loop, it iterates over the adjacent 
    edges once. In total, all $E$ edges are iterated over once by the inner loop. 
    Therefore, this gives $O(V + E) = O(V)$ for traversing.   
  so the total time complexity is $O(V) + O(V) + O(V + V) = O(V)$.
- Space complexity: $O(V)$  
    - The adjacent list is a list of length $V$ (stores all nodes) with inner lists with
    lengths that are added to a total of $E$ (edges), which takes $O(V + E) = O(V)$.
    - `visited` or `parent` stores all nodes in the worst takes, taking $O(V)$
    - The `queue` will store all nodes (total number of $V$) or `dfs` recursive function
    calls $V$ times in the worse case, taking $O(V)$ space.  
  So the total space complexity is $O(V) + O(V) + O(V) = O(V)$.

### Approach 3 - Advanced Graph Theory + Union Find

Based on the advanced definition, we can also use union find to check whether a single
connected component is formed (indicating connectivity).

=== "python"
    ```python
    class UnionFind:
    def __init__(self, size):
        self.root = [i for i in range(size)]
        self.rank = [0 for _ in range(size)]
        self.count = size

    def find(self, x):
        if x == self.root[x]:
            return x

        self.root[x] = self.find(self.root[x])
        return self.root[x]

    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)

        if root_x != root_y:
            if self.rank[root_x] > self.rank[root_y]:
                self.root[root_y] = root_x
            elif self.rank[root_x] < self.rank[root_y]:
                self.root[root_x] = root_y
            else:
                self.root[root_y] = root_x
                self.rank[root_x] += 1
            self.count -= 1


    class Solution:
        def validTree(self, n: int, edges: List[List[int]]) -> bool:
            if len(edges) != n - 1:
                return False

            uf = UnionFind(n)
            for edge in edges:
                uf.union(edge[0], edge[1])

            return uf.count == 1
    ```

#### Complexity Analysis of Approach 3

- Time complexity: $O(V \alpha(V))$  
  In the worst case, the number of edges equals the number of vertices. Then, go through
  each of the $E$ edges ($E = V$) and add them to the `UnionFind` data structure by
  using the `union` function. The union function takes amortized $O(\alpha(n))$,
  where $\alpha$ is the [Inverse Ackermann Function](https://en.wikipedia.org/wiki/Ackermann_function#Inverse).
  So the total time complexity is $O(E \alpha(E)) = O(V \alpha(V))$.
- Space complexity: $O(V)$  
  The `UnionFind` data structure requires $O(V)$ space to store the `root` and `rank`.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach - Basic + DFS/BFS |  $O(V + E)$           | $O(V + E)$ |
Approach - Advance + DFS/BFS |  $O(V)$           | $O(V)$ |
Approach - Advance + Union Find |  $O(V \alpha(V))$           | $O(V)$ |

## Test
