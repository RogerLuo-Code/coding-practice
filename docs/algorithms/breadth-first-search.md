# Breadth-first Search (BFS)

The breadth-first search (BFS) is usually used to find the shortest path from the root note to the target node.

Sometimes, need a `visited` hash set to track nodes visited to prevent getting stuck in an infinite loop, e.g., in graph with cycle. 

Note may not need to use a `visited`. Can check the existing value to indicate whether it is visited or not.