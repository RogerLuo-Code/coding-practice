# LeetCode Problem 240 - Search a 2D Matrix II

## Problem Description
[LeetCode Problem 240](https://leetcode.com/problems/search-a-2d-matrix-ii/): Write an efficient algorithm that searches for a target value in an m x n integer matrix. The matrix has the following properties:
* Integers in each row are sorted in ascending from left to right.
* Integers in each column are sorted in ascending from top to bottom.

## Analysis

## Approaches
The 2nd approach uses some idea of binary search but not exactly the same as binary search -- binary search excludes search space by half while the 2nd approach only excludes 1/4th search space. Counter-intuitively, the time complexity is worse than the linear time complexity of the first approach  
### Approach 1
Start from top-right corner,
* If target > element in top right, exclude the entire row and move down to the next row since the row is sorted in ascending order and all elements in the current row are smaller than the target;  
* If target < element in top right, exclude the entire column and move left to the next column since the column is sorted in ascending order and all elements in the current column are larger than the target 

Similarly, we can start from bottom-left corner. 

### Approach 2
Divide matrix into 4 quadrants,  
* If target < center element, bottom right quadrants (include center element) can be excluded since row and column are sorted in ascending order and all elements in that quadrant are larger than the target;
* If target > center element, top left quadrants (include center element) can be excluded since row and column are sorted in ascending order and all elements in that quadrant are smaller than the target  

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
Recursively divide matrix into 4 quadrants, exclude one quadrant and search the rest of 3 quadrants.

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}((mn)^{\log_4^3})$   
The time complexity can be expressed as $T(n) = T(n/2) + T(n/4) + 1$ or $T(n) = 3T(n/4) + 1$. 
So $T(n) = 3T(n/4) + 1 = 9T(n/16) + 3 + 1 = 27T(n/64) + 9 + 3 + 1 = 3^{\log_4^n} + (3^{\log_4^n-1} + \cdots + 9 + 3 + 1) = 2 \times 3^{\log_4^n} = 2 \times 3^{\log_3^n/\log_3^4} = 2 \times n^{1/\log_3^4} = 2 \times n^{\log_4^3}$ 
Using rules: $3^{\log_4^n-1} + \cdots + 9 + 3 + 1 = 3^{\log_4^n}$, $\log_4^n = \log_3^n/\log_3^4$, and $\log_4^3 = 1/\log_3^4$.
* **Space complexity**: $\mathcal{O}(1)$ as using several internal variables. 

### Complexity Summary
|     | Time Complexity | Space Complexity  
| ----- | ----- | ----- |  
| Approach 1 | $\mathcal{O}(m + n)$ | $\mathcal{O}(1)$ |  
| Approach 2 | $\mathcal{O}((mn)^{\log_4^3})$ | $\mathcal{O}(1)$ | 