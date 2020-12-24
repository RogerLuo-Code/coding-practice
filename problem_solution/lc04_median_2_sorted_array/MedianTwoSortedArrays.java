/**
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 * Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 *
 * Solution 1
 * Take minimum size of two array. Possible number of partitions are from 0 to m in m size array.
 * Try every cut in binary search way. When you cut first array at i then you cut second array at (m + n + 1)/2 - i
 * Now try to find the i where a[i-1] <= b[j] and b[j-1] <= a[i]. So this i is partition around which lies the median.
 *
 * Time complexity is O(log(min(x,y))
 * Space complexity is O(1)
 * 
 * Solution 2
 * Convert the problem to find k-th smallest elements of two sorted array
 */

public class MedianTwoSortedArrays {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        if ((nums1 == null || nums1.length == 0) && (nums2 == null || nums2.length == 0))
            return Double.NaN;
        
        // If num1 lenght is greater, then switch them so that the num1 is smaller
        if (nums1.length > nums2.length)
            return findMedianSortedArrays(nums2, nums1);
        
        int m = nums1.length;
        int n = nums2.length;
        
        int left = 0;
        int right = m; // not m - 1, since this is partition position, which can be 0 ~ m (inclusive)
        int i; // partition position for array nums 1 
        int j; // partition position for array nums 2
        
        // Binary search of partition position
        while (left <= right) {
            i = left + (right - left)/2;
            j = (m + n + 1)/2 - i; // (m + n + 1)/2 is the index of median
            
            // Handle corner cases: i == 0 or m
            int maxLeft1 = i == 0 ? Integer.MIN_VALUE : nums1[i - 1];
            int maxLeft2 = j == 0 ? Integer.MIN_VALUE : nums2[j - 1];
            
            // Handle corner cases: j == 0 or n
            int minLeft1 = i == m ? Integer.MAX_VALUE : nums1[i];
            int minLeft2 = j == n ? Integer.MAX_VALUE : nums2[j];
            
            if (maxLeft1 > minLeft2) // too far on right side of parittion i
                right = i - 1;
            else if (maxLeft2 > minLeft1) // too far on left side of partition i
                left = i + 1;
            else  { // found: nums1[i - 1] <= nums2[j], nums2[i - 1] <= nums1[i]
                if ((m + n)%2 == 0) // even number
                    return (double) (Math.max(maxLeft1, maxLeft2) + Math.min(minLeft1, minLeft2))/2;
                else
                    return (double) Math.max(maxLeft1, maxLeft2);
            }
        }
        
        // Only come here if input arrays were not sorted
        return Double.NaN;
    }

    public double findMedianSortedArrays2(int[] nums1, int[] nums2) {
        if ((nums1 == null || nums1.length == 0) && (nums2 == null || nums2.length == 0))
            return Double.NaN;
        
        int m = nums1.length; 
        int n = nums2.length;
        int k = (m + n + 1)/2;
        
        if ((m + n) % 2 == 0) {
            int x = findKthSmallestElement(nums1, 0, nums2, 0, k);
            int y = findKthSmallestElement(nums1, 0, nums2, 0, k + 1);
            return ((double) findKthSmallestElement(nums1, 0, nums2, 0, k) + (double) findKthSmallestElement(nums1, 0, nums2, 0, k + 1))/2;
        }
        else
            return (double) findKthSmallestElement(nums1, 0, nums2, 0, k);
    }
    
    private int findKthSmallestElement(int[] a, int aLeft, int[] b, int bLeft, int k) {
        int aMid;
        int bMid;
        int aVal;
        int bVal;

        while (k >= 1) {
            if (aLeft >= a.length)
                return b[bLeft + k - 1];
            if (bLeft >= b.length)
                return a[aLeft + k - 1];
            if (k == 1)
                return Math.min(a[aLeft], b[bLeft]);


            aMid = aLeft + k / 2 - 1;
            bMid = bLeft + k / 2 - 1;
        
            aVal = aMid >= a.length ? Integer.MAX_VALUE : a[aMid];
            bVal = bMid >= b.length ? Integer.MAX_VALUE : b[bMid];

            if (aVal <= bVal) 
                aLeft = aMid + 1;
            else
                bLeft = bMid + 1; 

            k = k - k / 2; // reduce searching space
        }
        
        return 0;
        
    }


    public static void main(String[] args) {
        int[] x = {1, 3, 5};
        int[] y = {2, 4, 6, 8, 10};

        MedianTwoSortedArrays m = new MedianTwoSortedArrays();
        double result = m.findMedianSortedArrays(x, y);
        System.out.println(result);
    }
}