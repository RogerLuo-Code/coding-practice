// Clarification:
//  - integer, sorted, ascending
//  - rotated? 
//  - any duplicates?
// Go through examples
// Soluton:
//  input/output: vector<int>, int; int
//  assumption: no duplicates
//  algorithm: use binary search for this type of rotated array
//  time/space complexity
// Coding
// Test

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        
        while (left <= right)
        {
            mid = left + (right - left)/2;
            
            if (target == nums[mid])
            {
                return mid;
            }
            else if (nums[mid] >= nums[left]) // left to mid is sorted
            {
                if (target >= nums[left] && target < nums[mid]) // check whether target is within the sorted range
                    right = mid - 1; 
                else 
                    left = mid + 1;
            }
            else // mid to right is sorted
            {
                if (target > nums[mid] && target <= nums[right]) // check whether target is whithin the sorted range
                    left = mid + 1;
                else 
                    right = mid - 1;
            }
        }
        return -1;   
    }
};