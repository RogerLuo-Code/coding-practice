class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        int mid; 
        //  0  1  2  3  4
        // [2, 0, 1, 1, 1]
        //  l     m     r
        
        while (left < right) {
            mid = left + (right - left)/2;
            
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            }
            else if (nums[mid] < nums[right]) {
                right = mid;
            }
            else {
                right--;
            }
        }
        
        return nums[left];
    }
};