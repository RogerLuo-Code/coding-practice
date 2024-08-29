---
tags:
    - Stack
---

# LC20. Valid Parentheses
## Problem Description
[LeetCode Problem 20](https://leetcode.com/problems/valid-parentheses/): Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

An input string is valid if:

1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.
3. Every close bracket has a corresponding open bracket of the same type.

## Clarification
- string only contains brackets
- string can starts with multiple open brackets, for example, '([{()}])', but need to close in the correct order
- Every close bracket has a open bracket
- What about empty string?

## Assumption

## Solution
### Approach - Stack
Use stack to store open brackets. When encounter close brackets, pop up open bracket and check whether they are valid parentheses. The stack should be empty at the end.

=== "Python"
    ```python
    from collections import deque

    class Solution:
        PARENTHESE_MAP = {")": "(", "}": "{", "]": "["}

        def isValid(self, s: str) -> bool:
            if not s or len(s) % 2 == 1:
                return False

            stack = deque()
            for letter in s:
                # If the letter is an closing bracket
                if letter in self.PARENTHESE_MAP:
                    if stack:
                        last_open_bracket = stack.pop()
                    else:
                        return False
                    if last_open_bracket != self.PARENTHESE_MAP[letter]:
                        return False
                else:
                    stack.append(letter)

            return not stack
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Traverse the given string one character at a time for total $n$ characters and push and pop operation on a stack take $O(1)$ time.
* Space complexity: $O(n)$  
	In the worst case, push all $n$ brackets.

## Test