---
tags:
    - Heap
---

# LC1337. The K Weakest Rows in a Matrix

## Problem Description

[LeetCode Problem 1337](https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/description/):
You are given an `m x n` binary matrix `mat` of `1`'s (representing soldiers) and `0`'s
(representing civilians). The soldiers are positioned **in front** of the civilians.
That is, all the `1`'s will appear to the **left** of all the `0`'s in each row.

A row `i` is **weaker** than a row `j` if one of the following is true:

- The number of soldiers in row `i` is less than the number of soldiers in row `j`.
- Both rows have the same number of soldiers and `i < j`.

Return _the indices of the_ `k` _**weakest** rows in the matrix ordered from weakest to strongest_.

## Clarification

- Binary matrix
- All the 1's appear to the left of all the 0's (how to use it?)

## Assumption

-

## Solution

### Approach - Heap

The problem can be solved using max queue to store top k weakest rows. The priority are
determined by two numbers (number of soldiers, row_id). Note that when using `tuple` in
python `heapq`, it will compare the first elements of tuples. If they are equal, it will
compare the second elements to break the tie. If the comparison is customized, we can
create a class with `__lt__` method.

```python
class Item:
    def __init__(self, value, row_id):
        self.value = value
        self.row_id = row_id

    def __lt__(self, other):
        # Compare by value first, then by row id if values are equal
        return (self.value, self.row_id) < (other.value, other.row_id)
```

=== "Python"
    ```python
    import heapq

    class Solution:
        def kWeakestRows(self, mat: List[List[int]], k: int) -> List[int]:
            max_heap = []
            for i_row, row in enumerate(mat):
                n_soldiers = row.count(1)  # (1)
                heapq.heappush(max_heap, Item(-n_soldiers, -i_row))  # (2)
                if len(max_heap) > k:
                    heapq.heappop(max_heap)

            # Essentially, pop items from "max heap".
            # (3)
            indices = [-heapq.heappop(max_heap)[1] for i in range(len(max_heap))]
            return indices[::-1]  # (4)
    ```

    1. Could use binary search to find the index of first `0` and the count is
    `index + 1` based on "all the `1`'s will appear to the **left** of all the `0`'s in
    each row".
    2. Store negative numbers to achieve max heap.
    3. Pop negative numbers from small to large (i.e., positive numbers from high to low).
    4. Reverse the order since it is sorted from largest to smallest.

#### Complexity Analysis of Approach 1

- Time complexity: $O(m n + m\log k)$ or $O(m \log n + m \log k)$
    - Iterate all $m$ rows. Each iteration will
        - count number of `1`s which takes $O(n)$. This could be reduced to $O(\log n)$
        if using binary search.
        - conduct at most two heap operations which takes $O(\log k)$ sine the heap size
        is maintained at $k$.
        - So iterating all rows take $O(m n + m \log k)$ or $O(m \log n + m \log k)$
        using binary search.
    - Popping all items from the heap takes $O(k)$.
    - Reversing the final result of $k$ items takes $O(k)$.
    - So the total time complexity is $O(m n + m \log k) + O(k) + O(k) = O(m n + m \log k)$
    or $O(m \log n + m \log k)$ using binary search.
- Space complexity: $O(k)$  
    The heap size is $k$, taking $O(k)$ space. The final result list takes $O(k)$ space.
    So the total space complexity is $O(k)$.

### Approach 2 - Vertical Iteration

Instead of going through row by row, we can scan column by column to find the k weakest
rows. This method takes advantage of _"all the `1`'s will appear to the **left** of all
the `0`'s in each row"_. It doesn't need to calculate weakest condition. Instead, it
finds the first 0s for each columns. The order of 0s found is the order of k weakest rows.

=== "python"
    ```python
    class Solution:
        def kWeakestRows(self, mat: List[List[int]], k: int) -> List[int]:
            n_rows, n_cols = len(mat), len(mat[0])

            k_weakest_rows = []
            # Scan matrix column by column
            for i_col in range(n_cols):
                for j_row in range(n_rows):
                    if len(k_weakest_rows) == k:
                        return k_weakest_rows
                    # (1)
                    if mat[j_row][i_col] == 0 and (
                        i_col == 0 or mat[j_row][i_col - 1] == 1
                    ):
                        k_weakest_rows.append(j_row)

            # (2)
            i_row = 0
            while len(k_weakest_rows) < k:
                # (3)
                if mat[i_row][-1] == 1:
                    k_weakest_rows.append(i_row)
                i_row += 1

            return k_weakest_rows
    ```

    1. Check whether it is the first 0 in the corresponding row, i.e., left is 1 and
    current is 0, `[..., 1, 1, 0, 0, ...]`.
    2. Edge cases: number of rows with 0s < k, indicating some of the first k weakest
    rows are entirely 1s.
    3. If last element in the row is 1, indicating the whole row is 1s, which is not
    included yet.

#### Complexity Analysis of Approach 2

- Time complexity: $O(m n)$  
    - Scanning matrix column by column to find k first 0s, taking $O(m n)$ time.
    - For edge cases, it takes at most $O(k)$ iterations to find the rest of weakest rows.
    - So the total time complexity is $O(m n)$.
- Space complexity: $O(k)$  
    The final result list store $k$ indices.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach 1 - Heap  |  $O(m \log n + m \log k)$           | $O(k)$ |
Approach 2 - Vertical Iteration  |  $O(m n)$           | $O(k)$  |

## Test
