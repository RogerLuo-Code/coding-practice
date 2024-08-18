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
### Approach - BFS 1 Gate 
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
* Time complexity: $O(kmn)$  
	If there is ONLY one gate, the breadth-first search takes at most m×n steps to reach all rooms, therefore the time complexity is $O(mn)$. When there are `k` gates, on average the space will be essentially divided by `k` subspaces since each BFS will only search rooms with larger value. So the time complexity is $O(\frac{k}{k}mn) + O(\frac{k-1}{k}mn) + \cdots + O(\frac{1}{k}mn) = O(\frac{1+k}{2} mn)$. So in worth case, the time complexity is $O(kmn)$.
* Space complexity: $O(mn)$  
	The space complexity depends on the queue's size. We insert at most $m \times n$ points into the queue.

### Approach - BFS All Gates 
Add all gates to the queue first and then check the same layer of each node and add empty rooms to the queue. Essentially, always check the same layer of all gates, when checking 1st layer, if room is empty, update with `1` and add it to the queue. When checking `kth` layer, if the room is empty, update the room with value `k` and add it to the queue. For `kth` layer, if room is updated for one gate with `k`, no need to update it for another gate since it will be update by the same value.

=== "python"
    ```python
    from collections import deque

    class Solution:
        EMPTY = 2**31 - 1
        GATE = 0
        DIRECTIONS = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        def wallsAndGates(self, rooms: List[List[int]]) -> None:
            """
            Do not return anything, modify rooms in-place instead.
            """
            n_row = len(rooms)
            if n_row == 0:
                return
            n_col = len(rooms[0])
            queue = deque()

            for i_row in range(n_row):
                for i_col in range(n_col):
                    if rooms[i_row][i_col] == self.GATE:
                        queue.append((i_row, i_col))
            
            while queue:
                current_row, current_col = queue.popleft()
                for step_row, step_col in self.DIRECTIONS:
                    next_row = current_row + step_row
                    next_col = current_col + step_col
                    if next_row >= 0 and next_row < n_row \
                        and next_col >= 0 and next_col < n_col \
                        and rooms[next_row][next_col] == self.EMPTY:
                            rooms[next_row][next_col] = rooms[current_row][current_col] + 1
                            queue.append((next_row, next_col))
    ```

#### Complexity Analysis
* Time complexity: $O(mn)$  
	Since it is only check non-empty rooms once, so in worth case, the time complexity is $O(mn)$.
* Space complexity: $O(mn)$  
	The space complexity depends on the queue's size. We insert at most $m \times n$ points into the queue.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - BFS 1 gate |  $O(kmn)$ 	   	   	| $O(mn)$ | 
Approach - BFS all gates |  $O(mn)$      	| $O(mn)$  |

## Test