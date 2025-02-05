---
tags:
    - Heap
    - Binary Search
---

# LC378. Kth Smallest Element in a Sorted Matrix

## Problem Description

[LeetCode Problem 378](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/description/):
Given an `n x n` `matrix` where each of the rows and columns is sorted in ascending order,
return _the_ `kth` _smallest element in the matrix_.

Note that it is the `kth` smallest element **in the sorted order**, not the `kth`
**distinct** element.

You must find a solution with a memory complexity better than `O(n2)`.

## Clarification

- Each row and column is sorted in ascending order. It doesn't mean 1D array from this
matrix is sorted. For example, `matrix = [[1,5,9],[10,11,13],[12,13,15]]`.
- Find kth smallest element, not the kth distinct element.

## Assumption

-

## Solution

### Approach - Heap

Push matrix elements into max heap with size of k. In the end, the top of the heap is the
`kth` smallest element

=== "Python"
    ```python
    import heapq

    class Solution:
        def kthSmallest(self, matrix: List[List[int]], k: int) -> int:
            max_heap = []

            for row in matrix:
                for element in row:
                    heapq.heappush(max_heap, -element)  # (1)

                    if len(max_heap) > k:
                        heapq.heappop(max_heap)

            return -max_heap[0]  # (2)
    ```

    1. Store negative elements to achieve max heap.
    2. `Kth` smallest element is the top of the max heap. Need to revert negative value
    to normal.

#### Complexity Analysis of Approach 1

- Time complexity: $O(n^2 \log k)$
    - Iterate all $n^2$ elements in the matrix. Each iteration will take at most two
    heap operations. The heap operation takes $O(\log k)$ since the heap size is $k$.
    - So the total time complexity is $O(n^2 \log k)$.
- Space complexity: $O(k)$  
    The heap size is $k$.

### Approach 2 - Binary Search

Since each row and column of the matrix is sorted, we can use binary search on the
**number range** to find the kth smallest number.

- At the beginning, the number range is between the smallest number at the top left
corner of the matrix and the largest number at the bottom lower corner.
- Then find the middle number. The middle number is not necessarily an element in the matrix.
- To decide whether to move left or right, we need to count numbers smaller than or
equal to middle in the matrix.
- When counting, we need to track the smallest number greater than the middle and the
largest number less than or equal to the middle. Use these values to set the new range.

=== "python"
    ```python
    class Solution:
        def kthSmallest(self, matrix: List[List[int]], k: int) -> int:
            left, right = matrix[0][0], matrix[-1][-1]
            while left < right:
                mid = (left + right) // 2
                smaller, larger = matrix[0][0], matrix[-1][-1]

                count_smaller, smaller, larger = self.countLessEqual(
                    matrix, mid, smaller, larger
                )

                if count_smaller == k:
                    return smaller

                if count_smaller < k:
                    left = larger
                else:
                    right = smaller

            return left

        def countLessEqual(
            self, matrix: list[list[int]], mid: int, smaller: int, larger: int
        ) -> tuple[int, int, int]:
            count_smaller, n = 0, len(matrix)

            # (1)
            i_row, i_col = (
                n - 1,
                0,
            )  # (2)
            while i_row >= 0 and i_col < n:
                if matrix[i_row][i_col] > mid:
                    larger = min(
                        larger, matrix[i_row][i_col]
                    )  # (3)
                    i_row -= 1
                else:
                    smaller = max(
                        smaller, matrix[i_row][i_col]
                    )  # (4)
                    count_smaller += i_row + 1
                    i_col += 1

            return count_smaller, smaller, larger
    ```

    1. Use [stair case traversal](../../tips/staircase-traversal.md).
    2. Start from the first column last row (important to choose this!).
    3. Track the smallest number that is larger than the mid.
    4. Track the biggest number less than or equal to the mid.

#### Complexity Analysis of Approach 2

- Time complexity: $O(n \log (\max - \min))$  
    - Binary search between smallest (min) and largest value (max) takes
    $O(\log (\max - \min))$ iterations.
    - Each iteration takes $O(n)$ to count the size of the left half.
    - So the overall time complexity is $O(n \log (\max - \min))$.
- Space complexity: $O(1)$  
    Only fixed number of variables are used for binary search.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach - Heap |  $O(n^2 \log k)$           | $O(k)$ |
Approach - Binary Search  |  $O(n \log (\max - \min))$           | $O(1)$  |

## Test

