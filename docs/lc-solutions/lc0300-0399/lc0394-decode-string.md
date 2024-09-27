---
tags:
    - Stack
---

# LC394. Decode String

## Problem Description

[LeetCode Problem 394](https://leetcode.com/problems/decode-string/): Given an encoded string, return its decoded string.

The encoding rule is: `k[encoded_string]`, where the `encoded_string` inside the square brackets is being repeated exactly `k` times. Note that `k` is guaranteed to be a positive integer.

You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, `k`. For example, there will not be input like `3a` or `2[4]`.

The test cases are generated so that the length of the output will never exceed `105`.

## Clarification

- Go through encoded rule
- Always have a valid input?
- Only contains english letters, digits, and square brackets `[]`?
- So no `3a`. Instead, `3[a]`

## Assumption

-

## Solution

### Approach - Stack

Uses a stack to handle nested patterns in the encoded string. It loops through the characters of the string,

- when encountering open bracket `[`, push the current string and number onto the stack.
- when encountering a closing bracket `]`, it pops the stack to retrieve the previous string and repeats the current string according to the last number, then concatenates it.
- digits are processed to form numbers.
- regular characters are appended directly to the current string.

=== "Python"
    ```python
    class Solution:
    def decodeString(self, s: str) -> str:
        stack = deque()
        curr_string = ""
        curr_num = 0

        for c in s:
            if c == "[":
                stack.append(curr_string)
                stack.append(curr_num)
                curr_string = ""
                curr_num = 0
            elif c == "]":
                num = stack.pop()
                prev_string = stack.pop()
                curr_string = prev_string + curr_string * num
            elif c.isdigit():
                curr_num = curr_num * 10 + int(c)
            else:
                curr_string += c
        return curr_string
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  The algorithm processes each character in the input string exactly once, when $n$ is the length of the input string. For stack pushing and pop, the time complexity is $O(1)$. For string concatenation, it concatenates at most $n$ letters, so the time complexity is within $O(n)$.
- Space complexity: $O(m)$, where $m$ is the size of the expanded string, which can be larger than $n$ if there are many repeated segments.


## Test
