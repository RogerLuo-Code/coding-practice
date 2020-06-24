class Search2dMatrix:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        if not matrix or not matrix[0]:
            return False
        
        n_row, n_col = len(matrix), len(matrix[0])
        tr, br = 0, n_row - 1
        lc, rc = 0, n_col - 1
        mr = -1

        while tr <= br:
            mr = tr + (br - tr)//2
            if (target < matrix[mr][0]):
                br = mr - 1
            elif (target > matrix[mr] [n_col - 1]):
                tr = mr + 1
            else:
                break
        
        if tr > br or mr < 0:
            return False
        
        while lc <= rc:
            mc = lc + (rc - lc)//2
            if (target < matrix[mr][mc]):
                rc = mc - 1
            elif (target > matrix[mr][mc]):
                lc = mc + 1
            else:
                return True
        
        return False

    def searchMatrixLinear(self, matrix: List[List[int]], target: int) -> bool:
        if not matrix or not matrix[0]:
            return False  # reommeded way in PEP8 -- style guide (https://www.python.org/dev/peps/pep-0008/)
        
        n_row, n_col = len(matrix), len(matrix[0])
        left, right = 0, n_row * n_col - 1
        
        while (left <= right):
            middle = left + (right - left)//2
            
            # Convert to matrix indices
            r = middle // n_col
            c = middle % n_col
            
            middle_val = matrix[r][c]
            
            if (target < middle_val):
                right = middle - 1
            elif (target > middle_val):
                left = middle + 1
            else:
                return True
            
        return False