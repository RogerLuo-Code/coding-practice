// Clarification:
//  - elements in 2nd row could be eiher smaller or larger than some elements in the first row
//  - which is row and which is column
//  - go through examples
// Solution:
//  - input/output: vector of vectors, int; bool
//  - algorithm:
//      - method 1: start from top right corner, 
//                  if target is larger, moves row from top to bootom since each row is ascending order and the target can not be in the entire row of current position; 
//                  otherwise, move columns from right to left, since each column is in ascending order and the target can not be in the entire column of current position;
//      - method 2: divide matrix into 4 quadrants, if target < center element, bottom right quadrants can be excluded; target > center element, top left quadrants can be excluded
// Coding:
//  - Time complexity: method1 O(m+n); mehtod2: T(n) = T(n/2) + T(n/4) + O(1) or T(n) = 3T(n/4) + O(1)
//    Method 2: 
//      T(mn)=3T(mn/4)+c
// T(mn)=3[3T(mn/16)+c]+c = 9 * T(mn/16) + 4c
// T(mn)=9[3T(mn/64)+c]+4c = 27 * T(mn/64) + (1+3+9)c
// ...

// Let's say mn ~ 4^K, where K = log_4(mn), then
// T(mn) = 3^K * q + (1+3+9+27+...+3^K) * c
// ~ 3^K
// ~ e^(log3/log4*log(mn))
// ~ (mn)^(log3/log4)
// ~ (mn)^.79
//  - Space complexity: method1 O(1); 
//
// Test  

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        
//         // Method 1:
//         if (matrix.empty() || matrix[0].empty()) return false;
        
//         int nRow = matrix.size(); // number of rows
//         int nCol = matrix[0].size(); // number of columns
        
//         int iRow = 0; 
//         int jCol = nCol - 1;
        
//         while ((iRow < nRow) && (jCol >= 0)) {
//             if (target == matrix[iRow][jCol]) {
//                 return true;
//             }
//             else if (target < matrix[iRow][jCol]) {
//                 jCol--;
//             }
//             else {
//                 iRow++;
//             }
//         }
        
//         return false;
        
        // Method 2:
          // zone 1      zone 2
        // *  *  *  * | *  *  *  *
        // *  *  *  * | *  *  *  *
        // *  *  *  * | *  *  *  *
        // *  *  *  * | *  *  *  *
        // -----------------------
        // *  *  *  * | *  *  *  *
        // *  *  *  * | *  *  *  *
        // *  *  *  * | *  *  *  *
        // *  *  *  * | *  *  *  *
        //   zone 3      zone 4
        
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