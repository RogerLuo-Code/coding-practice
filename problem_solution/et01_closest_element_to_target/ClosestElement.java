public class ClosestElement{
    private CloestElement(){}

    public static int binarySearch(int[] array, int target){
        if (array == null || array.length == 0)
            return -1;
        
        int left = 0;
        int right = array.length - 1; // -1 for zero-based indexing
        int middle;

        while (left < right - 1){ // stop at left == right - 1, two elements left
            middle = left + (right - left)/2;
            if (target < array[middle])
                right = middle; // middle -1 may rule out the final result
            else if (target > array[middle])
                left = middle; // middle +1 may rule out the final result
            else
                return middle; 
        }

        // Two elements left and compare them
        if (Math.abs(array[left] - target) <= Math.abs(array[right] - target))
            return left;
        else
            return right;
    }

    public static void main(String[] args){
        // int[] array = {-5, 1, 3, 9, 10, 25, 100};
        int[] array =  {};
        int target = 101;
        int index; 
        
        index = ClosestElement.binarySearch(array, target);

        System.out.println(index);
    }
}