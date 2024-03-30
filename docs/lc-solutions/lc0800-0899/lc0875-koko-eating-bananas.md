---
tags:
- Binary Search
---

# LC875. Koko Eating Bananas
## Problem Description
[LeetCode Problem 875](https://leetcode.com/problems/koko-eating-bananas): Koko loves to eat bananas. There are `n` piles of bananas, the `ith` pile has `piles[i]` bananas. The guards have gone and will come back in `h` hours.

Koko can decide her bananas-per-hour eating speed of `k`. Each hour, she chooses some pile of bananas and eats `k` bananas from that pile. If the pile has less than `k` bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return _the minimum integer_ `k` _such that she can eat all the bananas within_ `h` _hours_.

## Clarification

## Assumption

## Solution
### Approach - Binary Search
The difficult part of this problem is how to convert it into classic binary search problem. Based on the problem description, we can define the search space between 1 and the max number of bananas M on a pile, `[1, M]`. Each value in the search space has a status associated with it (let `N` denotes not finish eating and `Y` denotes finish eating). Then we have `[N, N, ···, N, Y, ···,Y]`. For a given k,

- If Koko can finish eating, no need to check k+1, k+2,..., since Koko can finish eating with bigger numbers.
- If Koko can’t finish eating, no need to check k − 1, k − 2, ... since Koko can NOT finish eating with smaller numbers.

Based on this property, we can use binary search to reduce search space after each iteration until only one element left. Assume there always existing K such that Koko can finish eating within H hours. We also need to create help functions on checking whether Koko can finish eating.

=== "Python"
    ```python
    class Solution:
        def minEatingSpeed(self, piles: List[int], h: int) -> int:
            left, right = 1, max(piles)
            while left < right:
                mid = (left + right) // 2

                if self.canEatAll(piles, h, mid):
                    right = mid
                else:
                    left = mid + 1
            return left

        def canEatAll(self, piles: List[int], h: int, k: int) -> bool:
            actual_hour = 0
            for pile in piles:
                if pile % k == 0:
                    actual_hour += pile // k
                else:
                    actual_hour += pile // k + 1
            return actual_hour <= h
    ```

=== "C++"
    ```c++
    class Solution {
    public:
        int minEatingSpeed(vector<int>& piles, int H) {
            if (piles.empty() || H < piles.size()) return -1;

            int left = 1; // eat at least one banana
            int right = getMaxPile(piles);
            int mid;

            while (left < right) {
                mid = left + (right - left)/2;

                if (canEatAll(piles, H, mid)) {
                    right = mid;    // continue to the left to find the smaller k since Koko wants to east as slow as possible
                }
                else {
                    left = mid + 1;
                }
            }

            // left == right
            return left;  //assumption: there will be at least one solution
        }

    private:
        bool canEatAll(vector<int>& piles, int H, int mid) {
            int hour = 0;

            for (int pile:piles) {
                hour += pile/mid + ((pile%mid == 0) ? 0 : 1); // round up
            }

            return (hour <= H) ? true : false;
        }

        int getMaxPile(vector<int>& piles) {
            int maxPile = piles[0];

            for (int pile:piles) {
                if (pile > maxPile) maxPile = pile;
            }

            return maxPile;
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n \log m)$ where $n$ is the number of piles and $m$ is the maximum number of bananas in a pile  
It takes $O(\log m)$ to find `k` in the search space `[1, m]` using binary search. For each step, it takes $O(n)$ to check all piles to see whether Koko can finishing eating. Additionally, it takes $O(n)$ to find the maximum number of bananas in a pile. So the total time complexity is $O(n \log m) = O(n \log m) + O(n)$.  
* Space complexity: $O(1)$  
Only use several variables for binary search and computation.

## Test