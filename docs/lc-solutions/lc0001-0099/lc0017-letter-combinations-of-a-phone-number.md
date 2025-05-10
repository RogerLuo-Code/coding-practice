---
tags:
    - Backtracking
---

# 17. Letter Combinations of a Phone Number

## Problem Description

[LeetCode Problem 17](https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/):
Given a string containing digits from 2-9 inclusive, return all possible letter
combinations that the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below.
Note that 1 does not map to any letters.

## Clarification

- Input is digit string 2 - 9 (no 0 and 1)
- Return letter combinations in any order
- Only 1 letter from each digit? Yes
- Does digits order matter?

## Assumption

-

## Solution

### Approach 1: Backtracking

We can build combinations one **digit at a time** and explore all possible paths by:

- choosing a letter from all possible letters under a digit
- recursively proceed to the next digit
- Repeat until a full-length combinations is formed.
- Backtracking by removing the last letter and trying the next one.

=== "Python"
    ```python
    class Solution:
        def __init__(self):
            self.DIGIT_TO_LETTERS = {
                "2": "abc",
                "3": "def",
                "4": "ghi",
                "5": "jkl",
                "6": "mno",
                "7": "pqrs",
                "8": "tuv",
                "9": "wxyz",
            }

        def letterCombinations(self, digits: str) -> List[str]:
            if not digits:
                return []
            self.results = []
            self._backtrack(digits, 0, "")
            return self.results

        def _backtrack(self, digits: str, index: int, curr: list[str]) -> None:
            # Base case
            if len(curr) == len(digits):
                self.results.append(curr)
                return

            if digits[index] in self.DIGIT_TO_LETTERS:
                possible_letters = self.DIGIT_TO_LETTERS[digits[index]]
                for letter in possible_letters:
                    self._backtrack(digits, index + 1, curr + letter)  # (1)
    ```

    1. Implicit backtrack since string is not immutable, which is equivalent to the
    following if using `curr` list
    ```
    curr.append(letter)
    self._backtrack(digits, index + 1, curr)
    curr.pop()
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(k^n \cdot n)$ where $n$ is the number of digits in the input and
$k$ is the maximum number of letters mapped to a digit (the max is 4 for digit `7` and
`9`)
    - For $n$ digits, the total number of combinations is $k^n$.
    - For each combination, it takes $O(n)$ time to build the string (one letter per digit).
    - So the total time complexity is $O(k^n \cdot n)$.
- Space complexity: $O(k^n \cdot n)$
    - The recursive call stack takes $O(n)$ space since the depth of recursion is $n$.
    - Since return all combinations, the output list has $O(k^n)$ string and each string
    has length $n$, which takes $O(k^n \cdot n)$ space.
    - So the total space complexity is $O(k^n \cdot n) + O(n) = O(k^n \cdot n)$.

### Approach 2: 

Solution

=== "python"
    ```python
    code
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(1)$  
  Explanation
- Space complexity: $O(n)$  
  Explanation

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - | $O(1)$          | $O(n)$
Approach - | $O(1)$          | $O(n)$

## Test

- Test empty digits
- Test one digit
- Test multiple digits
- Test multiple digits with duplicates
