// Clarification: 
//  - two sorted arrays
//  - median definition
//  - size of array are not equal and range (could be null)
//  - both null? No, m+n >= 1
//  - return values of corner cases? Nan?
// Go through examples
// Solutions:
//  - Input/Output: vector<int>&, vector<int>&; double
//  - Assumption: at least one array is not empty
//  - Algorithm: from median defintion to find partition, using binary search
// Coding


class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.empty() && nums2.empty())
        {
            return numeric_limits<double>::quiet_NaN();
        }
        
        if (nums1.size() > nums2.size())
        {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int m = nums1.size();
        int n = nums2.size(); 
        
        int left = 0;
        int right = m; // not m-1, since this is partition position, can be 0 ~ m (inclusive)
        
        int i; // partition position for array nums 1
        int j; // partition position for array nums 2
        
        while (left <= right)
        {
            i = left + (right - left)/2; 
            j = (m + n + 1)/2 - i;  //m+n+1 is the index of median
            
            // Handle edge cases: i == 0 or m or j == 0 or n
            int maxLeft1 = (i == 0) ? numeric_limits<int>::min() : nums1[i-1];
            int maxLeft2 = (j == 0) ? numeric_limits<int>::min() : nums2[j-1];
            int minRight1 = (i == m) ? numeric_limits<int>::max() : nums1[i];
            int minRight2 = (j == n) ? numeric_limits<int>::max() : nums2[j];
            
            // Compare and update partitions
            if (maxLeft1 > minRight2)
            {
                right = i - 1;
            }
            else if (maxLeft2 > minRight1)
            {
                left = i + 1;
            }
            else
            {
                if ((m + n)%2 == 0)
                {
                    return ((double)(max(maxLeft1, maxLeft2) + min(minRight1, minRight2)))/2;
                }
                else
                {
                    return (double)max(maxLeft1, maxLeft2);
                }
            }
        }
        return numeric_limits<double>::quiet_NaN();
    }
};