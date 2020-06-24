class Solution {
    public boolean searchMatrix(int[][] matrix, int target) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0)
            return false;
        
        int nRow = matrix.length;
        int nCol = matrix[0].length; 
            
        int tr = 0;   // top row 
        int br = nRow - 1; // bottom row
        int mr = -1; // middle row between top and bottom rows
        
        // Binary search along the row
        while (tr <= br){
            mr = tr + (br - tr)/2;
            if (target < matrix[mr][0]){
                br = mr - 1; 
            }
            else if (target > matrix[mr][nCol-1]){
                tr = mr + 1;
            }
            else
            {
                break;
            }
        }
        
        if (tr > br || mr < 0)
            return false;
        
        int lc = 0; // left column
        int rc = nCol - 1; // right column
        int mc;     // middle column between left and right columns
        // Binary search along the column
        while (lc <= rc){
            mc = lc + (rc - lc)/2;
            if (target < matrix[mr][mc]){
                rc = mc - 1;
            }
            else if(target > matrix[mr][mc]){
                lc = mc + 1;     
            }
            else{
                return true;
            }       
        }
        
        return false;
        
    }

    public boolean searchMatrixLinear(int[][] matrix, int target) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0)
            return false;
        
        int nRow = matrix.length; 
        int nCol = matrix[0].length;
        
        int left = 0;
        int right = nRow*nCol - 1; // -1 for zero-based indexing, assumption no overflow from nRow*nCol
        int middle; 
        int iRow;
        int iCol;
        
        // classic binary search of a target with linear to matrix indices conversion
        while (left <= right){
            middle = left + (right - left)/2;
            
            // Conversion from linear index to matrix indices
            // If it is sorted by column, use nRow for conversion
            iRow = middle/nCol; // row index
            iCol = middle%nCol; // column index
            
            if (target < matrix[iRow][iCol])
                right = middle - 1;
            else if (target > matrix[iRow][iCol])
                left = middle + 1;
            else
                return true;
        }
        
        return false;
    }
}