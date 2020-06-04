public class MedianTwoSortedArrays {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        if ((nums1 == null || nums1.length == 0) && (nums2 == null || nums2.length == 0))
            return Double.NaN;
        
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
            
            // handle edeg cases:
            int maxLeft1 = i == 0 ? Integer.MIN_VALUE : nums1[i - 1];
            int maxLeft2 = j == 0 ? Integer.MIN_VALUE : nums2[j - 1];
            
            int minLeft1 = i == m ? Integer.MAX_VALUE : nums1[i];
            int minLeft2 = j == n ? Integer.MAX_VALUE : nums2[j];
            
            // Corner case: i == 0 or m, j == 0 or n
            if (maxLeft1 > minLeft2)
                right = i - 1;
            else if (maxLeft2 > minLeft1)
                left = i + 1;
            else  { // found: nums1[i - 1] <= nums2[j], nums2[i - 1] <= nums1[i]
                if ((m + n)%2 == 0) // even number
                    return (double) (Math.max(maxLeft1, maxLeft2) + Math.min(minLeft1, minLeft2))/2;
                else
                    return (double) Math.max(maxLeft1, maxLeft2);
            }
        }
        
        return Double.NaN;
    }

    public static void main(String[] args) {
        int[] x = {1, 3, 5};
        int[] y = {2, 4, 6, 8, 10};

        MedianTwoSortedArrays m = new MedianTwoSortedArrays();
        double result = m.findMedianSortedArrays(x, y);
        System.out.println(result);
    }
}