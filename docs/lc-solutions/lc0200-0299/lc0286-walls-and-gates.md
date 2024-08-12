---
tags:
    - Breadth-First Search
---

# LC286. Walls and Gates
## Problem Description
[LeetCode Problem 286](https://leetcode.com/problems/walls-and-gates/): You are given an `m x n` grid `rooms` initialized with these three possible values.

- `-1` A wall or an obstacle.
- `0` A gate.
- `INF` Infinity means an empty room. We use the value `231 - 1 = 2147483647` to represent `INF` as you may assume that the distance to a gate is less than `2147483647`.

Fill each empty room with the distance to _its nearest gate_. If it is impossible to reach a gate, it should be filled with `INF`.

## Clarification
- There are multiple gates. Room value is the steps to the nearest gate.

## Assumption
- If the room can be reached, steps to the gate < `Inf`

## Solution
### Approach - Breadth-First Search
Find gate one at a time and use breadth-first search to search all rooms the gate can reach and update room value if is smaller.

Note that no need to store visited rooms since room value reflects whether it is visited. Another trick is to update the room value based on last room and no need to stop step value.

=== "Python"
    ```python
    class Solution:
    def wallsAndGates(self, rooms: List[List[int]]) -> None:
        """
        Do not return anything, modify rooms in-place instead.
        """
        queue = deque()
        n_row = len(rooms)
        n_col = len(rooms[0])
        
        for i_row in range(n_row):
            for j_col in range(n_col):
                if rooms[i_row][j_col] == 0:                
                    queue.append((i_row, j_col))
                    
                    # Use BFS to travers roomsa and update the room value
                    # for the gate
                    while queue:
                        size = len(queue)
                        for i in range(size):
                            base_row, base_col = queue.popleft()
                            for row_step, col_step in [(-1, 0), (0, 1), (0, -1), (1, 0)]:
                                    curr_row = base_row + row_step
                                    curr_col = base_col + col_step
                                    if curr_row >= 0 and curr_row < n_row \
                                        and curr_col >= 0 and curr_col < n_col \
                                        and rooms[curr_row][curr_col] > rooms[base_row][base_col] + 1:
                                            rooms[curr_row][curr_col] = rooms[base_row][base_col] + 1
                                            queue.append((curr_row, curr_col))
    ```

#### Complexity Analysis
* Time complexity: $O(mn)$  
	If there is ONLY one gate, the breadth-first search takes at most m×n steps to reach all rooms, therefore the time complexity is $O(mn)$. When there are `k` gates, the space will be essentially divided by `k` subspaces since each BFS will only search rooms with larger value. So the time complexity is $O(mn)$
* Space complexity: $O(mn)$  
	The space complexity depends on the queue's size. We insert at most $m \times n$ points into the queue.

## Test