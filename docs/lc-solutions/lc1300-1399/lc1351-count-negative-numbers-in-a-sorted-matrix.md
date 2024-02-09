---
tags:
    - Binary Search
    - Matrix
---

# LC1351. Count Negative Numbers in a Sorted Matrix
## Problem Description
[LeetCode Problem 1351](https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix): Given a `m x n` matrix `grid` which is sorted in non-increasing order both row-wise and column-wise, return _the number of **negative**numbers in_ `grid`.

**Example 1:**

**Input:** grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]  
**Output:** 8  
**Explanation:** There are 8 negatives number in the matrix.  

## Clarification
- matrix
- What does it mean sorted? non-increasing in row-wise and column-wise?
- return # of negative numbers
- go through examples

## Assumption

## Solution
### Approach - Binary Search
Since the matrix is sorted, we can go through each row and use modified binary search to find the first negative number. On that row, all numbers on the right of the negative number all also negative. The we can count negative numbers row by row.

=== "Python"
    ```python
    class Solution:
        def countNegatives(self, grid: List[List[int]]) -> int:
            m, n = len(grid), len(grid[0])

            num_negative = 0
            for i_row in range(m):
                row_value = grid[i_row]

                left = 0
                right = n - 1
                while left < right:
                    mid = (left + right) // 2
                    if row_value[mid] < 0:
                        right = mid
                    else:
                        left = mid + 1

                if row_value[left] < 0:
                    num_negative += n - left

            return num_negative
    ```

#### Complexity Analysis
* Time complexity: $O(m \log n)$  
	In the worst case, for each row, it takes at most $\log n$ steps to find the first negative number using binary search and we need to do it for $m$ rows. So the time complexity is $O(m \log n)$
* Space complexity: $O(1)$  
	Only use several variables for searching.

### Approach - Stairs
If replacing positive numbers or 0 with `+` sign and negative numbers with `-`sign, the problem can be viewed as climb up or go down stairs. The `-` form the stairs. 
```
[ + + + -
  + + + -
  + + - -
  - - - - ]
```
This idea is inspired by [@rock's solution](https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/solutions/510249/java-python-3-2-similar-o-m-n-codes-w-brief-explanation-and-analysis/)

Since the matrix is sorted in non-increasing order both row-wise and column-wise, there are some interesting properties:

1. Along a row, all numbers on the right of a negative number are negative. (non-increasing row-wise)
2. Along a column, all numbers below a negative number are negative. (non-increasing column-wise)
3. For the first negative on a row, we can divide a matrix by 4 quadrants with this negative number at the corner of each quadrant:

    1. The top left quadrant only contains positive numbers (except the negative number at the corner)  
    2. The top right quadrant may contain either positive or negative numbers  
    3. The bottom left quadrant may contain either positive or negative numbers  
    4. The bottom right quadrant only contains negative numbers  

If climbing up stairs, only need to search the top right quadrant (3b). If going down stairs, only need to search the bottom left quadrant (3c).

=== "Python"
    ```python
    class Solution:
        def countNegatives(self, grid: List[List[int]]) -> int:
            m, n = len(grid), len(grid[0])
            n_negative = 0

            # Start from the bottom left number and step up
            i_row, i_col = m - 1, 0
            while i_row >= 0 and i_col < n:
                if grid[i_row][i_col] >= 0:
                    i_col += 1  # (1)
                else:
                    n_negative += n - i_col  #(2)
                    i_row -= 1  # (3)

            return n_negative
    ```

    1. Always move right since no negative value on the left. Refer to property 3b
    2. Count the rest of negative numbers. Refer to property 1
    3. Step up

#### Complexity Analysis
* Time complexity: $O(m + n)$  
	In the worst case, climbing up stairs from bottom to top takes at most $m + n$ steps.  
* Space complexity: $O(1)$  
	Only use two variables for indexing.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Binary Search |  $O(m \log n)$ 	   	   	| $O(1)$  
Approach - Stairs |  $O(m + n)$      		| $O(1)$


Is $O(m \log n)$ better than $O(m + n)$?

- For general cases where $m$ and $n$ are in the same magnitude (e.g., $n = c \times m$ where $c > 1$ is a constant), $O(m + n)$ is better.  
$O(m + n) = O((c + 1) \times m) = O(m) < O(m \log(cm)) = O(m (\log c + \log m)) = O(m \log m)$  
- For rare cases where $n >> m$ (e.g. $n = m^2$), $O(m \log n)$ is better.  
$O(m \log n) = O(m \log(m^2)) = O(2m \log m) = O(m \log m) < O(m^2) = O(m + m^2) = O(m + n)$.

## Test