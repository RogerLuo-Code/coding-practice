class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if (nums.empty()) {
            return -1;
        }
        
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        
        // [1,  3, 5, 6], target = 2;
        //  l t m     h 
        //  l   h         stop while loop
        
        // [1,  3,  5,  6], target = 7
        //  l   m        h  t, mid = 1; nums[mid] = 3 < target
        //      l,       h  t; nums[mid] = 5 < target
        //          l,   h  t; end while loop
        while (left < right) {
            mid = left + (right - left)/2;
            
            if (target == nums[mid]) {
                return mid;
            }
            else if (target > nums[mid]) {
                left = mid + 1;  // mid is not the insert position but mid + 1 can be the potential insert position.
            }
            else {
                right = mid; // mid can be the insert position
            }
        }
        
        // 1 element left at the end
        // post-processing
        return nums[left] < target ? left + 1 : left;
    }
};