// Clarification:
//  - original array is sorted in ascending order
//  - there is at most one pivot point (could be zero)
//  - minimum is at the pivot point (i.e, nums[p-1] > nums[p])
// Solution:
//  - find pivot point where the minimum value locates
//  - for any give index, the array is sperate into two halves, one is sorted, the other is not since contains pivot point. So we can reduce search space in the sorted region. 

//  - [3, 4, 5, 1, 2]
//              p
//        m

class Solution {
public:
    int findMin(vector<int>& nums) {
//         if (nums.empty()) {
//             return -1;
//         }
//         int n = nums.size();
//         int left = 0;
//         int right = n - 1;
//         int mid;
        
//         // The whole array is sorted and no pivot point
//         if (nums[right] >= nums[left]) {
//             return nums[left];
//         }
        
//         // [7 5]
//         // l/m r
//         // There is one pivot point
//         while (left <= right) {
//             mid = left + (right - left)/2;
            
//             if (((mid - 1) >= 0) && (nums[mid - 1] > nums[mid])) { 
//                 // Find the pivot point
//                 return nums[mid];
//             }
//             else if (((mid + 1) <= (n-1)) && (nums[mid] > nums[mid + 1])) {
//                 return nums[mid + 1];
//             }
//             else if (nums[mid] >= nums[left]) {
//                 left = mid + 1;
//             }
//             else {
//                 right = mid - 1;
//             }
//         }
        
//         return -1;
        
        // Simplified version:
        int left = 0; 
        int right = nums.size() - 1;
        int mid;
        //  0  1  2  3  4  5  6
        // [4, 5, 6, 7, 0, 1, 2]
        //  l        m        r
        //              l     r
            0  1  2  3  4  5  6
            l        m        r  
        
        while (left < right) {
            mid = left + (right - left)/2;
            
            
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        
        // Postprocessing
        return nums[left];
            
        
        // Another version
//         int left = 0;
//         int right = nums.size() - 1;
//         int mid;
        
//         // The whole array is sorted and no pivot point
//         if (nums[right] >= nums[left]) {
//             return nums[left];
//         }
        
//         //  0  1  2  3  4  5  6
//         // [4, 5, 6, 7, 0, 1, 2]
//         //  l        m        r   7 > 4
//         //           l  m      r   1 > 0 
        
//         while (left < right - 1) {
//             mid = left + (right - left)/2;
            
//             if (nums[mid] > nums[left]) {
//                 left = mid;
//             } 
//             else {
//                 right = mid;
//             }
//         }
        
//         // Postprocessing
//         return (nums[left] <= nums[right]) ? nums[left] : nums[right];    
    }
};