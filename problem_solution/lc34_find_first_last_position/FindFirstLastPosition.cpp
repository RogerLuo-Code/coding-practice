// Clarification:
//  - sorted, ascending
//  - size of array?
//  - range of elements?
// Go through exampels
// Solution:
//  - input/output: vetor<int>&, int; vector<int>
//  - assumption: array size and range of elements are within integer range
//  - solution: using binary search twice, find the starting position first and then the ending position
// Coding:
// Test
//  - Test corner case: empty, 1 element, 2 elements, not exist
//  - Test normal cases


class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> index = {-1, -1};
        
        if (nums.empty()) return index;
        
        int startIdx = 0;
        int endIdx = nums.size() - 1; // zero-based indexing
        
        index[0] = binarySearch(nums, startIdx, endIdx, target, true);
        if (index[0] != -1) 
        {
            index[1] = binarySearch(nums, index[0], endIdx, target, false);
        }

        return index; 
    }
    
    int binarySearch(vector<int>& nums, int left, int right, int target, bool first)
    {
        if (nums.empty() || left > right) return -1;
        
        // Note that if using left < right, it will get stuck when the remaining two elements equal to target.
        while(left < right - 1) 
        {
            int mid = left + (right - left)/2;
            if (target == nums[mid]) 
            {   
                if (first) right = mid; 
                else left = mid;
            }
            else if (target < nums[mid]) right = mid - 1;
            else left = mid + 1;
        }
        
        // Left == right - 1 after while loop. Need to check the remaining two elements
        if (first)
        {
            if (target == nums[left]) return left;
            else if (target == nums[right]) return right;
            else return -1;
        }
        else
        {
            if (target == nums[right]) return right;
            else if (target == nums[left]) return left;
            else return -1;
        }
        
    }
    
//     int findFirst(vector<int>& nums, int left, int right, int target)
//     {
//         if (nums.empty() || left > right) return -1;
        
//         while(left < right)
//         {
//             int mid = left + (right - left)/2;
//             if (target == nums[mid]) right = mid;
//             else if (target < nums[mid]) right = mid - 1;
//             else left = mid + 1;
//         }
        
//         // Left == right after while loop. Need to check the remaining one
//         if (target == nums[left]) return left;
//         else return -1;
//     }
    
//     int findLast(vector<int>& nums, int left, int right, int target)
//     {
//         if (nums.empty() || left > right) return -1;
        
//         // Note that if using left < right, it will get stuck when the remaining two elements equal to target.
//         while(left < right - 1) 
//         {
//             int mid = left + (right - left)/2;
//             if (target == nums[mid]) left = mid;
//             else if (target < nums[mid]) right = mid - 1;
//             else left = mid + 1;
//         }
        
//         // Left == right - 1 after while loop. Need to check the remaining two elements
//         if (target == nums[right]) return right;
//         else if (target == nums[left]) return left;
//         else return -1;
//     }
};