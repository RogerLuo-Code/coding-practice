---
tags:
    - Topological Sort
---

# LC210. Course Schedule II

## Problem Description

[LeetCode Problem 210](https://leetcode.com/problems/course-schedule-ii/description/):
There are a total of `numCourses` courses you have to take, labeled from `0` to
`numCourses - 1`. You are given an array `prerequisites` where
`prerequisites[i] = [ai, bi]` indicates that you **must** take course `bi` first if you
want to take course `ai`.

- For example, the pair `[0, 1]`, indicates that to take course `0` you have to first
take course `1`.

Return _the ordering of courses you should take to finish all courses_. If there are
many valid answers, return **any** of them. If it is impossible to finish all courses,
return **an empty array**.

## Clarification

- `prerequisites[i] = [ai, bi]` order is bi --> ai
- may contain cycle

## Assumption

-

## Solution

We can represent the course information in the form of a **directed** and **unweighted**
graph:

- Each course represents a vertex in the graph.
- Each prerequisite relationship, `prerequisites[i] = [ai, bi]`, represents a directed
edge from `bi` to `ai`.
- The graph may be a cyclic graph.

### Approach - Topological Sort

The ordering of courses based on prerequisites is a classic topological sorting problem.

- Build adj_list and compute in_degree for each course
- Go through each zero-in-degree vertex in a queue
    - move it to result list
    - reduce neighbor vertex's in degree to 1
    - if in degree is 0, add to the queue
- if len(result) != numCourses, return empty array

=== "Python"
    ```python
    from collections import defaultdict, deque


    class Solution:
        def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
            ordered_courses = []

            # Build adjacent list and compute in-degree
            course_in_degree = [0] * numCourses
            adj_list = defaultdict(list)
            for dependent_course, prerequisite_course in prerequisites:
                adj_list[prerequisite_course].append(dependent_course)
                course_in_degree[dependent_course] += 1

            # Iterate zero in degree queue
            zero_in_degree_list = [i for i in range(numCourses) if course_in_degree[i] == 0]
            zero_in_degree_queue = deque(zero_in_degree_list)
            while zero_in_degree_queue:
                curr_course = zero_in_degree_queue.popleft()
                ordered_courses.append(curr_course)

                # Reduce in-degree of all the neighbors
                for dependent_course in adj_list[curr_course]:
                    course_in_degree[dependent_course] -= 1
                    if course_in_degree[dependent_course] == 0:
                        zero_in_degree_queue.append(dependent_course)

            return ordered_courses if len(ordered_courses) == numCourses else []
    ```

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
- Space complexity: $O(V + E)$  
    - Adjacent list takes $O(E)$ since storing edges of all nodes.
    - In-degree dictionary takes $O(V)$ space in the worst case to store in-degree of
    all nodes.
    - The queue may take $O(V)$ space in the worst case.  
    So the total space complexity is $O(E) + O(V) + O(V) = O(V + E)$

### Approach 2 -

Solution

=== "python"
    ```python
    code
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(1)$  
  Explanation
- Space complexity: $O(n)$  
  Explanation

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach -  |  $O(1)$           | $O(n)$ |
Approach -  |  $O(1)$           | $O(n)$  |

## Test

- No prerequisites (`prerequisites = []`): Any order of courses is valid.
- Single course (`numCourses = 1`).
- Cycles in the graph (e.g., `[0,1]`,`[1,0]`): Return an empty list.