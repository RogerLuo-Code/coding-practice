// Clarification: 
//  - non-negative integer
//  - return integer
//  - compute the square root
// Solution:
//  - search space [1, x] to find i elements such that (i*i <= x) && ((i+1)*(i+1) > x)
//  - use binary search idea
class Solution {
public:
    int mySqrt(int x) {
        if (x <= 1) {
            return x;
        }

        int left = 1;
        int right = x;
        int mid;

        while (left <= right) {
            mid = left + (right - left)/2;

            if ((mid <= x/mid) && ((mid + 1) > x/(mid + 1))) {
                return mid;
            }
            else if (mid > x/mid) {
                right = mid - 1;
            }
            else {
                left = mid + 1; 
            }
        }
        return -1;
    }
};