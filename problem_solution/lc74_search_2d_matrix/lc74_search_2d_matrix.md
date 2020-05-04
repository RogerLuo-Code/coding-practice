# Leetcode Problem 74 - Search a 2D Matrix

## Problem Description <a id="problem"></a>
[Leetcode Problem 74:](https://leetcode.com/problems/search-a-2d-matrix/) Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
* Integers in each row are sorted from left to right.
* The first integer of each row is greater than the last integer of the previous row.

## Analysis
* Clarifications
    - sorted or unsorted?
    - how is it sorted? row, column, any other properties
    - how big is the size?
    - data type
    - return value? boolean, linear index, or indices (row and column)
* Go through some examples
* Solution
    - Assumptions: regular 2d matrix with the same number of columns
    - Input/output (signature): input 2D int array and int scalar; output boolean
    - Corner cases: empty matrix or with zero columns or rows
    - Algorithm: bineary search
    - Time/space complexity
* Coding
* Test
    - Test corner cases: zero matrix 
    - Test general cases   


## Approaches
Taking advantages of [two above mentioned properties] (#problem) of the matrix, we can use binary search here. Two approaches:
1. Use binary search twice: search along the row and then along the column for the target row (if exists)
2. The matrix $m \times n$ can be considered as a sorted array of length $m \times n$. Then apply binary search on a sorted array instead of a matrix.
![Matrix to Array](https://leetcode.com/problems/search-a-2d-matrix/Figures/74/matrix2.png)

### **Approach 1**: Binary search twice on the matrix  
Binary search along the row and then along the column for the target row.
* Search along the row is a slightly modified version of classic binary search. It uses the first and last element of middle row for comparison instead of just one element. The row with potential target should meet condition: `target >= matrix[mr][0] && target <= matrix[mr][nCol-1]`
* Search along the column is a classic binary search.

```java
class Solution {
    public boolean searchMatrix(int[][] matrix, int target) {
        if (matrix.length == 0 || matrix[0].length == 0)
            return false;
        
        int nRow = matrix.length;
        int nCol = matrix[0].length; 
        
        // Initialization of row and column target
        int targetRow = -1;
        int targetCol = -1;
        
        
        int tr = 0;   // top row 
        int br = nRow - 1; // bottom row
        int mr; // middle row between top and bottom rows
        // Binary search along the row
        while (tr <= br){
            mr = tr + (br - tr)/2;
            if (target < matrix[mr][0]) {
                br = mr - 1; 
            }
            else if (target > matrix[mr][nCol-1]) {
                tr = mr + 1;
            }
            else
            {
                targetRow = mr;
                break;
            }
        }
        
        if (targetRow < 0)
            return false;
        
        int lc = 0; // left column
        int rc = nCol - 1; // right column
        int mc;     // middle column between left and right columns
        // Binary search along the column
        while (lc <= rc){
            mc = lc + (rc - lc)/2;
            if (target < matrix[targetRow][mc]) {
                rc = mc - 1;
            }
            else if(target > matrix[targetRow][mc]) {
                lc = mc + 1;     
            }
            else{
                targetCol = mc;
                break;
            }       
        }
        
        if (targetRow >= 0 && targetCol >= 0)
            return true;
        else
            return false;
        
    }
}
```


### **Approach 2**: Binary search on a sorted array (transformed from the matrix)
Based on [two above mentioned properties](#problem), the matrix $m \times n$ can be considered as a sorted array of length $m \times n$. A classic binary search can be applied on this sorted array.

Matrix to array: `matrix[r][c] -> a[r*m+c]`  
Array to matrix: `a[x] -> matrix[x/m][x%m]`

**Drawbacks**  
* `m*n` may overflow for large m and n
* `/` and `%` are expensive operations

```java
class Solution {
    public boolean searchMatrix(int[][] matrix, int target) {
    // Use binary search on linear index of a matrix
    if (matrix.length == 0 || matrix[0].length == 0) {
        return false;
    }
        
    int nRow = matrix.length;
    int nCol = matrix[0].length; 
    
    int left = 0;
    int right = nRow*nCol - 1; // -1 for zero-based indexing
    int middle;
    int iRow;
    int iCol;
        
    while (left <= right){
        middle = left + (right - left)/2;
        
        // Convert linear index to matrix indices
        // Use nCol below for matrix sorted by rows
        // Otherwise use nRow for matrix sorted by columns
        iRow = middle/nCol;
        iCol = middle%nCol;
        
        if (target < matrix[iRow][iCol])
            right  = middle - 1;
        else if (target > matrix[iRow][iCol])
            left = middle + 1;
        else
            return true;
            
    }
    
    return false;
        
    }
}
```

## Complexity Analysis
* **Time complexity**: $\mathcal{O}(\log(mn))$ for both approaches.  
  - Approacheh 1: For the worse case, search along the row needs $\log m$ number of iterations  and search along the column needs $\log n$ number of iterations. So the total number is $\log mn  = \log m + \log n$ for the worst case. Therefore the time complexity is $\mathcal{O}(\log(mn))$.
  - Approach 2: It uses the classic binary searc on $m \times n$ elements. Therefore the time complexity is $\mathcal{O}(\log(mn))$. 
* **Space complexity**: $\mathcal{O}(1)$.  
Both approaches use several more variables than classic binary search but they still use $\mathcal{O}(1)$ space 

|     | Time Complexity | Space Complexity  
| ----- | ----- | ----- |  
| Approach 1 | $\mathcal{O}(\log(mn))$ | $\mathcal{O}(1)$ |  
| Approach 2 | $\mathcal{O}(\log(mn))$ | $\mathcal{O}(1)$ | 

