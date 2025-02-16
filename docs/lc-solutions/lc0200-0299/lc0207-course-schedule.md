---
tags:
    - Topological Sort
---

# LC207. Course Schedule

## Problem Description

[LeetCode Problem 207](https://leetcode.com/problems/course-schedule/description/):
There are a total of `numCourses` courses you have to take, labeled from `0` to
`numCourses - 1`. You are given an array `prerequisites` where 
`prerequisites[i] = [ai, bi]` indicates that you **must** take course `bi` first if you
want to take course `ai`.

- For example, the pair `[0, 1]`, indicates that to take course `0` you have to first
take course `1`.

Return `true` if you can finish all courses. Otherwise, return `false`.

## Clarification

- 0-based indexing
- [ai, bi], bi is the prerequisites

## Assumption

-

## Solution

### Approach - Topological Sort

We can solve the problem by using topological sort. It is similar to
[210 Course Schedule II](lc0210-course-schedule-ii.md). Instead of find ordered courses,
return whether all courses can finish.

=== "Python"
    ```python
    from collections import deque

    class Solution:
        def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
            # Build adjacent list and count in degrees
            adj_list = defaultdict(list)
            in_degrees = [0] * numCourses  # (1)
            for course_after, course_before in prerequisites:
                adj_list[course_before].append(course_after)
                in_degrees[course_after] += 1

            # Obtain zero in-degree list
            zero_in_degree_list = [i for i in range(numCourses) if in_degrees[i] == 0]
            zero_in_degree_queue = deque(zero_in_degree_list)

            # Conduct topological sort
            n_visited = 0
            while zero_in_degree_queue:
                curr_course = zero_in_degree_queue.popleft()
                n_visited += 1

                for next_course in adj_list[curr_course]:
                    in_degrees[next_course] -= 1
                    if in_degrees[next_course] == 0:
                        zero_in_degree_queue.append(next_course)

            # return whether finish all courses
            return n_visited == numCourses
    ```

    1. The courses are labeled from 0 to numCourses - 1.

#### Complexity Analysis of Approach 1

- Time complexity: $O(V + E)$  
    - Building adjacent list and computing in-degree takes $O(E)$ since going through
    all prerequisites.
    - Finding initial course with 0 in-degree takes $O(V)$ time since going through all courses.
    - For queue operations, it will process all $V$ nodes and each queue operation takes
    $O(1)$. So the queue operations take $O(V)$.
    - For neighboring exploration, it will explore all neighbor nodes of each node, the
    total number of exploration is $O(E)$.  
    So the total time complexity is $O(E) + O(V) + O(V) + O(E) = O(V + E)$.
- Space complexity: $O(n)$  
    - Adjacent list takes $O(E)$ since storing edges of all nodes.
    - In-degree dictionary takes $O(V)$ space in the worst case to store in-degree of
    all nodes.
    - The queue may take $O(V)$ space in the worst case.  
    So the total space complexity is $O(E) + O(V) + O(V) = O(V + E)$

## Test
