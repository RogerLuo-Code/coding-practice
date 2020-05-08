class FindSmallestLetterGreaterThanTarget:
    def nextGreatestLetter(self, letters: List[str], target: str) -> str:
        if not letters:
            return ' '
        
        # Wrap around case
        if target >= letters[-1]:
            return letters[0]
        
        
        left, right = 0, len(letters) - 1
        
        # Binary search below
        while left < right:
            mid = left + (right - left)//2
            
            if target < letters[mid]:
                right = mid  # mid - 1 may accidently exclude the result (the one larger than target and the first one)
            # elif target > letters[mid]: 
            #     left = mid + 1
            else:
                left = mid + 1 # not stop and continue to search
        
        # No post-processing needed (left == right) 
        # wrap around case is handled at the beginning
        return letters[left]