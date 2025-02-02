---
tags:
    - Shortest Path
---

# LC743. Network Delay Time

## Problem Description

[LeetCode Problem 743](https://leetcode.com/problems/network-delay-time/description/):
You are given a network of `n` nodes, labeled from `1` to `n`. You are also given
`times`, a list of travel times as directed edges `times[i] = (ui, vi, wi)`, where `ui`
is the source node, `vi` is the target node, and `wi` is the time it takes for a signal
to travel from source to target.

We will send a signal from a given node `k`. Return _the **minimum** time it takes for
all the_ `n` _nodes to receive the signal_. If it is impossible for all the `n` nodes to
receive the signal, return `-1`.

## Clarification

- Find minimum time between a given node k and the rest of nodes
- May not reach all nodes

## Assumption

-

## Solution

The problem is to find the shortest time for each node to receive the signal and then
find the maximum of shortest time of all nodes.

### Approach - Shortest Path Faster Algorithm

Starting from node `k`, use a queue to track the signal along the
directed edges with cumulative time. This is similar to breadth-first search but allowing
nodes visited multiple times. We will update the shortest time between node `k` and any
node `i` during the search process. We will add node to the queue if the next node has
less time.

Note that this algorithm can also works with negative weight but need to detect negative
edge cycle.

=== "Python"
    ```python
    import math
    from collections import defaultdict, deque


    class Solution:
        def networkDelayTime(self, times: List[List[int]], n: int, k: int) -> int:
            # Build adj_list with directed edge and weight
            adj_list = defaultdict(list)
            for source, target, time in times:
                adj_list[source].append((target, time))

            # Find shortest time from k to each node
            shortest_time_map = self.find_shortest_time(k, adj_list)

            # Return time to reach all nodes
            if len(shortest_time_map) == n:
                return max(shortest_time_map.values())
            else:
                return -1

        def find_shortest_time(
            self, source: int, adj_list: dict[int, list]
        ) -> dict[int, int]:
            shortest_time = defaultdict(lambda: math.inf)  # (1)
            shortest_time[k] = 0  # (2)
            queue = deque([k])  # (node)
            while queue:
                curr_node = queue.popleft()
                curr_time = shortest_time[curr_node]
                for next_node, time in adj_list[curr_node]:
                    next_time = curr_time + time
                    if next_time < shortest_time_map[next_node]:
                        shortest_time_map[next_node] = next_time
                        queue.append(next_node)
    ```

    1. Store shortest time from k to each node.
    2. For starting node k, the shortest time from k to k is 0.

#### Complexity Analysis of Approach 1

- Time complexity: $O(V E)$ where $V$ is the number of nodes and $E$ is the number of
edges  
    - Build adjacent list takes $O(E)$ time since going through all times (i.e. edges);
    - `find_shortest_time` function goes through multiple paths between node `k` and the
    rest of nodes. It may reach each node multiple times. In the worst case (a complete
    graph), each node will be visited $E$ times (number of edges). So the time
    complexity is $O(V E)$;
    - The `max` function takes $O(V)$ time;  
    The total time complexity is $O(E) + O (V E) + O(V) = O(V E)$.
- Space complexity: $O(V + E)$  
    - Build adjacent list takes $O(V + E)$ space to store nodes and edges;
    - The queue may store all nodes, taking $O(V)$ space;
    - Shortest time map takes $O(V)$ space to store shortest time for each node;
    So the total space complexity is $O(V + E) + O(V) + O(V) = O(V + E)$.

### Approach 2 - Dijkstra's Algorithm

This algorithm similar to approach 1 but replacing queue with a priority queue.

=== "python"
    ```python
    import math
    import heapq
    from collections import defaultdict


    class Solution:
        def networkDelayTime(self, times: List[List[int]], n: int, k: int) -> int:
            # Build adj_list with directed edge and weight
            adj_list = defaultdict(list)
            for source, target, time in times:
                adj_list[source].append((target, time))

            # Find shortest time from k to each node
            shortest_time_map = self.find_shortest_time(k, adj_list)

            # Return max value of shortest_time of all nodes
            if len(shortest_time_map) == n:
                return max(shortest_time_map.values())
            else:
                return -1

        def find_shortest_time(
            self, source: int, adj_list: dict[int, list]
        ) -> dict[int, int]:
            shortest_time_map = defaultdict(lambda: math.inf)  # (1)
            pq = [(0, source)]

            while pq:
                curr_time, curr_node = heapq.heappop(pq)
                if curr_node not in shortest_time_map:  # (2)
                    shortest_time_map[curr_node] = curr_time

                    for next_node, time in adj_list[curr_node]:
                        heapq.heappush(pq, (curr_time + time, next_node))
    ```

    1. Store shortest time from k to each node.
    2. Just check existing and no need to compare whether time is the shortest since the
    priority queue will return the smallest value. This assumes non-negative weight.

#### Complexity Analysis of Approach 2

- Time complexity: $O(E + V \log V)$  
    - Build adjacent list takes $O(E)$ time since going through all times (i.e. edges);
    - `find_shortest_time` function in the worst case goes through all nodes, $V$. For
    each node, push and pop from priority queue takes $\log V$. So the time complexity
    is $V \log V$;
    - The `max` function takes $O(V)$ time;  
    The total time complexity is $O(E) + O (V \log V) + O(V) = O(E + V \log V)$.
- Space complexity: $O(n)$  
    - Build adjacent list takes $O(V + E)$ space to store nodes and edges;
    - The priority queue may store all nodes, taking $O(V)$ space;
    - Shortest time map takes $O(V)$ space to store shortest time for each node;
    So the total space complexity is $O(V + E) + O(V) + O(V) = O(V + E)$.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach - SPFA |  $O(V E)$           | $O(V + E)$ |
Approach - Dijkstra |  $O(E + V \log V)$           | $O(V + E)$  |

## Test

- Single node (`n = 1`): The result is always $0$.
- Disconnected nodes: Return $-1$ if not all nodes are reachable.
- Multiple paths between nodes: Ensure the algorithm finds the shortest path.
