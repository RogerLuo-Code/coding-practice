// Clarification:
//  - positive integer
//  - find num where num = i*i
// Solution:
//  - search i in the search space [1, num] such that i*i == num
//  - properties: if i*i > num, no need to check i+1, i+2, ..., num, since square of these values will be > num
//                if i*i < num, no need to check i-1, i-2, ..., 1, since square of these values will be < num
//                  i*i == num find the value
//  - Based on the properties, we can use binary search to reduce search space in each iteration
//  - corner case: i*i may over flow
//                  i = 16/i, 3, 4, 5
class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num <= 0) return false;
        
        int left = 1;
        int right = num;
        int mid;
        int res;
        int remain;
        
        //  0   1
        // [16, 17]
        //  l/m  r
        while (left <= right) {
            mid = left + (right - left)/2;
            res = num / mid; // avoid overflow mid*mid
            remain = num % mid;
            
            if (res == mid && remain == 0) {
                return true;
            }
            else if (res < mid) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        
        return false;
    }
};