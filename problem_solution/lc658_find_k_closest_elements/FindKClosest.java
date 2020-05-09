// Clarification
//  - sorted or unsorted
//  - k < arr.length 
//  - result sorted in ascending order or based on distance from x
//  - deal with tie case? return smaller elements
// Go through examples
// Solution
//  - Assumption: k <= arr.length
//  - Input/Output: input: array, int, int, output: array list
//  - Corner case: empty array, invalid k
//  - ALgorithm: binary search of slide window
//  - Time/space complexity
// Coding
//
class FindKCloest {
    public List<Integer> findClosestElements(int[] arr, int k, int x) {
        List<Integer> result = new ArrayList<Integer>();
        
        if (arr == null || arr.length == 0)
            return result; // return array
        
        // Corner cases for k
        // could return all elements if k > arr.length
        if (k <= 0 || k > arr.length)
            return result; // return new int[0]

        // binary search first
        // then find closest elements from target to left and to right

        int idxLeft = binarySearch(arr, x); // index for the left half, left closet element or equal element
        int idxRight = idxLeft + 1; // index for the right half

        for (int count = 0; count < k; count++){
            if (idxRight >= arr.length  || (idxLeft >= 0 && Math.abs(arr[idxLeft] - x) <= Math.abs(arr[idxRight] - x)))
                idxLeft--;
            else
                idxRight++;
        }

        for (int idx = idxLeft+1; idx < idxRight; idx++)
            result.add(arr[idx]);

        return result;
    }
    
    private int binarySearch(int[] arr, int target){
        // return index of the left closest element to the target
        int left = 0;
        int right = arr.length - 1;
        int middle;

        while (left < right - 1){
            middle = left + (right - left)/2;
            if (target < arr[middle])
                right = middle;
            else if (target > arr[middle])
                left = middle;
            else // target == arr[middle]
                return middle;
        }
        
        // No need postprocessing, just return the left element
        return left;
    }
}