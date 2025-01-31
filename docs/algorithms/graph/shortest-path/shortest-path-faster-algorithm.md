# Shortest Path Faster Algorithm


## Algorithm

- Use a `queue` to maintain the next starting vertex of the edge to be traversed.
- Add the vertex to the queue when the shortest distance of a vertex is relaxed and the
vertex is not in the `queue`.
- Iterate the process until the queue is empty.