class SearchRotatedArray:
    def search(self, nums: List[int], target: int) -> int:
        if not nums:
            return -1
        
        left = 0
        right = len(nums) - 1
        
        while (left <= right):
            mid = left + (right - left)//2
            
            if nums[mid] == target:
                return mid
            # elif nums[mid] == nums[left]: # mid == left, 
            #     left = mid + 1
            # elif nums[mid] == nums[right]: # mid == right, 
            #     right = mid - 1
            elif nums[mid] >= nums[left]:
                if target >= nums[left] and target < nums[mid]:
                    right = mid - 1
                else:
                    left = mid + 1
            else:
                if target > nums[mid] and target <= nums[right]:
                    left = mid + 1
                else:
                    right = mid - 1
        return -1