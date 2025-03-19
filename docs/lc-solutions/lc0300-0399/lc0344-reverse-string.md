---
tags:
    - Two Pointers
    - String
---

# LC344. Reverse String

## Problem Description

[LeetCode Problem 344](https://leetcode.com/problems/): Write a function that reverses a string. The input string is given as an array of characters `s`.

You must do this by modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm)
with `O(1)` extra memory.

## Clarification

-

## Assumption

-

## Solution

### Approach 1: Iteration with Two Pointers

Use two pointers, one start from the beginning of the array and the other from the end.
Move two pointers from two ends to the center and swap two values during the moving.

=== "Python"
    ```python
    class Solution:
    def reverseString(self, s: List[str]) -> None:
        """
        Do not return anything, modify s in-place instead.
        """

        idx_begin, idx_end = 0, len(s) - 1

        while idx_begin < idx_end:
            s[idx_begin], s[idx_end] = s[idx_end], s[idx_begin]
            idx_begin += 1
            idx_end -= 1
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  Every execution two pointers together move 2 steps. So it takes $n/2$ executions. So
  the time complexity is $O(n)$.
- Space complexity: $O(1)$  
  Only use limited index variables.

### Approach 2: Recursion

We can also use two pointer to solve the problem recursively by passing updated the
begin and end indices as arguments.

=== "python"
    ```python
    class Solution:
      def reverseString(self, s: List[str]) -> None:
          """
          Do not return anything, modify s in-place instead.
          """
          self.reverse(s, 0, len(s) - 1)

      def reverse(self, s: list[str], idx_begin: int, idx_end: int) -> None:
          # Base case: 0 or 1 character, no need to swap
          if idx_begin >= idx_end:
              return

          # Swap two ends
          s[idx_begin], s[idx_end] = s[idx_end], s[idx_begin]

          # Recursive call a smaller string without two ends.
          self.reverse(s, idx_begin + 1, idx_end - 1)
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  It performs $n/2$ swaps with recursive function calls.
- Space complexity: $O(n)$  
  The recursive function call stack depth is up to $n/2$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Iteration | $O(n)$          | $O(1)$
Approach - Recursion | $O(n)$          | $O(n)$

## Test

- Test empty array.
- Test array with 1 or 2 elements.
