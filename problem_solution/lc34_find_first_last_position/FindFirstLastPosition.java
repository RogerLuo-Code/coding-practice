public class FindFirstLastPosition {
    private FindFirstLastPosition() { }

    public static int binarySearchFirst(int[] a, int target) {
        // find the first occurrence of an element
        int left = 0;
        int right = a.length - 1;
        if (right < 0)
            return -1;
        int middle;

        while (left < right - 1) { // end at left == right -1, two elements left
            middle = left + (right - left)/2;

            if (target < a[middle])
                right = middle - 1;
            else if (target > a[middle])
                left =  middle + 1;
            else // target == a[middle]
                right = middle; // not stop here, keep checking to the left to find the first occurent, mmiddle -1 may rule out the final result
        }

        // postprocessing for two elements
        if (a[left] == target)
            return left;
        else if (a[right] == target)
            return right;
        else 
            return -1;
    }

    public static int binarySearchLast(int[] a, int target) {
        // find the last occurence of an element
        int left = 0;
        int right = a.length - 1;
        if (right < 0)
            return -1;
        int middle;

        while (left < right - 1) {
            middle = left + (right - left)/2;

            if (target < a[middle])
                right = middle - 1;
            else if (target > a[middle])
                left = middle + 1;
            else // target == a[middle]
                left = middle; // not stop here, keep checking  to the right to find the last occurrenct, middle + 1 may rule out the final result
        }

        // Postprocessing the two elements
        if (a[right] == target)
            return right; 
        else if (a[left] == target)
            return left;
        else 
            return -1;
    }

    public static void main(String[] args) {
        int[] a = {-1, -1, 1, 2, 3, 3, 3, 5}; 
        // int[] a = {};
        int target = 3; // -5, -1, 3, 5, 8
        int indexFirst; 
        int indexLast;
        indexFirst = FirstOrLastOccurrence.binarySearchFirst(a, target);
        indexLast  = FirstOrLastOccurrence.binarySearchLast(a, target);
        //System.out.println(index);
        System.out.format("Target: %d, the first occurrence: %d, the last occurence: %d \n", target, indexFirst, indexLast);
    }
}