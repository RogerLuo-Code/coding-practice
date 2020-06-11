public class KthSmallest {
    private KthSmallest() { }

    public int kthRecursive(int[] a, int aLeft, int[] b, int bLeft, int k) {
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
        int aMid = aLeft + k / 2 - 1;
        int bMid = bLeft + k / 2 - 1;

        // Special case:
        // if a.size too small, use the max value of integer, and vice versa.
        int aVal = aMid >= a.length ? Integer.MAX_VALUE : a[aMid];
        int bVal = bMid >= b.length ? Integer.MAX_VALUE : b[bMid];

        // Comparison: <= vs. <
        // when encountering duplicates, remove a's elments first if using <=
        if (aVal <= bVal)
            return kthRecursive(a, aMid + 1, b, bLeft, k - k / 2);
        else
            return kthRecursive(a, aLeft, b, bMid + 1, k - k / 2);
    }

    public int kthIterative(int[] a, int[] b, int k) {
        int aLeft = 0;
        int bLeft = 0;
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
 }

    public static void main(String[] args) {
        KthSmallest kth = new KthSmallest();   
        int[] a = {1, 3, 15};
        int[] b = {2, 4, 6, 8, 10, 12, 14, 16};
        int k = 10;
        int kthSmallVal;

        kthSmallVal = kth.kthRecursive(a, 0, b, 0, k);
        System.out.println(kthSmallVal);    

        kthSmallVal = kth.kthIterative(a, b, k);
        System.out.println(kthSmallVal);
    }

}