---
tags:
    - Array
	- Math
	- Geometry
---

# LC1232. Check If It Is a Straight Line
## Problem Description
[LeetCode Problem 1232](https://leetcode.com/problems/check-if-it-is-a-straight-line/): You are given an array `coordinates`, `coordinates[i] = [x, y]`, where `[x, y]` represents the coordinate of a point. Check if these points make a straight line in the XY plane.

## Clarification
- Any duplicates
- Integer or float point

## Assumption

## Solution
### Approach - Math
To check if points make a straight line, we can go through points by pair and check whether they have the same slope. For any 2 points $(x_0, y_0)$ and $(x_1, y_1)$ and any given 3rd point $(x, y)$, if they are in a straight line, the slopes between points are equal:

$$ (y - y_1) / (x - x_1) = (y_1 - y_0) / (x_1 - x_0) \tag{1.1}$$

In order to avoid being divided by 0, change the above equation to the multiplication form:

$$ (y - y_1) (x_1 - x_0) = (x - x_1) (y_1 - y_0) $$

=== "Python"
	```python
	class Solution:
		def checkStraightLine(self, coordinates: List[List[int]]) -> bool:
			n_points = len(coordinates)

			if n_points == 1:
				return False

			if n_points == 2:
				return True

			(x0, y0), (x1, y1) = coordinates[:2]

			for i in range(2, len(coordinates)):
				(x, y) = coordinates[i]
				if (x1 - x0) * (y - y1) != (y1 - y0) * (x - x1):
					return False

			return True
	```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Need to to go through all points and check slope.
* Space complexity: $O(1)$  
	Use limited local variables. 

## Test