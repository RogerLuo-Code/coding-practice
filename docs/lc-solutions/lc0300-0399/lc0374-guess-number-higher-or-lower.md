---
tags:
    - Binary Search
---

# LC374. Guess Number Higher or Lower
## Problem Description
[LeetCode Problem 374](https://leetcode.com/problems/guess-number-higher-or-lower/): We are playing the Guess Game. The game is as follows:

I pick a number from `1` to `n`. You have to guess which number I picked.

Every time you guess wrong, I will tell you whether the number I picked is higher or lower than your guess.

You call a pre-defined API `int guess(int num)`, which returns three possible results:

- `-1`: Your guess is higher than the number I picked (i.e. `num > pick`).
- `1`: Your guess is lower than the number I picked (i.e. `num < pick`).
- `0`: your guess is equal to the number I picked (i.e. `num == pick`).

Return _the number that I picked_.

## Clarification
- picked number is between 1 to n number
- call guess to return guess results

## Assumption

## Solution
### Approach - Binary Search
Essentially, the problem is to find the target in an array of 1 to n (sorted). We can use binary search to find the picked number by using the guess results from the api function.

=== "Python"
    ```python
    class Solution:
        def guessNumber(self, n: int) -> int:
            left, right = 1, n

            while left <= right:
                mid = (left + right) // 2

                res = guess(mid)
                if res == 0:
                    return mid
                elif res == -1:
                    right = mid - 1
                else:
                    left = mid + 1

            return -1  # if not found
    ```

#### Complexity Analysis
* Time complexity: $O(\log n)$  
	Since using binary search, the time complexity is $O(\log n)$.
* Space complexity: $O(1)$  
	Just use two index variables. 

## Test