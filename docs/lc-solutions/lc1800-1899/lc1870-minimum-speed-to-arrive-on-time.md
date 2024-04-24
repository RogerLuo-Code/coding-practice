---
tags:
- Binary Search
---

# LC1870. Minimum Speed to Arrive on Time
## Problem Description
[LeetCode Problem 1870](https://leetcode.com/problems/minimum-speed-to-arrive-on-time): You are given a floating-point number `hour`, representing the amount of time you have to reach the office. To commute to the office, you must take `n` trains in sequential order. You are also given an integer array `dist` of length `n`, where `dist[i]`describes the distance (in kilometers) of the `ith` train ride.

Each train can only depart at an integer hour, so you may need to wait in between each train ride.

- For example, if the `1st` train ride takes `1.5` hours, you must wait for an additional `0.5` hours before you can depart on the `2nd` train ride at the 2 hour mark.

Return _the **minimum positive integer** speed **(in kilometers per hour)** that all the trains must travel at for you to reach the office on time, or_ `-1` _if it is impossible to be on time_.

Tests are generated such that the answer will not exceed `107` and `hour` will have **at most two digits after the decimal point**.

## Clarification
- `hour`: floating-point
- integer `dist`
- return minimum positive integer speed

## Assumption

## Solution
### Approach - Binary Search
Since each train will depart at an integer hour, when computing actual hours, for all the rides except the last one, the time of train ride need to round off to the next integer (`ceil`). The last ride can end at a decimal with a float value. 

- If speed `s` meets the time requirement, no need to search speed > `s` since they all will meet the requirement
- Otherwise, no need to search speed < `s`, since they won't meet the requirement either.

Based on these properties, we can use binary search to speed up searching. 

=== "Python"
    ```python
    class Solution:
        def minSpeedOnTime(self, dist: List[int], hour: float) -> int:
            ans = -1
            minSpeed, maxSpeed = 1, 10**7

            while minSpeed <= maxSpeed:
                midSpeed = (minSpeed + maxSpeed) // 2
                if self.canReachInTime(dist, hour, midSpeed):
                    ans = midSpeed
                    maxSpeed = midSpeed - 1  # (1)
                else:
                    minSpeed = midSpeed + 1

            return ans

        def canReachInTime(self, dist: List[int], hour: float, speed: int) -> bool:
            hour_actual = 0
            for idx in range(len(dist) - 1):
                hour_actual += (dist[idx] + speed - 1) // speed  # (2)

            hour_actual += dist[-1] / speed  # (3)
            return hour_actual <= hour
    ```

    1. Can use `-1` since the answer is stored in the step above. If no `ans = midSpeed`, can't add `-1`
    2. Integer hour with ceiling calculation since each train departs at an integer hour
    3. Last one is floating calculation


#### Complexity Analysis
* Time complexity: $O(n \log k)$ where $n$ is the number of rides and $k$ is the size of the search space, i.e., $10^7$.
After each iteration, the search space, $k$ ($10^7$), is reduced by half. Within each iteration, it needs to go through the array to find the ride time, which takes $O(n)$ time. Therefore, the total time complexity is $O(n \log k)$.   
* Space complexity: $O(1)$  
No extra space is required other that limited number of variables.

## Test