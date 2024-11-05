# Depth-First Search

## Introduction
Goal: Systematically search through a graph

```python
DFS(to visit a vertex v)
    Mark v as visited.
    Recursively visited all unmarked vertices w adjacent to v
```

## Implementation

There are two ways to implement DFS:

- Use recursion
  Use the implicit stack provided by the system, also know as the [Call Stack](https://en.wikipedia.org/wiki/Call_stack).
- Use Stack

Sometimes, need addition parameters like

- `visited` to indicate whether the node has visited to avoid loops, which can explicit or implicit (using existing values)
- `state` with multiple states (no visited, in process, done) to indicate whether the node is visited or a cycle exists.

## Tips

- How to find the **shortest** path?
  Add one more parameter to indicate the shortest path you have already found

## Typical Applications

- Find all vertices connected to a given source vertex
- Find a path between two vertices
