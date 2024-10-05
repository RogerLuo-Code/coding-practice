---
tags:
    - Breadth-First Search
---

# LC841. Keys and Rooms

## Problem Description

[LeetCode Problem 841](https://leetcode.com/problems/keys-and-rooms/): There are n rooms labeled from 0 to n - 1 and all the rooms are locked except for room 0. Your goal is to visit all the rooms. However, you cannot enter a locked room without having its key.

When you visit a room, you may find a set of distinct keys in it. Each key has a number on it, denoting which room it unlocks, and you can take all of them with you to unlock the other rooms.

Given an array rooms where rooms[i] is the set of keys that you can obtain if you visited room i, return true if you can visit all the rooms, or false otherwise.

## Clarification

- Each room may contain 0+ keys include no key
- Room `0` is not locked

## Assumption

-

## Solution

### Approach - BFS

Similar to BFS, visit a room, add all keys of each room to queue, and marked the room visited. Iterate until queue is empty

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

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  In the worst case, visit all rooms once.
- Space complexity: $O(n)$  
  In the worst case, add all room keys to the queue and set. The space complexity is $O(n + n) = O(n)$.

## Test
