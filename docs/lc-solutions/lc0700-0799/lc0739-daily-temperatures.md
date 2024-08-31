---
tags:
    - Stack
---

# LC739. Daily Temperatures
## Problem Description
[LeetCode Problem 739](https://leetcode.com/problems/daily-temperatures/): Given an array of integers `temperatures` represents the daily temperatures, return _an array_ `answer` _such that_`answer[i]` _is the number of days you have to wait after the_ `ith` _day to get a warmer temperature_. If there is no future day for which this is possible, keep `answer[i] == 0` instead.

## Clarification
- answer[i]: number of days to wait until a warmer temperature
- if don't exist, set 0

## Assumption
-

## Solution
### Approach - Stack
Use `monotonic stack` to store indices of temperatures so temperatures are in monotonic **decreasing** order. Note that for a given index, we can use `temperatures[i]` to find the temperature of the `ith` day. So only indexes are stored in the stack.

When encountering warmer temperature (warmer than the temperature on top of the stack), it means that the current day is the **first** day with a warmer temperature than the day on top of the stack. Then update answers and pop up lower temperatures until no lower temperature or stack is empty. After that, push the current index to the stack.

=== "Python"
    ```python
    from collections import deque
    class Solution:
        def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
            n_days = len(temperatures)
            answer = [0] * n_days
            stack = deque()
            for curr_day in range(n_days):
                # Pop until the current temperature is not warmer than the temperature at the top
                while stack and temperatures[stack[-1]] < temperatures[curr_day]:
                    prev_day = stack.pop()
                    answer[prev_day] = curr_day - prev_day
                stack.append(curr_day)

            return answer
    ```

#### Complexity Analysis

* Time complexity: $O(n)$  
  Each element can only be added to the stack once. In the worst case, every element will be pushed and popped once. This gives a time complexity of $O(2n) = O(n)$.
* Space complexity: $O(n)$  
  If the input is non-increasing, then all $n$ elements will add to the stack.

## Test