---
tags:
    - Binary Search
    - Matrix
---

# LC240. Search a 2D Matrix II
## Problem Description
[LeetCode Problem 240](https://leetcode.com/problems/search-a-2d-matrix-ii/): Write an efficient algorithm that searches for a value `target` in an `m x n` integer matrix `matrix`. This matrix has the following properties:

- Integers in each row are sorted in ascending from left to right.
- Integers in each column are sorted in ascending from top to bottom.

![](assets/searchgrid2.jpg)

**Input:** matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5  
**Output:** true  

## Clarification
- Search target in matrix
- row-wise and column-wise ascending
- return index or true/false

## Assumption

## Solution
### Approach - Binary Search by Row
Go through each row and search each row by using binary search since it is sorted.

=== "Python"
    ```python
    class Solution:
        def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
            m, n = len(matrix), len(matrix[0])

            for i_row in range(m):
                left = 0
                right = n - 1
                while left <= right:
                    mid = (left + right) // 2
                    if matrix[i_row][mid] == target:
                        return True
                    elif target < matrix[i_row][mid]:
                        right = mid - 1
                    else:
                        left = mid + 1

            return False
    ```

#### Complexity Analysis
* Time complexity: $O(m \log n)$  
	There are $m$ rows and search each row takes at most $\log n$ steps using binary search. In the worst case, it will search all rows, $m \log n$.
* Space complexity: $O(1)$  
	Use several variables to search

### Approach - Skip Row Or Column
Based on the sorted properties, starting from bottom left or top right

- if target > value, skip the current column
- if target < value, skip the current row

=== "Python"
    ```python
    class Solution:
        def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
            m, n = len(matrix), len(matrix[0])

            i_row, j_col = m - 1, 0

            while i_row >= 0 and j_col < n:
                if matrix[i_row][j_col] == target:
                    return True
                elif target > matrix[i_row][j_col]:
                    j_col += 1  # Remove the current column
                else:
                    i_row -= 1  # Remove the current row

            return False
    ```

### Approach - Binary Search by Sub Matrix
Divide matrix into 4 quadrants:

- if target < center element, bottom right quadrants can be excluded; 
- if target > center element, top left quadrants can be excluded;
Continue to search the rest of 3 quadrants.

```
   zone 1      zone 2
*  *  *  * | *  *  *  *
*  *  *  * | *  *  *  *
*  *  *  * | *  *  *  *
*  *  *  * | *  *  *  *
-----------------------
*  *  *  * | *  *  *  *
*  *  *  * | *  *  *  *
*  *  *  * | *  *  *  *
*  *  *  * | *  *  *  *
  zone 3      zone 4
```

=== "C++"
    ```c++
    class Solution {
    public:
        bool searchMatrix(vector<vector<int>>& matrix, int target) {
            if (matrix.empty() || matrix[0].empty()) return false;

            int nRow = matrix.size(); // number of rows
            int nCol = matrix[0].size(); // number of columns

            return searchSubMatrix(matrix, target, 0, nRow - 1, 0, nCol - 1);

        }

        bool searchSubMatrix(vector<vector<int>>& matrix, int target, int rStart, int rEnd, int cStart, int cEnd) {
            if ((rStart > rEnd) || (cStart > cEnd)) return false;

            int rMid = rStart + (rEnd - rStart)/2;
            int cMid = cStart + (cEnd - cStart)/2;
            int midVal = matrix[rMid][cMid];

            if (target == midVal) {
                return true;
            }
            else if (target < midVal) {
                // Exclude zone 4; search zone 1 + zone 2 and zone 3
                return searchSubMatrix(matrix, target, rStart, rMid - 1, cStart, cEnd) 
                    || searchSubMatrix(matrix, target, rMid, rEnd, cStart, cMid - 1);
            }
            else {
                // Exclude zone 1; search zone 3 + zone 4 and zone 2
                return searchSubMatrix(matrix, target, rMid + 1, rEnd, cStart, cEnd)
                    || searchSubMatrix(matrix, target, rStart, rMid, cMid + 1, cEnd);
            }
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(\log (mn))$  
	Every step it excludes $1/4$ quadrant and search the rest $1/2$ and $1/4$ sub matrix. 
    When formulate this search path as a tree, the worst path is search $1/2$ the space each step and the best path is search $1/4$ space each step.

    ```
                  1
             /         \
            1/2        1/4
           /   \      /   \
         1/2   1/4  1/2   1/4
    ```
* Space complexity: $O(\log (mn))$  
	Need to recursive call functions at most $\log (mn)$ times and need to store function call stack.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Binary Search by Row |  $O(m \log n)$ 	   	   	| $O(1)$ | 
Approach - Skip Row Or Column |  $O(m + n)$      		| $O(1)$  |
Approach - Binary Search by Sub Matrix | $O(\log (mn))$ | $O(\log (mn))$ |

## Test