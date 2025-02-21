---
tags:
    - Queue
---

# LC346. Moving Average from Data Stream

## Problem Description

[LeetCode Problem 346](https://leetcode.com/problems/moving-average-from-data-stream):
Given a stream of integers and a window size, calculate the moving average of all
integers in the sliding window.

Implement the `MovingAverage` class:

- `MovingAverage(int size)` Initializes the object with the size of the window `size`.
- `double next(int val)` Returns the moving average of the last `size` values of the stream.

## Clarification

- `next` function will do two things: add val to the moving window and return the moving
average.

## Assumption

-

## Solution

### Approach - deque

From moving window definition, at each step, add a new element to the window, and at the
same time remove the oldest element from the window.

- We can use queue data structure to
implement the moving window, which has the constant time complexity ($O(1)$) to add or
remove an element from both ends.
- To compute the new sum, we keep the sum of the previous moving window and add the new
element and subtract the oldest element.

=== "Python"
    ```python
    from collections import deque


    class MovingAverage:

        def __init__(self, size: int):
            self.count = 0
            self.queue = deque([], size)
            self.size = size
            self.sum = 0

        def next(self, val: int) -> float:
            self.count += 1
            if self.count > self.size:
                tail = self.queue.popleft()
            else:
                tail = 0

            self.queue.append(val)  # (1)

            self.sum = self.sum + val - tail
            return self.sum / min(self.count, self.size)
    ```

    1. Since queue is defined with the fix size, append value here (not early). Otherwise, it will automatically popleft.

#### Complexity Analysis of Approach 1

- Time complexity: $O(1)$  
    - Two queue operations are $O(1)$.
    - New sum calculation is based on previous sum, new value, and the oldest value,
    which takes $O(1)$.
    - So the total time complexity is $O(1)$.
- Space complexity: $O(n)$, where $n$ is the size of moving window  
    The queue will store at most $n$ elements.

### Approach 2 - Circular Queue with Array

We can also use circular queue data structure to implement the moving window. The
circular queue is basically a queue with the circular shape.

we can implement a circular queue with a fixed-size array. The key to the implementation
is to find the relationship between the index of `head` and `tail` elements,
`tail = (head + 1) % size`. The `tail` element is right next to the `head` element. Once
moving the `head` forward, the previous `tail` will be overwritten.

=== "python"
    ```python
    class MovingAverage:

        def __init__(self, size: int):
            self.size = size
            self.queue = [0] * size
            self.head = 0
            self.window_sum = 0
            self.count = 0

        def next(self, val: int) -> float:
            self.count = min(self.count + 1, self.size)
            tail = (self.head + 1) % self.size  # (1)
            self.window_sum = self.window_sum - self.queue[tail] + val
            self.head = (self.head + 1) % self.size  # (2)
            self.queue[self.head] = val  # (3)
            return self.window_sum / self.count
    ```

    1. Find the index of the `tail` element since `head` is update in the last execution.
    2. Find the index of the `head` element.
    2. Update the `head`. The old `tail` will be overwritten.

#### Complexity Analysis of Approach 2

- Time complexity: $O(1)$  
  Find the indices and calculations take $O(1)$.
- Space complexity: $O(n)$  
  The circular queue will take at most $n$ elements.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach                  | Time Complexity | Space Complexity
--------------------------|-----------------|-----------------
Approach - deque          | $O(1)$          | $O(n)$
Approach - circular queue | $O(1)$          | $O(n)$

## Test
