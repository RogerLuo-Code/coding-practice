public class ClosestElement{
    private CloestElement(){}

    public static int binarySearch(int[] a, int target){
        int left = 0;
        int right = a.length - 1; // -1 for zero-based indexing
        if (right < 0)
            return -1;
        int middle;

        while (left < right - 1){ // stop at left == right - 1, two elements left
            middle = left + (right - left)/2;
            if (target < a[middle])
                right = middle; // middle -1 may rule out the final result
            else if (target > a[middle])
                left = middle; // middle +1 may rule out the final result
            else
                return middle; 
        }

        // Two elements left and compare them
        if (Math.abs(a[left] - target) <= Math.abs(a[right] - target))
            return left;
        else
            return right;
    }

    public static void main(String[] args){
        // int[] a = {-5, 1, 3, 9, 10, 25, 100};
        int[] a =  {};
        int target = 101;
        int index; 
        
        index = ClosestElement.binarySearch(a, target);

        System.out.println(index);
    }
}