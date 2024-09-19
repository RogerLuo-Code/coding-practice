---
tags:
    - Stack
---

# LC232. Implement Queue using Stacks

## Problem Description

[LeetCode Problem 232](https://leetcode.com/problems/implement-queue-using-stacks): Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (`push`, `peek`, `pop`, and `empty`).

Implement the `MyQueue` class:

- `void push(int x)` Pushes element x to the back of the queue.
- `int pop()` Removes the element from the front of the queue and returns it.
- `int peek()` Returns the element at the front of the queue.
- `boolean empty()` Returns `true` if the queue is empty, `false`otherwise.

## Clarification

- Any requirement on time complexity of different operations? Still O(1)?
- What to return when stack is empty?

## Assumption

-

## Solution

### Approach - 2 Stacks with Move

- Use one **input** stack for pushing new elements
- Use one **output** stack for peak/pop
- **Move** all elements from input stack to output stack when performing peep/po with empty output stack. So the order is reversed with the correct one for peep/pop.

=== "Python"
    ```python
    from collections import deque
    class MyQueue:

        def __init__(self):
            self.input_stack = deque()
            self.output_stack = deque()

        def push(self, x: int) -> None:
            self.output_stack.append(x)

        def pop(self) -> int:
            self.move()
            return self.input_stack.pop()

        def peek(self) -> int:
            self.move()
            return self.input_stack[-1]

        def empty(self) -> bool:
            return not self.input_stack and not self.output_stack

        def move(self):
            if not self.input_stack:
                while self.output_stack:
                    self.input_stack.append(self.output_stack.pop())

    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(1)$ or Amortized $O(1)$

    - `push`: $O(1)$
    - `pop`: Amortized $O(1)$  
    Since this moving operation only happens once for each element (when it is about to be popped), the amortized time complexity for pop() is O(1)
    - `peek`: Amortized $O(1)$
    - `empty`: $O(1)$

- Space complexity: $O(n)$  
  In the worst case, store $n$ elements

## Test

- Empty
- 1 element
- normal queue
