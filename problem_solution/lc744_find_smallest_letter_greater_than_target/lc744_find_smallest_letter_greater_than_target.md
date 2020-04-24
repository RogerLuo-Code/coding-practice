# LeetCode Problem 744 - Find Smallest Letter Greater Than Target 

## Problem Description
[LeetCode Problem 744:](https://leetcode.com/problems/find-smallest-letter-greater-than-target/) Given a list of sorted characters letters containing only lowercase letters, and given a target letter target, find the smallest element in the list that is larger than the given target.

Letters also wrap around. For example, if the target is target = 'z' and letters = ['a', 'b'], the answer is 'a'.

## Clarifications
* Sorted or unsorted?
* What does sorted characters mean? a, b, ..., z?
* Only lowercase letters?
* Wrap around?
* What about duplicates?
* Return type?

## Approaches
* For **unsorted** letter array, scan through letters and record if seeing a letter or not.The data structure is array of size 26 or a set structure.
* For **sorted** letter array, using binary search is much better than linear scan from left to right. 

```java
class Solution {
    public char nextGreatestLetter(char[] letters, char target) {
        int left = 0;
        int right = letters.length - 1; // -1 for zero-based indexing 
        if (right < 0){
            return 0;  // or return null?
        }
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