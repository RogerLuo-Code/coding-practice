---
tags:
    - Breadth-First Search
---

# LC841. Keys and Rooms

## Problem Description

[LeetCode Problem 841](https://leetcode.com/problems/keys-and-rooms/): There are n rooms
labeled from 0 to n - 1 and all the rooms are locked except for room 0. Your goal is to
visit all the rooms. However, you cannot enter a locked room without having its key.

When you visit a room, you may find a set of distinct keys in it. Each key has a number
on it, denoting which room it unlocks, and you can take all of them with you to unlock
the other rooms.

Given an array rooms where rooms[i] is the set of keys that you can obtain if you
visited room i, return true if you can visit all the rooms, or false otherwise.

## Clarification

- Each room may contain 0+ keys include no key
- Room `0` is not locked
- Same key may show up in different rooms

## Assumption

-

## Solution

### Approach - BFS

We can start from room 0 as root node and use breadth-first search (BFS) to visit the
rooms. When visited a room, add all keys of that room to a queue, and marked the room
visited. Iterate until the queue is empty.

=== "Python"
    ```python
    class Solution:
    def canVisitAllRooms(self, rooms: List[List[int]]) -> bool:
        queue = deque([0])
        visited = set([0])

        while queue:
            i = queue.popleft()
            for key in rooms[i]:
                if key not in visited:
                    queue.append(key)
                    visited.add(key)
                    if len(visited) == len(rooms):  #(1)
                        return True

        return len(visited) == len(rooms)
    ```

    1. Early termination.

=== "Python - BFS Function"
    ```python
    from collections import deque

    class Solution:
        def canVisitAllRooms(self, rooms: List[List[int]]) -> bool:
            visited = self.bfs(0, rooms)

            return len(visited) == len(rooms)

        def bfs(self, curr: int, rooms: List[List[int]]) -> Set[int]:
            queue = deque([curr])
            visited = set([curr])

            while queue:
                curr = queue.popleft()

                for next in rooms[curr]:
                    if next not in visited:
                        queue.append(next)
                        visited.add(next)
                        if len(visited) == len(rooms):
                            return visited

            return visited
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n + k)$ where $n$ is the total number of rooms and $k$ is the total
numbers of keys  
  In the worst case, visit all $n$ rooms exact once. When visited a room, need to go
  through all keys in the room.
- Space complexity: $O(n)$  
  In the worst case, add all room keys to the queue and set. The space complexity is
  $O(n + n) = O(n)$.

### Approach 2 - DFS

We can start from room 0 as root node and use either depth-first search (DFS) to visit
the rooms. During traversing, track the visited room. In the end, check whether number
of visited rooms equal n

=== "python"
    ```python
    class Solution:
        def canVisitAllRooms(self, rooms: List[List[int]]) -> bool:
            visited = set()
            self.dfs(0, rooms, visited)

            return len(visited) == len(rooms)

        def dfs(self, curr: int, rooms: List[List[int]], visited: Set[int]) -> None:
            visited.add(curr)

            for next in rooms[curr]:
                if next not in visited:
                    self.dfs(next, rooms, visited)
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n + k)$  
  It visits all $n$ rooms exact once. When visited a room, need to go through all keys
  in the room.
- Space complexity: $O(n)$  
  The space used is mainly from recursive function call stack. In the worst case, it
  could go deep as $n-1$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach - BFS |  $O(n + k)$    | $O(n)$ |
Approach - DFS |  $O(n + k)$    | $O(n)$  |

## Test
