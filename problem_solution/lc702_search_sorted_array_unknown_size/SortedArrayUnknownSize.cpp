// Clarification:
//  - integer array, sorted, ascending
//  - array size is unknow. How big? exceeds integer max?
// Go through examples
// Solution:
//  - Input/output: ArrayReader object, int target
//  - Assumption: array size is less than integer max
//  - Algorithm: find array size and then use binary search
//  - Corner case:
// Coding
// Test

/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     int get(int index);
 * };
 */

class Solution {
public:
    int search(const ArrayReader& reader, int target) {
        int left = 0;
        int right = 10;
        int maxInt = numeric_limits<int>::max()/2;
        
        while (reader.get(right) < target)
        {
            if (reader.get(right) == 2147483647)
            {
                return -1;
            }
            left = right;
            if (right >= maxInt/2)
            {
                right = maxInt;
                break;
            }
            else
            {
                right = 2*right;
            }  
        }
        
        int mid;
        int value;
        while (left <= right)
        {
            mid = left + (right - left)/2;
            value = reader.get(mid);
            if (value == 2147483647) right = mid - 1;
            else if (target < value) right = mid - 1;
            else if (target > value) left = mid + 1;
            else return mid;
        }
        return -1;
    }
};