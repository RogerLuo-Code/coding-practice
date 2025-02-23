---
tags:
    - Stack
---

# LC739. Daily Temperatures

## Problem Description

[LeetCode Problem 739](https://leetcode.com/problems/daily-temperatures/): Given an
array of integers `temperatures` represents the daily temperatures, return _an array_
`answer` _such that_`answer[i]` _is the number of days you have to wait after the_ `ith`
_day to get a warmer temperature_. If there is no future day for which this is possible,
keep `answer[i] == 0` instead.

## Clarification

- answer[i]: number of days to wait until a warmer temperature
- if don't exist, set 0

## Assumption

-

## Solution

### Approach - Stack

Observation: the temperatures in descending order can share the same "warmer" day. So we
can delay finding the answer for temperatures in descending order until finding a warmer
day. Then we can move backward to calculate the answers. This process matches the
behavior of a stack.

We can use `monotonic stack` to store indices of temperatures so temperatures are in monotonic
**decreasing** order. Note that for a given index, we can use `temperatures[i]` to find
the temperature of the `ith` day. So only indexes are stored in the stack.

On each day, there are two possibilities:

- If the current day's temperature is not warmer, just push the current day onto the
stack since it is not warmer (equal or smaller). This will maintain the sorted property.
- If the current temperature is warmer than the temperature on top of the stack, it
means that the current day is the **first** day with a warmer temperature than the
day on top of the stack. Then update answers and pop up lower temperatures until no
lower temperature or stack is empty. After that, push the current index to the stack.
After this, the sorted property is still maintained.

=== "Python"
    ```python
    from collections import deque
    class Solution:
        def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
            n_days = len(temperatures)
            answer = [0] * n_days
            stack = deque()
            for curr_day in range(n_days):
                # (1)
                while stack and temperatures[stack[-1]] < temperatures[curr_day]:
                    prev_day = stack.pop()
                    answer[prev_day] = curr_day - prev_day
                stack.append(curr_day)

            return answer
    ```

    1. Pop until the current temperature is not warmer than the temperature at the top.

#### Complexity Analysis

- Time complexity: $O(n)$  
  Each element can only be added to the stack once. In the worst case, every element
  will be pushed and popped once. This gives a time complexity of $O(2n) = O(n)$.
- Space complexity: $O(n)$  
  If the input is non-increasing, then all $n$ elements will add to the stack.

### Approach 2 - Array, Optimized Space

For the monotonic stack, we iterated forward trough the array and move backwards when
finding a warmer day. Can we find answers in an opposite way? iterate **backwards** through
the array and move **forwards** to find the number of days until a warmer day.

Yes, we can find the next warmer day by using the information from answers. For example,
for `temperature[i]`,

- If `temperature[i + 1]` <= `temperature[i]`, we can skip to temperature at
`j = i + 1 + answers[i + 1]` since we just need to find the next warmer temperature after
`i + 1` and answers store that information since moving backwards.
- if `temperature[j]` <= `temperature[i]`, continue to just ahead based on the
information in the answer.

Note that, we need to track the hottest temperature seen so far.
If `current temperature > hottest temperature`, no need to search since no warmer
temperatures available.

=== "python"
    ```python
    class Solution:
        def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
            n = len(temperatures)
            hottest = 0
            answer = [0] * n

            # Go though days in a reversed order
            for idx_curr_day in range(n - 1, -1, -1):
                curr_temp = temperatures[idx_curr_day]

                # (1)
                if curr_temp >= hottest:
                    hottest = curr_temp
                    continue

                # Find number of days to reach warmer temperature in forward order
                days = 1
                while temperatures[idx_curr_day + days] <= curr_temp:
                    days += answer[idx_curr_day + days] (2)
                answer[idx_curr_day] = days

            return answer
    ```

    1. If current temperature > hottest temp seen so far, no need to check warmer temperature since it doesn't exist.
    2. Use information from answer to search for the next warmer day.

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  The outer loop goes through $n$ temperatures and the inner loop will skip some indices,
  which leads to amortized time complexity $O(n)$.
- Space complexity: $O(n)$  
  The answer store $n$ values.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - | $O(1)$          | $O(n)$
Approach - | $O(1)$          | $O(n)$

## Test

- **Strictly decreasing temperatures** → `[90, 80, 70, 60]` → Output: `[0, 0, 0, 0]`
- **Strictly increasing temperatures** → `[60, 70, 80, 90]` → Output: `[1, 1, 1, 0]`
- **Single element** → `[75]` → Output: `[0]`