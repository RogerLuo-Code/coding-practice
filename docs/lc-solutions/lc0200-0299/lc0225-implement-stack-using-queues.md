---
tags:
    - Queue
---

# LC225. Implement Stack using Queues

## Problem Description

[LeetCode Problem 225](https://leetcode.com/problems/implement-stack-using-queues): Implement a last-in-first-out (LIFO) stack using only two queues. The implemented stack should support all the functions of a normal stack (`push`, `top`, `pop`, and `empty`).

Implement the `MyStack` class:

- `void push(int x)` Pushes element x to the top of the stack.
- `int pop()` Removes the element on the top of the stack and returns it.
- `int top()` Returns the element on the top of the stack.
- `boolean empty()` Returns `true` if the stack is empty, `false` otherwise.

## Clarification

- Any time complexity requirement?
- What to return for pop/top operations when stack is empty?
- What about just using 1 queue?

## Assumption

-

## Solution

### Approach - 1 queue

We can use 1 queue instead of 2 queues to achieve the stack functions. For `pop` operations, we need to pop the front elements out and append them back until the last element is at the front.

=== "Python"
    ```python
    from collections import deque

    class MyStack:

        def __init__(self):
            self.queue = deque()

        def push(self, x: int) -> None:
            self.queue.append(x)

        def pop(self) -> int:
            self.move()
            return self.queue.popleft()

        def top(self) -> int:
            return self.queue[-1]

        def empty(self) -> bool:
            return not self.queue

        def move(self) -> bool:
            n = len(self.queue)

            for i in range(n - 1):
                self.queue.append(self.queue.popleft())
    ```

#### Complexity Analysis of Approach 1

- Time complexity:
    - `push`: $O(1)$ since the queue `append` function is $O(1)$.
    - `pop`: $O(n)$ since needs to move the elements using a for-loop.
    - `top`: $O(1)$ since the queue's view operations is $O(1)$.
    - `empty`: $O(1)$
- Space complexity: $O(n)$  
  In the worst case, it will store all $n$ elements.

## Test
