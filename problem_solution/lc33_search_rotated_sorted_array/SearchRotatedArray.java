class SearchRotatedArray {
    public int search2(int[] nums, int target) {
        if (nums == null || nums.length == 0)
            return -1;
        
        int left = 0;
        int right = nums.length - 1; // -1 for zero-based indexing
        int mid; 
        
        while (left <= right) {
            mid = left + (right - left)/2;
            
            if (target == nums[mid])
                return mid;
            else if (nums[mid] >= nums[left]) { // must be >=; pivot point on the right
                if (target >= nums[left] && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            } 
            else { // pivot point on the right
                if (target > nums[mid] && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        
        return -1;
    }

    public int search1(int[] nums, int target) {
        if (nums == null || nums.length == 0)
            return -1;
        
        int pivotIdx = findRotateIndex(nums);
        
        if (target >= nums[0] &&  target <= nums[pivotIdx])
            return binarySearch(nums, 0, pivotIdx, target);
        else
            return binarySearch(nums, pivotIdx + 1, nums.length - 1, target);
    }
    
    public int findRotateIndex(int[] nums) {
        int left = 0; 
        int right = nums.length - 1; // -1 for zero-based indexing
        int mid; 
        
        while (left <= right) {
            mid = left + (right - left)/2;
            
            if (mid + 1 < nums.length && nums[mid] > nums[mid + 1]) {
                return mid; // find the pivot at mid
            }
            else if (nums[mid] >= nums[left]) 
                left = mid + 1;
            else 
                right = mid - 1;
        }
        return 0;
    }
    
    public int binarySearch(int[] nums, int left, int right, int target) {
        int mid;
        
        while (left <= right) {
            mid = left + (right - left)/2;
            
            if (target == nums[mid])
                return mid;
            else if (target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }
        
        return -1;
    }

}