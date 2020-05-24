class SearchRotatedArray2:
    def search(self, nums: List[int], target: int) -> bool:
        if not nums:
            return False
        
        left = 0
        right = len(nums) - 1
        
        while (left <= right):
            mid = left + (right - left)//2
            if nums[mid] == target:
                return True
            elif nums[left] == nums[mid] and nums[mid] == nums[right]: # don't know which side to move, simply remove duplicates
                left, right = left + 1, right - 1
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
        return False    