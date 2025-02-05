# Staircase Traversal

## Introduction

Staircase traversal is a powerful technique for searching and counting efficiently in a
**row-wise** and **column-wise** sorted matrix. It runs in $O(n)$ time, making it more efficient
than brute-force $O(n^2)$. It is often paired with binary search to further optimize
problems (e.g.,
[kth smallest element in a sorted matrix](../lc-solutions/lc0300-0399/lc0378-kth-smallest-element-in-a-sorted-matrix.md)).

## Why is it Called "Staircase" Traversal?

- Start at the **top-right corner** (or bottom-left corner). This is the key. After each
comparison, it only has **one** direction to go instead of multiple potential directions.
- Move **left** if the current element is **large**.
- Move **down** if the current element is **small**.
- The movement resembles walking down a staircase.

### Example

Given a **sorted matrix**:

$$\begin{bmatrix} 1 & 5 & 9 \\ 10 & 11 & 13 \\ 12 & 13 & 15 \end{bmatrix}$$

Suppose we need to count how many elements are **≤ 10**.

1. Start at **top-right (matrix[0][2] = 9)**.
2. Since **9 ≤ 10**, count all elements in this column up to row 0 → count **3**.
3. Move **down** to (matrix[1][2] = 13).
4. Since **13 > 10**, move **left** to (matrix[1][1] = 11).
5. Since **11 > 10**, move **left** to (matrix[1][0] = 10).
6. Since **10 ≤ 10**, count all elements in this column up to row 1 → count **5**.
7. Move **down** to (matrix[2][0] = 12), but **12 > 10**, so stop.

Total count = **5 elements** ≤ 10.
