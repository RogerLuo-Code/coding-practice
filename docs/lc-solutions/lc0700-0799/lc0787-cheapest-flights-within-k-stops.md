---
tags:
    - Shortest Path
---

# LC787. Cheapest Flights Within K Stops

## Problem Description

[LeetCode Problem 787](https://leetcode.com/problems/cheapest-flights-within-k-stops/description/):
There are `n` cities connected by some number of flights. You are given an array
`flights` where `flights[i] = [fromi, toi, pricei]` indicates that there is a flight
from city `fromi` to city `toi` with cost `pricei`.

You are also given three integers `src`, `dst`, and `k`, return _**the cheapest price**
from_ `src` _to_ `dst` _with at most_ `k` _stops._ If there is no such route, return `-1`.

## Clarification

- Does `k` stops mean the number of cities between `src` and `dst`?
- Directed edge

## Assumption

-

## Solution

The problem can be considered as directed graph with positive weights where vertices are
the cities and flights (with prices) as directed weighted edges. The problem becomes to
find the shortest paths from a source city to a destination with positive weights.

### Approach - Breadth-First Search

We can use breadth-first search (BFS) to explore cities level by level, where each level
corresponds to the number of stops.

- Use a queue to maintain the current cost and number of stops for each path.
- Use a dictionary to track the minimum cost to reach a city within a certain number of
stops to avoid unnecessary processing.

???+ "Tips on calculating new cost"

    - When calculating `new_cost = cost + price`, the `cost` variable represents the
    cost of reaching the `current_city` during the current BFS step. This ensures that
    the new cost is based on the cost from the **specific path** that leads to `current_city`.
    - When calculating `new_cost = min_cost[current_city] + price`,
    `min_cost[current_city]` is the **globally minimum cost** recorded for reaching
    `current_city`. This value might have been computed in a **previous BFS step** from
    a completely **different path**. Use it here means the cost calculation is no longer
    tied to the current BFS traversal path, but rather to the **overall best** observed
    so far.

=== "Python"
    ```python
    from collections import defaultdict, deque

    class Solution:
        def findCheapestPrice(
            self, n: int, flights: List[List[int]], src: int, dst: int, k: int
        ) -> int:

            # Create adjacent list
            adj_list = defaultdict(list)
            for from_city, to_city, price in flights:
                adj_list[from_city].append((to_city, price))

            # Create the minimum cost dictionary to track the minimum cost to reach each city
            min_cost = defaultdict(lambda: float("inf"))
            min_cost[(src, 0)] = 0  # cost to reach source is 0

            queue = deque([(src, 0, 0)])  # store (city, stops, cost)

            while queue:  # BFS traversal
                curr_city, stops, cost = queue.popleft()

                if stops <= k:
                    for next_city, price in adj_list[curr_city]:
                        new_cost = cost + price
                        # Only consider the path if it's cheaper
                        if new_cost < min_cost[next_city]:
                            min_cost[next_city] = new_cost
                            queue.append((next_city, stops + 1, new_cost))

            if dst in min_cost:
                return min_cost[dst]
            else:
                return -1
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(k V + k E)$  
    - Build adjacent list takes $O(E)$ time since going through all edges;
    - For BFS traversal, there are two nested levels for iteration. The outer level is to
    iterate cities in the queue. All cities could be added or removed from the
    queue at most $k + 1$ times (due to $k$ stops), so at most $k V$ cities in the queue.
    The inner level iterate neighbor cities of the current city (i.e., edges of the
    current city). In the worst case, it will explore neighbors of all cities $k + 1$
    times with total of $k E$. Moreover, queue operations(enqueue and deque) take
    $O(1)$. So the time complexity of BFS is $O(k V + k E)$.  
    The total time complexity is $O(E) + O(k V + k E) = O(k V + k E)$.
- Space complexity: $O(k V + E)$  
    - The adjacent list takes $O(V + E)$ space;
    - The queue stores $k V$ nodes in the worst case;
    - The `min_cost` dictionary takes $O(V)$ space;  
    The total time complexity is $O(V + E) + O(k V) + O(V)= O(k V + E)$.

???- "Detailed Time Complexity Analysis for BFS"

    - **Queue Operations ($O(k V)$):**
        - Each city can be enqueued and dequeued at most $k + 1$ times, where $k$ is the
        maximum number of stops allowed.
        - Since there are $V$ cities, the total number of enqueue and dequeue operations
        is: $(k + 1) V$, which is $O(k V)$ time.
    - **Edge Traversal ($O(k E)$):**
        - For every dequeue operation of a city, its outgoing edges are processed
        (neighbor exploration).
        - Since each city is dequeued at most $k + 1$ times, and there are $E$ total edges
        in the graph, the total number of edge considerations is: $(k + 1) E$, which is
        $O(k E)$ time.
    - **Total Time Complexity:**: $O(k V + k E)$.
        - This reflects the time spent on both queue operations and edge traversal.

### Approach 2 - Dijkstra

We can use Dijkstra's algorithm to solve the shortest path problem.

A priority queue is used to select the node that currently has the lowest price.
Additionally, using an dictionary to track the minimum number of stops needed to reach
each city.

=== "python"
    ```python
    import heapq

    class Solution:
        def findCheapestPrice(self, n: int, flights: List[List[int]], src: int,
            dst: int, k: int) -> int:

            # Create adjacent list
            adj_list = defaultdict(list)
            for from_i, to_i, price_i in flights:
                adj_list[from_i].append((to_i, price_i))

            city_stops_map = defaultdict(lambda: float("inf"))
            heap = [(0, src, 0)]  # (1)
            while heap:
                curr_price, curr_city, n_stops = heapq.heappop(heap)

                if curr_city == dst:
                    return curr_price

                if n_stops <= k and n_stops < city_stops_map[curr_city]:  # (2)
                    city_stops_map[curr_city] = n_stops
                    for next_city, price in adj_list[curr_city]:
                        heapq.heappush(heap, (curr_price + price, next_city, n_stops + 1))

            return -1  # (3)
    ```

    1. Add `(cum_price, city, number of stops)`.
    2. Have to add `n_stops < city_stops_map[curr_city]` to prevent exceeding time limit.
    The idea is that if you've already reached a city with fewer stops, revisiting it
    with more stops means:
        - The route is longer in terms of flights.
        - The total cost cannot be cheaper because you would be adding more flight
        prices (positive).  
    Note that the worst-case time complexity remains the same.
    3. Can't reach the destination.


#### Complexity Analysis of Approach 2

- Time complexity: $O(k E \log (k V))$ where $V$ is the number of flights, $E$ is the
number of cities, and $k$ is the number of stops.  
    - Build adjacent list takes $O(E)$ time;
    - When processing the priority queue,
        - Each node (city) can be added to the priority queue at most $k + 1$ times with
        at most $(k + 1) V$ queuer operations.
        - Each queue operation (push or pop from a heap) takes $O(\log P)$, where $P$ is
        the size of the heap. The size of the heap is bounded by the number of nodes and
        stops, i.e., $P \leq k V$.
        - So the time complexity for priority queue operation is $O(k V \log(k V))$;
        - Edge relaxation takes $O(k E)$ time, since there are $E$ edges in total, each
        edge is relaxed at most $k + 1$ times.
    - The total time complexity is $O(E) + O(k V \log (k V)) + O(k E)$ $=$
    $O(k V \log (k V)) + O(k E)$.
- Space complexity: $O(k V + E)$  
    - The adjacent list stores the graph as a dictionary where each node points to a
    list of neighbors, which takes $O(V + E)$ space;
    - The priority queue is used to track the paths being explored. At any given time,
    the size of the priority queue depends on the number of paths being considered. In
    the worst case, each node can be added to the queue with $k + 1$ different stop
    counts. So the maximum size of the queue is $O(k V)$;  
    So the total space complexity is $O(V + E) + O(k V) = O(k V + E)$.

???- "Detailed Time Complexity Analysis of Priority Queue Operation Part"

    - **Priority queue operations:**
        - The priority queue is used to always expand the node with the current smallest
        cost.
        - Each node (city) can be added to the priority queue at most $k + 1$ times,
        where $k$ is the maximum number of stops allowed.
        - There are at most $O(k V)$ enqueue operations because each node can be visited
        $k + 1$ times, once for each valid stop count.
        - **Heap insertion and extraction** take $O(\log P)$ where $P$ is the size of
        the priority queue. In the worst case, the size of the priority queue can grow
        to $O(k V)$. So each heap operation takes $O(\log (k V))$.
        - Total time on priority queue operations: $O(k V \log (k V))$.
    - **Edge relaxation:**
        - For each node dequeued from the priority queue, all its outgoing edges are
        relaxed (i.e., we check if a cheaper path exists via that edge).
        - Since there are $E$ edges in total, each edge is relaxed at most $k + 1$ times
        (once for each valid stop count of its source node).
        - Total edge relaxations: $O(k E)$
    - **Total time complexity:** $O(k V \log (k V) + k E)$, combining both priority
    queue operations and edge relaxations.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach -  |  $O(k V + k E)$           | $O(k V + E)$ |
Approach - Dijkstra  |  $O(k V \log (k V) + k E)$           | $O(k V + E)$  |

## Test
