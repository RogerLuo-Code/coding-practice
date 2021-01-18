// Clarification: 
//  - two sorted array --> one sorted array
//  - assume two arrays are sorteed in the ascending order
// Solution:
//  - fill arrays from the right to left
//  - similar to the merge action in the merge sort (differences: no need to create a new array; move from right to left)

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1; // pointer for nums 1, scan from right to left
        int j = n - 1; // pointer for nums 2, scan from right to left
        int k = m + n - 1; // poionter for temp array
        
        //    0  1  2  3  4  5
        //   [1, 2, 2, 3, 5, 6]
        //    i/k 
        //   [2, 5, 6]
        //  j
        
        while (k >= 0) {
            if (i < 0) {
                nums1[k--] = nums2[j--];
            }
            else if (j < 0) {
                nums1[k--] = nums1[i--];
            }
            else if (nums1[i] >= nums2[j]) {
                nums1[k--] = nums1[i--];
            }
            else {
                nums1[k--] = nums2[j--];
            }
        }        
    }

};