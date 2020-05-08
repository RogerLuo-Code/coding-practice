// Clarification:
//  - sorted or unsorted? How are characters sorted? based on ASCII number?
//  - the first element on the right of the target?
//  - how warp around work?
//  - how large is the number of letters?
//  - only lower case?
//  - any duplicates?
// Go through examples
// Solution:
//  - assumption: sorted by ASCII number and use built-in comparion for characters
//  - Input/Output: input with char array and char scalar, output is char scalar
//  - Corner case: empty letters
//  - Time/space complexity:
// Coding
// Test case
//   - Test corner case: zero, 1, 2, 3 elements, wrap around
//   - Test general case:
public class FindSmallestLetterGreaterThanTarget {
    public char nextGreatestLetter(char[] letters, char target) {
        if (letters == null || letters.length == 0)
            return ' ';
        
        int left = 0;
        int right = letters.length - 1;
        int mid; 
        
        while (left < right) {
            mid = left + (right - left)/2;
            
            if (target < letters[mid])
                right = mid; // using mid not mid - 1, since mid could be the result (the first element on the right of the target)
            // else if (target > letters[mid])
            //     left = mid + 1;
            else // target == letters[mid]
                left = mid + 1;
        }
        
        // Post-process the remaining 1 element (left == right)
        // considering the wrap around case 
        // if (target >= letters[left])
        //     return letters[0];
        // else
        //     return letters[left];
        return letters[left] <= target ? letters[0] : letters[left];
    }
}