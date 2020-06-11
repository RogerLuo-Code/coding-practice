class BinarySearch {
    public int search(int[] nums, int target) {
        if (nums == null || nums.length == 0)
            return - 1;
        
        int left = 0;
        int right = nums.length - 1; // -1 for zero-based indexing
        int mid;
        
        while (left <= right) {
            mid = left + (right - left)/2;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] > target)
                right = mid - 1;
            else
                left = mid + 1;
        }
        
        // not find target
        return -1;
    }
}