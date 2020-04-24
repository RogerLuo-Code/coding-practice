public class Smallest {
    private Smallest() { }

    public static int binarySearch(int[] a, int target) {
        // find the smallest element that is larger than a target number
        // 3 cases: small, equal, bigger [sssss eeee Bbbbbbb]
        // try to the find the first B
        
        // Clarification: 
        //  - sorted array?
        //  - duplicates?
        //  - data type

        int left = 0;
        int right = a.length - 1; 
        if (right < 0)
            return -1;
        int middle;

        while (left < right - 1) {
            middle = left + (right - left)/2;
            if (target < a[middle])
                right = middle;  // middle - 1 may rule out the final result
            else if (target > a[middle])
                left = middle + 1;
            else // target == a[middle]
                left = middle + 1; // move to the right of target, finding the the first element that is larger than target
        }

        // postprocessing
        if (a[left] > target)
            return left;
        else if (a[right] > target)
            return right;
        else 
            return -1;


    }

    public static void main(String[] args) {
        int[] a = {1, 2, 3, 5, 7};
        int target = 8;
        int result; 

        result = Smallest.binarySearch(a, target);
        System.out.println(result);

    }
}