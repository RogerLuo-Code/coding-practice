# Depth-First Search


## Implementation

There are two ways to implement DFS:

- Use recursion
  Use the implicit stack provided by the system, also know as the [Call Stack](https://en.wikipedia.org/wiki/Call_stack).
- Use Stack

Sometimes, need addition parameters like

- `visited` to indicate whehter the node has visited to avoid loops
- `state` with multiple states (no visited, in process, done) to indicate whether the node is visited or a cycle exists.


## Tips

- How to find the **shortest** path?
  Add one more parameter to indicate the shortest path you have already found