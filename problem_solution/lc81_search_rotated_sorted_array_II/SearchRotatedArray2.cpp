// Clarification:
//  - integer array, 
//  - original array is sorted in ascending order
//  - no duplicates
//  - rotated at some pivot point
// Solution:
//  - Brutal force: compare individual element until find the target
//  - [4, 5, 6, 7, 0, 1, 2] the array can be divided into two halves, one is sorted and the other is unsorted with pivot point
//  - If target is in the sorted array, we can use binary search for that half. Otherwise, we search unsorted part and further break it down into two halves (again, one half will be sorted and the other will be unsorted)

// 1 target == nums[mid], then we find it;
// 2 nums[left] < nums[mid], then the left part must be sorted;
// 3 nums[left] > nums[mid], then the right part must be sorted;
// 4 nums[left] == nums[mid], we can not make sure which part is sorted, the only thing we can do is scale in the problem size. Since target != nums[mid] == nums[left], we just offset right by left++.



class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if (nums.empty()) return false;
        
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        
        while (left <= right) {
            mid = left + (right - left)/2;
            
            if (target == nums[mid]) {
                return true;
            }
            else if (nums[left] < nums[mid]) {
                // [left, mid] is sorted
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            else if (nums[left] == nums[mid]) {
                left++;
            }
            else {
                // [mid, right] is sorted
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
        }
        
        return false;
    }
};