// Clarification:
//  - sorted characters based on what rule? ASCII? 
//  - include uppercase letters?
//  - what does it mean smallest element but larger than the given target
//  - wrap up?
//  - array length?
// Go through examples
//  
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        if (letters.empty()) return '\0';
        
        int left = 0;
        int right = letters.size() - 1;
        int mid; 
        
        while (left < right)
        {
            mid = left + (right - left)/2;
            
            if (target < letters[mid]) right = mid; // not mid - 1, which may skip the answer (e.g., [..., target, mid])
            else left = mid + 1;
        }
        
        // left == right after while loop
        return (letters[left] <= target) ? letters[0] : letters[left];
        // if (letters[left] > target) return letters[left];
        // else return letters[0];
    }
};