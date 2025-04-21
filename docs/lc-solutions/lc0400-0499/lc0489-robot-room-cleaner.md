---
tags:
    - Backtracking
---

# 489. Robot Room Cleaner

## Problem Description

[LeetCode Problem 489](https://leetcode.com/problems/robot-room-cleaner/description/):
You are controlling a robot that is located somewhere in a room. The room is modeled as
an `m x n` binary grid where `0`represents a wall and `1` represents an empty slot.

The robot starts at an unknown location in the room that is guaranteed to be empty,
and you do not have access to the grid, but you can move the robot using the given API `Robot`.

You are tasked to use the robot to clean the entire room (i.e., clean every empty cell
in the room). The robot with the four given APIs can move forward, turn left,
or turn right. Each turn is `90` degrees.

When the robot tries to move into a wall cell, its bumper sensor detects the obstacle,
and it stays on the current cell.

Design an algorithm to clean the entire room using the following APIs:

```java
interface Robot {
  // returns true if next cell is open and robot moves into the cell.
  // returns false if next cell is obstacle and robot stays on the current cell.
  boolean move();

  // Robot will stay on the same cell after calling turnLeft/turnRight.
  // Each turn will be 90 degrees.
  void turnLeft();
  void turnRight();

  // Clean the current cell.
  void clean();
}
```

**Note** that the initial direction of the robot will be facing up. You can assume all
four edges of the grid are all surrounded by a wall.

## Clarification

- 0: wall; 1: empty
- All empty cells are reachable?
- Does the robot need to return to its original position?

## Assumption

-

## Solution

### Approach 1: Backtracking

Since we don't know the coordinates or layout, we simulate the robot's position using
**coordinates relative to the start** `(0, 0)`. We can use a depth-first search (DFS)
approach to explore all possible paths the robot can take.

The robot can move in four directions: up, right, down, and left. When moving, we will check

- if the next cell is empty and not visited. If it is, we will move the robot to that cell,
clean it, and continue exploring from there.
- if we reach a dead end (i.e., all adjacent cells are either walls or already visited),
we will **backtrack** to the previous cell and try another direction.

=== "Python"
    ```python
    class Solution:
        def cleanRoom(self, robot):
            """
            :type robot: Robot
            :rtype: None
            """
            self.DIRECTIONS = [(-1, 0), (0, 1), (1, 0), (0, -1)]  # up, right, down, left
            self.visited = set()
            self.dfs(robot, 0, 0, 0)

        def dfs(self, robot, i_row: int, i_col: int, i_d: int) -> None:
            self.visited.add((i_row, i_col))
            robot.clean()

            # Iterate all 4 directions, starting from the current direction,
            # keep turning right (or left) until all directions explored
            for i in range(4):
                i_d_next = (i_d + i) % 4
                i_row_next = i_row + self.DIRECTIONS[i_d_next][0]
                i_col_next = i_col + self.DIRECTIONS[i_d_next][1]

                if (i_row_next, i_col_next) not in self.visited and robot.move():
                    self.dfs(robot, i_row_next, i_col_next, i_d_next)
                    self.go_back(robot)

                # Try another direction by turning right (we can also turn left here)
                robot.turnRight()

        def go_back(self, robot):
            # Turn 180 degrees to face the opposite direction
            robot.turnRight()
            robot.turnRight()

            # Move back to the previous cell
            robot.move()

            # Turn 180 degrees again to restore the original direction
            robot.turnRight()
            robot.turnRight()
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n - m)$ where $n$ is the number of cells and $m$ is the number of obstacles.  
  The robot will visit each empty cell once. At each cell, it will check 4 directions,
  resulting in $4(n - m)$ operations.
- Space complexity: $O(n - m)$  
    - The `visited` hashset will store up to $n - m$ cells.
    - The recursion stack can go as deep as $n - m$ in the worst case.
    - So the overall space complexity of the algorithm is $O(n - m)$.

## Test

1. **Single Cell Room**  
   Input: A room with only one empty cell.  
   Output: The robot cleans the single cell.

2. **Room with Obstacles**  
   Input: A room with walls blocking some cells.  
   Output: The robot cleans all reachable cells.

3. **Large Empty Room**  
   Input: A large room with no obstacles.  
   Output: The robot cleans all cells.

4. **Edge Case: All Walls**  
   Input: A room where all cells are walls.  
   Output: The robot does nothing.