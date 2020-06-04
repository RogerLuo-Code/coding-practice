class FindKClosest:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Input check
        if not arr:
            return [] 
        if k <= 0 or k > len(arr):
            return []
        
        left, right = 0, len(arr) - k
        while left < right:
            mid = left + (right - left)//2
            if x - arr[mid] > arr[mid + k] - x:
                left = mid + 1
            else:
                right = mid
        return arr[left:left + k]