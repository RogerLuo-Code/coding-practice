---
tags:
- Binary Search
---

# LC1011. Capacity to Ship Packages Within D Days
## Problem Description
[LeetCode Problem 1011](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days): A conveyor belt has packages that must be shipped from one port to another within `days` days.

The `ith` package on the conveyor belt has a weight of `weights[i]`. Each day, we load the ship with packages on the conveyor belt (in the order given by `weights`). We may not load more weight than the maximum weight capacity of the ship.

Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within `days`days.

## Clarification

## Assumption

## Solution
### Approach - Binary Search
The problem is to find the minimum capacity of the ship so all the packages can be shipped within `days`. The search space of capacity is `[max(weights), sum(weights)]`.

- If a given capacity `c_k` meets the requirement, all capacity > `c_k` also meets the requirement
- If a give capacity `c_k` doesn't meet the requirement, all capacity < `c_k` can't meet the requirement

Base on above mentioned conditions, we can use binary search to speed up the search.

=== "Python"
    ```python
    class Solution:
        def shipWithinDays(self, weights: List[int], days: int) -> int:
            left, right = max(weights), sum(weights)

            while left < right:
                mid = (left + right) // 2
                if self.canShipWithinDays(weights, days, mid):
                    right = mid
                else:
                    left = mid + 1

            return left

        def canShipWithinDays(self, weights: List[int], days: int, capacity: int) -> bool:
            daysNeeded = 1
            wSum = 0
            for w in weights:
                wSum += w
                if wSum > capacity:
                    daysNeeded += 1
                    wSum = w

            return daysNeeded <= days
    ```

#### Complexity Analysis
* Time complexity: $O(n \log s)$ where $n$ is the number of weights, $s$ is the sum of all weights  
    - It takes $O(n)$ time to iterate through `weights` to compute max weight and total weights
    - During the binary search,  
        - search range is `[max(weights), sum(weights)]`. In the worst case, it is `sum(weights)`. So it takes $O(\log s)$ to do binary search.
        - each step, it takes $O(n)$ to check whether it is feasible
        - So time complexity of whole binary search is $O(n \log s)$
* Space complexity: $O(1)$  
Only define a few local variables.

## Test