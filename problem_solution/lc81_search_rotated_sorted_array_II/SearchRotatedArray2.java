// Clarification: 
//  - sorted
//  - ascedning order
//  - rotated at one pivot point
//  - contain duplicates
//  - return value (true or false) for duplicates
// Go through examples
// Solution:
//  - Assumption: one pivot point
//  - Input/output: int array, int; boolean
//  - Algorithm: binary search 
//  - Time/space complexity
// Coding
// Test Cases
class SearchRotatedArray2 {
    public boolean search(int[] nums, int target) {
        if (nums == null || nums.length == 0)
            return false;
        
        int left = 0;
        int right = nums.length - 1;
        int mid;
        
       // [s s s s s e e e e b b b s s s s]
       //                ^ 
        while (left <= right) {
            mid = left + (right - left)/2;
            
            if (target == nums[mid])
                return true;
            else if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
                left++;
                right--;
            } 
            else if (nums[mid] >= nums[left]) { // sorted subarray from left to mid
                if (target >= nums[left] && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else { // sorted subarray from mid to right
                if (target > nums[mid] && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        return false;
    }
}