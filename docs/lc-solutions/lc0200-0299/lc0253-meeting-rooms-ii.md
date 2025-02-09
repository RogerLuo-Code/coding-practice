---
tags:
    - Heap
---

# LC253. Meeting Rooms II

## Problem Description

[LeetCode Problem 253](https://leetcode.com/problems/meeting-rooms-ii/description/):
Given an array of meeting time intervals `intervals` where
`intervals[i] = [starti, endi]`, return _the minimum number of conference rooms required_.

**Example 1:**

**Input:** intervals = [[0,30],[5,10],[15,20]]
**Output:** 2

**Example 2:**

**Input:** intervals = [[7,10],[2,4]]
**Output:** 1

## Clarification

- Explain more on minimum number of conference rooms --> most number of overlapped intervals?

## Assumption

-

## Solution

### Approach - Heap

- Like normal meetings, allocate rooms for meetings from earlier to later. So we first
sort intervals by start time.
- Don't care which room gets freed up based on their end times while allocating a room
for the current meeting.
- We can use a min-heap to store the end times of the meetings in various rooms. It
dynamically grows until reaching the minimum number of conference rooms:
    - Check the top element of the heap (end time), indicating the room that would be
    get free the earliest.
        - If it is not free, allocate a new room.
        - If it is free, no need to allocate a new room.

=== "Python"
    ```python
    import heapq
    from operator import itemgetter

    class Solution:
        def minMeetingRooms(self, intervals: List[List[int]]) -> int:
            # Sort intervals by start time.
            intervals_sorted = sorted(intervals, key=itemgetter(0))

            # Use a min heap to track the end times of ongoing meetings.
            # (1)
            min_heap = [intervals_sorted[0][1]]  # (2)
            for start_time, end_time in intervals_sorted[1:]:
                # (3)
                if min_heap[0] <= start_time:
                    heapq.heappop(min_heap)

                # (4)
                heapq.heappush(min_heap, end_time)

            return len(min_heap)  #(5)
    ```

    1. The heap represents active meeting rooms, with the earliest ending meeting time
    at the top.
    2. Add the end time of the first meeting.
    3. If the earliest ending meeting has already finished before the current one
    starts, remove it from the heap (freeing up a room).
    4. Add the current meeting's end time to heap.
        - If a room was freed in a previous step, the heap size remains the same.
        - If no room was free,  a new room is allocated, increasing the heap size.
    5. The heap size represents the number of rooms needed.

#### Complexity Analysis of Approach 1

- Time complexity: $O(n \log n)$  
    - Sorting the intervals takes $O(n \log n)$ time.
    - Iterate all $n$ intervals. For each iteration, it takes at least 1 heap operation,
    which takes $O(\log s)$ time where $s$ is the size of the heap. In the worst case,
    the heap size could be $n$. So the time complexity is $O(n \log n)$.
    - So the total time complexity is $O(n \log n)$.
- Space complexity: $O(n)$  
    - Sorting in Python takes $O(n)$ space.
    - Heap takes $O(n)$ space in the worst case.
    - So the total space complexity is $O(n)$.

### Approach 2 - Separate Start and End Times

The start and end times don't need to be together. When start time of one meeting > end
time of any meeting, it indicates a room is available. We don't need to know which room
is available.

With separation of start and end times and sort them individually, we can track them separately:

- if start time >= end time, the room is available and increase the end pointer;
- if start time < end time, no room is available and allocate a new room.

=== "python"
    ```python
    class Solution:
        def minMeetingRooms(self, intervals: List[List[int]]) -> int:
            # Separate start and end times and sort them individually.
            start_times_sorted = sorted([i[0] for i in intervals])
            end_times_sorted = sorted([i[1] for i in intervals])

            # Go through start times
            n_rooms_needed = 0
            end_pointer = 0
            for start_time in start_times_sorted:
                if start_time >= end_times_sorted[end_pointer]:
                    end_pointer += 1
                else:
                    n_rooms_needed += 1

            return n_rooms_needed
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n \log n)$  
    - Sorting start times takes $O(n \log n)$ time.
    - Sorting end times takes $O(n \log n)$ time.
    - Iterate all start times, which takes $O(n)$.
    - So the total time complexity is $O(n \log n) + O(n \log n) + O(n) = O(n \log n)$.
- Space complexity: $O(n)$  
    - Start and end times take $O(n)$ space.
    - Sorting in Python takes $O(n)$ space.
    - So the total space complexity is $O(n) + O(n) + O(n) = O(n)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach - Heap |  $O(n \log n)$           | $O(n)$ |
Approach -  |  $O(n \log n)$           | $O(n)$  |

## Test

- **Non-overlapping meetings** → Needs only one room.
- **Meetings that all overlap** → Requires `n` rooms.
- **Large input size** → Sorting dominates runtime complexity.