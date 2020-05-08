# LeetCode Problem 744 - Find Smallest Letter Greater Than Target 

## Problem Description
[LeetCode Problem 744:](https://leetcode.com/problems/find-smallest-letter-greater-than-target/) Given a list of sorted characters letters containing only lowercase letters, and given a target letter target, find the smallest element in the list that is larger than the given target.

Letters also wrap around. For example, if the target is target = 'z' and letters = ['a', 'b'], the answer is 'a'.

## Analysis 
* Clarifications
    - Sorted or unsorted?
    - Include both lower and upper case? 
    - How are letters sorted?   
        * Dictionary order: the upper case "A" sorts adjacent to lowercase "a"  
        * ASCII-code order: compare using ASCII codes. All uppercase come before lowercase letters; Digits and many punctuation marks come before letters.
    - How wrap around work?
    - Any duplicates? Impact the results?
    - Return type?
* Go through examples (understand better about wrap around)
* Solution:
    - assumption: sorted by ASCII number and use built-in comparion for characters
    - Input/Output: input with char array and char scalar, output is char scalar  
    - Corner case: empty letters
    - Time/space complexity:
* Coding
* Test case
    - Test corner case: zero, 1, 2, 3 elements, wrap around
    - Test general case:

## Approaches
* For **unsorted** letter array, scan through letters and record if seeing a letter or not.The data structure is array of size 26 or a set structure.
* For **sorted** letter array, using binary search is much better than linear scan from left to right. 
    - Case 1: `target < letters[mid]`,  need to update `right` with `mid` not `mid - 1`. Think about the case where target is just on the left of `letters[mid]`, `mid - 1` will accident exclude the final result
    - Case 2: `target > letters[mid]`, it is safe to update `left = mid + 1` and won't exclulde the final result 
    - Case 3: `target == letters[mid]`, do not stop here and continue to search the right to find the first one that is larger than target, so `left = mid + 1` 

```java
class Solution {
    public char nextGreatestLetter(char[] letters, char target) {
        if (letters == null || letters.length == 0)
            return ' ';

        int left = 0;
        int right = letters.length - 1; // -1 for zero-based indexing 
        int middle;
        
        while (left < right){
            middle = left + (right - left)/2;
            if (target < letters[middle])
                right = middle;  // middle - 1 may exclude the find result
            else // (target >= letters[middle])
                left = middle + 1;
        }
        
        // postprocess on the remaining one element (left == right), considering wrap around case       
        return letters[left] <= target ? letters[0] : letters[left];
    }
}
```

## Complexity Analysis
* **Time complexity**: $\mathcal{O}(\log N)$, where $N$ is the length of letters.   
We only peek at most $\log N$ elements in the array using binary search. 

* **Space complexity**: $\mathcal{O}(1)$ as only maintain indices. 