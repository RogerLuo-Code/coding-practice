# Depth-First Search

## Introduction

Goal: Systematically search through a graph

## Implementation

There are two ways to implement DFS:

- recursive DFS using recursion
  Use the implicit stack provided by the system, also know as the [Call Stack](https://en.wikipedia.org/wiki/Call_stack).

```python
visited = set()
def dfs(node, visited):
    visited.add(node)
        for neighbor in adjacent_list[node]:
            if neighbor not in visited:
                dfs(neighbor, visited)
```

- iterative DFS using stack

```python
def dfs(node):
    stack = [node]
    visited = set([node])
    while stack:
        curr = stack.pop()
        for neighbor in adjacent_list[curr]:
            if neighbor not in visited:
                visited.add(neighbor)
                stack.append(neighbor)
```

Sometimes, need addition parameters like

- `visited` to indicate whether the node has visited to avoid loops, which can explicit or implicit (using existing values).
- `state` with multiple states (no visited, in process, done) to indicate whether the node is visited or a cycle exists.
- `turple` object, for example to store `(current node, parent node)`.

## Tips

- How to find the **shortest** path?
  Add one more parameter to indicate the shortest path you have already found

## Typical Applications

- Find all vertices connected to a given source vertex
- Find a path between two vertices
