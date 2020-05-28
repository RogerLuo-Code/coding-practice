public class KthSmallest {
    private KthSmallest() { }

    public static int kthRecursive(int[] a, int aLeft, int[] b, int bLeft, int k) {
        // aLeft and bLeft are pointers, pointing to the index whose left elments are excluded 
        // k, number of elements left to search for k-th smallest, reduced by half each iteration
        
        // Base case
        if (aLeft >= a.length) {
            return b[bLeft + k - 1];
        }
        if (bLeft >= b.length) {
            return a[aLeft + k - 1];
        } 
        if (k == 1){
            return Math.min(a[aLeft], b[bLeft]);
        }
        
        // index starts from left
        // the k/2-th element should be left + k/2 - 1
        int aMid = aLeft + k/2 - 1;
        int bMid = bLeft + k/2 - 1;

        // Special case:
        // if a.size too small, then remove elments from b first, and vice versa.
        int aVal = aMid >= a.length ? Integer.MAX_VALUE : a[aMid];
        int bVal = bMid >= b.length ? Integer.MAX_VALUE : b[bMid];

        // Comparison: <= vs. <
        // when encountering duplicates, prioritize a's elements 
        // (keep a's elements and remove b's first)
        if (aVal <= bVal)
            return kth(a, aMid+1, b, bLeft, k - k/2);
        else
            return kth(a, aLeft, b, bMid+1, k - k/2);
    }

    public int kthtIterative(int[] nums1, int[] nums2, int k) {
        int n1 = nums1.length;
        int n2 = nums2.length;
        int i = 0; // starting index of nums1 array
        int j = 0; // starting index of nums2 array
          
        while (k > 1) {
            // Eliminate k elements based on comparison results
            if (i >= n1) { // finish searching all elments in nums1
                j = j + k - 1;
                return nums2[j];
            }
            else if (j >= n2) { // finish searching all elments in nums1
                i = i + k - 1;
                return nums1[i];
            }
            else if (i + k/2 - 1 >= n1) // not enough elements in nums1
                j = j + k/2;
            else if (j + k/2 - 1 >= n2) // not enought elements in nums2
                i = i + k/2;
            else if (nums1[i + k/2 - 1] <= nums2[j + k/2 - 1])
                i = i + k/2;
            else
                j = j + k/2;
            
            k = k - k/2; // update k to search in next iteration
        }

        // k == 1 
        return Math.min(nums1[i], nums2[j]);
 }

    public static void main(String[] args) {
        int[] a = {1, 3, 15};
        int[] b = {2, 4, 6, 8, 10, 12, 14, 16};
        int k = 10;
        int kthSamllVal;

        kthSamllVal = KthSmallest.kthRecursive(a, 0, b, 0, k);

        System.out.println(kthSamllVal);    
    }

}