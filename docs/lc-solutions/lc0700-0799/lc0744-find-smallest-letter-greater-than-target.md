---
tags:
    - Binary Search
---

# LC744. Find Smallest Letter Greater Than Target
## Problem Description
[LeetCode Problem 744](https://leetcode.com/problems/find-smallest-letter-greater-than-target/description/?envType=study-plan-v2&envId=binary-search): You are given an array of characters `letters` that is sorted in **non-decreasing order**, and a character `target`. There are **at least two different** characters in `letters`.

Return _the smallest character in_ `letters` _that is lexicographically greater than_ `target`. If such a character does not exist, return the first character in `letters`.

## Clarification
- array of letters
- non-decreasing order
- capital or small letters and how to determin orders between capital and small ones
- definition of lexicographically?
- return letter or index

## Assumption
- letters and target are the same case (either uppercase or lowercase)

## Solution
### Approach - Binary Search
Since letters are sorted, we can use binary search to find the smallest letter that is greater than target.

=== "Python"
    ```python
    class Solution:
        def nextGreatestLetter(self, letters: List[str], target: str) -> str:
            left, right = 0, len(letters) - 1

            while left < right:
                mid = (left + right) // 2
                if target >= letters[mid]:
                    left = mid + 1
                else:
                    right = mid

            if letters[left] <= target:
                return letters[0]
            else:
                return letters[left]
    ```

=== "C++"
    ```c++
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

                if (target < letters[mid]) right = mid;
                else left = mid + 1;
            }

            // left == right after while loop
            return (letters[left] <= target) ? letters[0] : letters[left];
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(\log n)$  
	Since using the binary search, the time complexity is $O(\log n)$.
* Space complexity: $O(1)$  
	Use 3 variables for binary search.