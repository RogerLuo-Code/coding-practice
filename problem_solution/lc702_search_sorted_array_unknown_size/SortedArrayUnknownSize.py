# """
# This is ArrayReader's API interface.
# You should not implement it, or speculate about its implementation
# """
#class ArrayReader:
#    def get(self, index: int) -> int:

class SortedArrayUnknownSize:
    def search(self, reader, target):
        """
        :type reader: ArrayReader
        :type target: int
        :rtype: int
        """
        left, right = 0, 1
        
        # Search boundaries
        while (reader.get(right) < target):
            if (reader.get(right) == 2147483647):
                return -1
            left, right = right, right*2 # python int type is unbounded
            
        # Binary search
        while (left <= right):
            mid = left + (right - left)//2
            val = reader.get(mid)
            if val == target:
                return mid
            elif val > target or val == 2147483647:
                right = mid - 1
            else:
                left = mid + 1
        
        return -1