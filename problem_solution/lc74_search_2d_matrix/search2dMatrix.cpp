#include <vector>

class search2dMatrix {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty())
        {
            return false;
        }
        
        int nRow = matrix.size();
        int nCol = matrix[0].size();
        int left = 0;
        int right = nRow*nCol - 1;
        int mid, element, iRow, iCol;
        
        while (left <= right)
        {
            mid = left + (right - left)/2;
            
            iRow = mid/nCol;
            iCol = mid%nCol;
            
            element = matrix[iRow][iCol];
            if (target == element) return true;
            else if (target < element) right = mid - 1;
            else left = mid + 1;
        }
        return false;
    }
};