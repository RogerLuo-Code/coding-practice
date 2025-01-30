---
tags:
    - Breadth-First Search
    - Depth-First Search
    - Union Find
---

# LC1202. Smallest String With Swaps

## Problem Description

[LeetCode Problem 1202](https://leetcode.com/problems/smallest-string-with-swaps/description/):
You are given a string `s`, and an array of pairs of indices in the string `pairs` where
`pairs[i] = [a, b]` indicates 2 indices(0-indexed) of the string.

You can swap the characters at any pair of indices in the given `pairs` **any number of
times**.

Return the lexicographically smallest string that `s` can be changed to after using the
swaps.

## Clarification

- pairs: pair of indices in the string
- 0-indexed
- mixed case or just lower case?
- lexicographically smallest

## Assumption

-

## Solution

The problem can be viewed as a graph problem. Each index is a vertex and each given pair
is a undirected edge between the vertices. An edge implies that we can travel from one
vertex to another (i.e., swap them in the context of this problem).

???+ tip
    Since characters in the `pairs` can be swapped **any number of times**, letters in a
    connected component can be rearranged in any order. For example, for `(a, b)` and
    `(b, c)` pairs, we can swap `a` and `c` by swapping `a` with `b` and then with `c`.

### Approach 1 - BFS/DFS

Starting from the first letter, use breadth-first search (BFS) or depth-first search
(DFS) to find the connected components in the graph. Then sort the characters in each
connected component in ascending order and put in sorted indices. Continue the process
to re-order letters in the rest of indices.

=== "Python - DFS"
    ```python
    from collections import queue, defaultdict


    class Solution:
        def smallestStringWithSwaps(self, s: str, pairs: List[List[int]]) -> str:
            n = len(s)
            # Convert edges to adjacent list of vertices
            adj_list = defaultdict(list)
            for i, j in pairs:
                adj_list[i].append(j)
                adj_list[j].append(i)  # (1)

            visited = set()
            s_smallest_list = ['' for _ in range(n)]
            for i in range(n):  # (2)
                if i in visited:
                    continue

                indices = []
                self.dfs(i, adj_list, visited, indices)
                letters = [s[i] for i in indices]

                # (3)
                indices.sort()
                letters.sort()

                for i, ch in zip(indices, letters):
                    s_smallest_list[i] = ch

            return ''.join(s_smallest_list)

        def dfs(
            self,
            index: int,
            adj_list: dict[int, list],
            visited: set[int],
            indices: list[int],
        ) -> None:
            visited.add(index)
            indices.append(index)

            for neighbor in adj_list[index]:
                if neighbor not in visited:
                    self.dfs(neighbor, adj_list, visited, indices)
    ```

    1. Undirected edge so add both directions.
    2. Go through each index and find connected components.
    3. Letters in a connected component can be swapped with any others. sort them for
    the lexicographically order

=== "Python - BFS"
    ```python
    from collections import queue, defaultdict


    class Solution:
        def smallestStringWithSwaps(self, s: str, pairs: List[List[int]]) -> str:
            n = len(s)
            # Convert edges to adjacent list of vertices
            adj_list = defaultdict(list)
            for i, j in pairs:
                adj_list[i].append(j)
                adj_list[j].append(i)  # (1)

            visited = set()
            s_smallest_list = [""] * n
            for i in range(n):  # (2)
                if i in visited:
                    continue

                indices = []
                self.dfs(i, adj_list, visited, indices)
                letters = [s[idx] for idx in indices]

                # (3)
                letters.sort()
                indices.sort()

                for i, ch in zip(indices, letters):
                    s_smallest_list[i] = ch

            return ''.join(s_smallest_list)

        def bfs(
            self,
            index: int,
            adj_list: dict[int, list],
            visited: set[int],
            indices: list[int],
        ) -> None:
            visited.add(index)
            queue = deque([index])

            # Travel the adjacent indices
            while queue:
                curr_index = queue.popleft()
                indices.append(curr_index)
                for neighbor in adj_list[curr_index]:
                    if neighbor not in visited:
                        queue.append(neighbor)
                        visited.add(neighbor)
    ```

    1. Undirected edge so add both directions.
    2. Go through each index and find connected components.
    3. Letters in a connected component can be swapped with any others. sort them for
    the lexicographically order

#### Complexity Analysis of Approach 1

- Time complexity: $O(E + V \log V)$ where $V$ is the number of vertices (i.e., the
length of the string) and $E$ is the number of edges (the number of pairs).  
    - Building the adjacent list will take $O(E)$ operation. Each operation takes $O(1)$
    time to insert elements into the adjacent list;
    - During the DFS/BFS traversal, each vertex will only be visited once and iterate
    over the edge list of each vertex. Each edge is also iterated once. So it takes
    $O(V + E)$;
    - Converting `indices` to `letters` takes $O(V)$;
    - Sorting the list of `letters` and `indices` take $O(V \log V)$;
    - Update the smallest string list takes $O(V)$;
    - Convert list of letters to string takes $O(V)$;  
    So the total time complexity is $O(V) + O(E) + O(V + E) + O(V) + O(V \log V) + O(V) + O(V)$,
    which is $O(E) + O(V \log V) = O(E + V \log V)$.
- Space complexity: $O(E + V)$  
    - Building the adjacent list takes $O(E)$ space;
    - Tracking the visited vertices takes $O(V)$ in the worst case;
    - For traversal, the run time stack of DFS or the queue of BFS will use $O(V)$ space
    in the worst case;
    - Sorting in Python (timsort) takes $O(V)$ space in the worst case;
    - The smallest string list takes $O(V)$ space  
    So the total space is $O(E) + O(V) + O(V) + O(V) + O(V) = O(V + E)$.

### Approach 2 - Union Find

Similarly, we can use union-find to find all connected components by union `pairs`.
Then, put indices and letters of different parents (connected components) in separate
list. For each connected components, sort indices and letters and put them in the
smallest string.

=== "python"
    ```python
    class UnionFind:
        def __init__(self, n):
            self.parent = [i for i in range(n)]
            self.rank = [0] * n

        def find(self, x):
            if x != self.parent[x]:
                self.parent[x] = self.find(self.parent[x])
            return self.parent[x]

        def union(self, x, y):
            parent_x = self.find(x)
            parent_y = self.find(y)

            if parent_x != parent_y:
                if self.rank[x] > self.rank[y]:
                    self.parent[parent_y] = parent_x
                elif self.rank[x] < self.rank[y]:
                    self.parent[parent_x] = parent_y
                else:
                    self.parent[parent_y] = parent_x
                    self.rank[parent_x] += 1


    class Solution:
        def smallestStringWithSwaps(self, s: str, pairs: List[List[int]]) -> str:
            n = len(s)
            uf = UnionFind(n)

            # Use union-find to union pairs for connected component
            for a, b in pairs:
                uf.union(a, b)

            # Group indices by connected components
            groups = defaultdict(lambda: ([], []))
            for i, ch in enumerate(s):
                parent = uf.find(i)
                groups[parent][0].append(i)
                groups[parent][1].append(ch)

            # Sorting within each group and combine for smallest string
            res = [""] * n
            for ids, chars in groups.values():
                ids.sort()
                chars.sort()
                for ch, i in zip(chars, ids):
                    res[i] = ch

            return "".join(res)
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O((E + V) \alpha(V) + V \log V)$  
    - `union-find` takes $O(V)$ time to initialize;
    - When union pairs, it goes through $E$ pairs and each operation takes
    $O(\alpha(V))$ time. The time complexity is $O(E \alpha(V))$;
    - For grouping by connected components, it takes $O(V)$ operations and each
    operation takes $O(\alpha(V))$ to `find` and $O(1)$ to insert;
    - Sorting takes $O(V \log V)$ in the worst case;
    - Insert into result and combine into string takes $O(V)$  
    So the total time complexity is $O(V) + O(E \alpha(V)) + O(V \alpha(V)) + O(V \log V) + O(V)$,
    which is $O((E + V) \alpha(V) + V \log V)$.
- Space complexity: $O(V)$  
    - `union-find` takes $O(V)$ space to store parent and rank;
    - `groups` takes $O(V)$ store indices and letters;
    - sorting in Python (timsoret) takes $O(V)$ space in the worst case;
    - find result takes $O(V)$ space  
    So the total time complexity is $O(V) + O(V) + O(V) = O(V)$

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach -  |  $O(E + V \log V)$           | $O(V + E)$ |
Approach 2 - Union Find  |  $O((E + V) \alpha(V) + V \log V)$           | $O(V)$  |

## Test

- **No Pairs**: If `pairs` is empty, return the string as is.
- **Isolated Characters**: Characters not in any pairs remain unchanged.
- **Multiple Components**: Ensure each connected component is handled independently.