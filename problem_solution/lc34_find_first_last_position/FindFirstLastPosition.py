class FindFirstLastPosition:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        ans = [-1, -1]
        
        if not nums:
            return ans;
        
        ans[0] = self.binary_search_first(nums, target)
        if ans[0] == -1:
            return ans
        ans[1] = self.binary_search_last(nums, target, ans[0])
        
        return ans
        
    def binary_search_first(self, nums: List[int], target: int) -> List[int]:
        left, right = 0, len(nums) - 1
        
        while left < right - 1:
            mid = left + (right - left)//2
            if target < nums[mid]:
                right = mid - 1
            elif target > nums[mid]:
                left = mid + 1
            else: # equal case
                right = mid  # not stop, continue to search left for the first position 
            
        # postprocessing of remainting two elements
        if nums[left] == target:
            return left
        elif nums[right] == target:
            return right
        else:
            return -1
        
    def binary_search_last(self, nums: List[int], target: int, start: int = 0) -> List[int]:
        left, right = start, len(nums) - 1

        while left < right - 1:
            mid = left + (right - left)//2
            if target < nums[mid]:
                right = mid - 1
            elif target > nums[mid]:
                left = mid + 1
            else: # equal case
                left = mid;  # not stop, continue to search right for the last position 

        # postprocessing of remainting two elements
        if nums[right] == target:
            return right
        elif nums[left] == target:
            return left
        else:
            return -1