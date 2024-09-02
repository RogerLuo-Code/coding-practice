---
tags:
    - Stack
---

# LC150. Evaluate Reverse Polish Notation

## Problem Description

[LeetCode Problem 150](https://leetcode.com/problems/evaluate-reverse-polish-notation/): You are given an array of strings `tokens` that represents an arithmetic expression in a [Reverse Polish Notation](http://en.wikipedia.org/wiki/Reverse_Polish_notation).

Evaluate the expression. Return _an integer that represents the value of the expression_.

**Note** that:

- The valid operators are `'+'`, `'-'`, `'*'`, and `'/'`.
- Each operand may be an integer or another expression.
- The division between two integers always **truncates toward zero**.
- There will not be any division by zero.
- The input represents a valid arithmetic expression in a reverse polish notation.
- The answer and all the intermediate calculations can be represented in a **32-bit** integer.

## Clarification

- What are valid operators
- What about division by 0?
- What to do with incorrect expression?
- Go through examples

## Assumption

-

## Solution

### Approach - Stack

Use stack to solve the problem:

- push numbers to stack
- for operators, pop up two operands and push result to stack

For integer division, in Python:

- `a // b`: truncate the result to the smaller value
- `int(a / b)`: do float division `a / b` and then use `int` function to truncate toward zero.

Inflix Notation vs. Reverse Polish Notation

=== "Python"
    ```python
    class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        stack = deque()

        for token in tokens:
            if token in "+-*/":
                operand2 = stack.pop()
                operand1 = stack.pop()
                if token == '+':
                    stack.append(operand1 + operand2)
                elif token == '-':
                    stack.append(operand1 - operand2)
                elif token == '*':
                    stack.append(operand1 * operand2)
                elif token == '/':
                    stack.append(int(operand1 / operand2))
                else:
                    pass
                    # the operator is not supported
            else:
                stack.append(int(token))

        return stack.pop()
    ```

=== "Python - Lambda"
    ```python
    class Solution:
    OPERATIONS = {
        "+": lambda a, b: a + b,
        "-": lambda a, b: a - b,
        "/": lambda a, b: int(a / b),
        "*": lambda a, b: a * b,
    }

    def evalRPN(self, tokens: List[str]) -> int:
        stack = deque()

        for token in tokens:
            if token in self.OPERATIONS:
                operand2 = stack.pop()
                operand1 = stack.pop()
                operation = self.OPERATIONS[token]
                stack.append(operation(operand1, operand2))
            else:
                stack.append(int(token))

        return stack.pop()
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  We do a linear search of all $n$ numbers. The operation of each step is $O(1)$ (either `push` or two `pop`s with math operation).
- Space complexity: $O(n)$  
  In the worst case, the stack will have all the numbers (~ $n/2$).

## Test
