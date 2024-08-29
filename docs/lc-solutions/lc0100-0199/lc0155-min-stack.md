---
tags:
- Stack
---

# LC155. Min Stack
## Problem Description
[LeetCode Problem 155](https://leetcode.com/problems/min-stack/): Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the `MinStack` class:

- `MinStack()` initializes the stack object.
- `void push(int val)` pushes the element `val` onto the stack.
- `void pop()` removes the element on the top of the stack.
- `int top()` gets the top element of the stack.
- `int getMin()` retrieves the minimum element in the stack.

You must implement a solution with `O(1)` time complexity for each function.

## Clarification
- Normal stack operation + retrieve the minimum
- O(1) time complexity
- What value should return for invalid cases: pop(), getMin, top() if no values in stack

## Assumption

## Solution
### Approach - Stack of Value/Min Paris
Use one stack to store `(value, min)` pair.

=== "Python"
    ```python
    from collections import deque

    class MinStack:

        def __init__(self):
            self.stack = deque()

        def push(self, val: int) -> None:
            # Push (val, min) pair
            # If the stack is empty, the min value is the first value
            if not self.stack:
                self.stack.append((val, val))
                return

            current_min = self.stack[-1][1]
            self.stack.append((val, min(val, current_min)))

        def pop(self) -> None:
            self.stack.pop()

        def top(self) -> int:
            return self.stack[-1][0]

        def getMin(self) -> int:
            return self.stack[-1][1]
    ```

#### Complexity Analysis
* Time complexity: $O(1)$ for all operations  
Similar to stand stack operations.
* Space complexity: $O(n)$  
The worse case to save all (value, min) pairs. The space used is $O(2 n) = O(n)$.

## Test