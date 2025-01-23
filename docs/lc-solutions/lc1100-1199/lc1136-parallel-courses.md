---
tags:
    - Topological Sort
---

# LC1136. Parallel Courses

## Problem Description

[LeetCode Problem 1136](https://leetcode.com/problems/parallel-courses/description/):
You are given an integer `n`, which indicates that there are `n` courses labeled from
`1` to `n`. You are also given an array `relations` where
`relations[i] = [prevCoursei, nextCoursei]`, representing a prerequisite relationship
between course `prevCoursei` and course `nextCoursei`: course `prevCoursei` has to be
taken before course `nextCoursei`.

In one semester, you can take **any number** of courses as long as you have taken all
the prerequisites in the **previous**semester for the courses you are taking.

Return _the **minimum** number of semesters needed to take all courses_. If there is no
way to take all the courses, return `-1`.

## Clarification

- directed edge from prevCourse to nextCourse
- index from 1 to n (not 0 to n - 1)
- takey any number of courses in one semester as long as no prerequisites needed

## Assumption

-

## Solution

### Approach - Topological Sort

This problem is similar to course schedule II problem and can be solved using
topological sort. It needs to count number of levels. Each level is for the courses with
the same in-degrees. The number of levels indicate the number of semesters.

=== "Python"
    ```python
    from collections import defaultdict, deque


    class Solution:
        def minimumSemesters(self, n: int, relations: List[List[int]]) -> int:
            # Build adjacent list and compute in degrees from relations.
            adj_list = defaultdict(list)
            in_degrees = {i: 0 for i in range(1, n + 1)}  # (1)
            for prev_course, next_course in relations:
                if next_course not in adj_list[prev_course]:  # Handle duplicated relations.
                    adj_list[prev_course].append(next_course)  # Directed edge.
                    in_degrees[next_course] += 1

            # Find nodes with zero in-degree
            zero_in_degree_list = [i for i in range(1, n + 1) if in_degrees[i] == 0]
            zero_in_degree_queue = deque(zero_in_degree_list)

            # Perform topological sort
            n_levels = 0
            n_processed = 0
            while zero_in_degree_queue:
                size = len(zero_in_degree_queue)
                n_processed += size
                for i in range(size):
                    curr_node = zero_in_degree_queue.popleft()
                    for next_node in adj_list[curr_node]:
                        in_degrees[next_node] -= 1
                        if in_degrees[next_node] == 0:
                            zero_in_degree_queue.append(next_node)

                n_levels += 1

            return n_levels if n_processed == n else -1
    ```

    1. Use dict comprehension instead of defaultdict since all nodes need to have in-degree.

#### Complexity Analysis of Approach 1

- Time complexity: $O(V + E)$ where $V$ is number of courses and $E$ is number of relations.
    - Initialize in_degree dictionary takes $O(V)$ for all $V$ courses.
    - Build adjacent lis takes $O(E)$ time since goes through all relations.
    - Find zero in-degree queue takes $O(V)$ since goes trough all nodes and check in-degree.
    - Queue operations will process all nodes exact once, taking $O(V)$ time.
    - Neighbor explorations of all nodes take $O(E)$ time.
    - So the total time complexity is $O(V) + O(E) + O(V) + O(V) + O(E) = O(V + E)$.
- Space complexity: $O(V + E)$.
    - Adjacent list takes $O(V + E)$ space store all nodes and their edges.
    - In-degree dictionary take $O(V)$ space since store in-degrees for all nodes.
    - Queue may hold all nodes in the worst case, taking $O(V)$.
    - So the total space complexity is $O(V + E) + O(V) + O(V) = O(V + E)$.

## Test
