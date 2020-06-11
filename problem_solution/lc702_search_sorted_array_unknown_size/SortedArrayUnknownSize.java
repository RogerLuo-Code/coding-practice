/**
 * // This is ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * interface ArrayReader {
 *     public int get(int index) {}
 * }
 */

class SortedArrayUnknownSize {
    public int search(ArrayReader reader, int target) {
        int left = 0;
        int right = 1;
        
        // Search boundaries [Left, Right] to include target
        while ((reader.get(right) < target)) {
            if (reader.get(right) == 2147483647)
                return -1;
            
            left = right;
            if (right < Integer.MAX_VALUE/2)   
                right *= 2;  // or right <<= 1, double right until finding the right boundary (i.e., right > target)
            else{
                right = Integer.MAX_VALUE;
                break;
            }
        }
        // left = right/2;
        
        int mid;
        int val;  // value of reader.get(mid)
        // classic bineary search
        while (left <= right) {
            mid = left + (right - left)/2;
            
            val = reader.get(mid);
            if (val == 2147483647)
                right = mid - 1;
            else if (target < val)
                right = mid - 1;
            else if (target > val)
                left = mid + 1;
            else 
                return mid;
        }
        
        return -1; 
    }
}