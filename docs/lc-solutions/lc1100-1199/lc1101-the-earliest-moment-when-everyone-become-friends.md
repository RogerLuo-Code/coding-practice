---
tags:
    - Union-Find
---

# LC1101. The Earliest Moment When Everyone Become Friends

## Problem Description

[LeetCode Problem 1101](https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends/description/): There are n people in a social group labeled from `0` to `n - 1`. You are given an array `logs`where `logs[i] = [timestampi, xi, yi]` indicates that `xi` and `yi` will be friends at the time `timestampi`.

Friendship is **symmetric**. That means if `a` is friends with `b`, then `b` is friends with `a`. Also, person `a` is acquainted with a person `b` if `a` is friends with `b`, or `a` is a friend of someone acquainted with `b`.

Return _the earliest time for which every person became acquainted with every other person_. If there is no such earliest time, return `-1`.

## Clarification

- Friendship is symmetric (undirected graph?)
- clarifications on acquainted, does long friendship link count for acquainted?
0 - 1 - 2 - 3 - 4 are in single link friendship. Are 0 and 4 acquainted?

## Assumption

-

## Solution

### Approach - Union Find

First, sort the log by time stamp. Then use union find to union two people based on the log. When comes downs to the single connected component the first time, the time stamp is the earliest time everyone become friends.

=== "Python"
    ```python
    from operator import itemgetter

    class UnionFind:
        def __init__(self, n):
            self.root = [i for i in range(n)]
            self.rank = [0] * n
            self.count = n

        def find(self, x):
            if x == self.root[x]:
                return x

            self.root[x] = self.find(self.root[x])
            return self.root[x]

        def union(self, x, y):
            root_x = self.find(x)
            root_y = self.find(y)

            if root_x != root_y:
                if self.rank[root_x] > self.rank[root_y]:
                    self.root[root_y] = self.root[root_x]
                elif self.rank[root_x] < self.rank[root_y]:
                    self.root[root_x] = self.root[root_y]
                else:
                    self.root[root_y] = self.root[root_x]
                    self.rank[root_x] += 1
                self.count -= 1


    class Solution:
        def earliestAcq(self, logs: List[List[int]], n: int) -> int:
            logs_sorted = sorted(logs, key=itemgetter(0))  # (1)

            uf = UnionFind(n)

            for time_stamp, friend_a, friend_b in logs_sorted:
                uf.union(friend_a, friend_b)

                if uf.count == 1:  # (2)
                    return time_stamp

            return -1  # (3)
    ```

    1. Sort the events in chronological order in order to find the earliest moment. We can also sort in-place if the input is allowed to change.
    2. Return the moment when all individuals are all connected. This is earliest moment.
    3. Not everyone connected.


#### Complexity Analysis of Approach 1

- Time complexity: $O(m \log m + n + m \alpha(n))$ where $n$ is number of people and $m$ is the number of logs  
    - First, Sort the logs (Pyhon uses [Timsort](https://en.wikipedia.org/wiki/Timsort)) takes $O(m \log m$) time.
    - Then, creating a union-find data structure takes $O(n)$ time to initialize `root` and `rank` arrays.
    - Then iterate through the $m$ sorted logs. At each iteration, it invokes the `union` function with amortized time complexity of $O(\alpha(n))$. So all iterations take $O(m \alpha(n))$.  
    So the total time complexity is $O(m \log m) + O(n) + O(m \alpha(n)) = O(m \log m + n + m \alpha(n))$.

- Space complexity: $O(n + m)$  
    - The space complexity of union-find data structure takes $O(n)$ due to `root` and `rank` arrays.
    - The space complexity of the sorting algorithm depends on the implementation. Python uses [Timsort](https://en.wikipedia.org/wiki/Timsort), which takes $O(m)$.
    - If the log is not allowed to change, the sorted log takes $O(3 m) = O(m)$  
    So the total time complexity is $O(n) + O(m) + O(m) = O(n + m)$

## Test

- `n = 1`, return 0 since a person is connected to himself.
- log doesn't connect all nodes.