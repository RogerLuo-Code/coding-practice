---
tags:
    - Recursion
    - Binary Tree
    - Bit Manipulation
---

# 779. K-th Symbol in Grammar

## Problem Description

[LeetCode Problem 779](https://leetcode.com/problems/k-th-symbol-in-grammar/description/):
We build a table of `n` rows (**1-indexed**). We start by writing `0` in the `1st` row.
Now in every subsequent row, we look at the previous row and replace each occurrence of
`0` with `01`, and each occurrence of `1` with `10`.

- For example, for `n = 3`, the `1st` row is `0`, the `2nd` row is `01`, and the `3rd`
row is `0110`.

Given two integer `n` and `k`, return the `kth` (**1-indexed**) symbol in the `nth` row
of a table of `n` rows.

## Clarification

-

## Assumption

-

## Solution

### Approach 1: Recursion Based on Binary Tree Pattern

We can view row creation as a binary tree creation. It will generate a perfect binary
tree with all levels completely filled.

```text
Row1                          0
                          /       \
Row2                     0          1
                       /   \      /    \
Row3                  0     1     1      0
                     / \    / \   / \   / \
Row4                0  1   1   0  1  0  0  1

Index(for Row 4)->  1  2   3   4  5  6  7  8
```

Based on explanations from [@repititionismastery](https://leetcode.com/problems/k-th-symbol-in-grammar/):

- The **parent** of `kth` index in `nth` row is:
    - `k/2` index in the `(n-1)th` row when `k` is **even**.
    - `(k + 1)/2` index in the `(n-1)th` row when `k` is **odd**.
- The **value** of `kth` index in `nth` row is:
    - **flipped** (reversed) value of the parent.
    - **same** value as the parent.

=== "Python"
    ```python
    class Solution:
        def kthGrammar(self, n: int, k: int) -> int:
            # Base case
            if n == 1:
                return 0

            if k % 2 == 0:
                # If k is in the 2nd half, it is the reversed value of the first half in previous row
                return 1 - self.kthGrammar(n - 1, k // 2)
            else:
                return self.kthGrammar(n - 1, (k + 1) // 2)
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  Each recursion call will reduce $n$ by 1 until reaching 1 and takes $O(1)$ for
  calculation. so the time complexity is $O(n)$.
- Space complexity: $O(n)$  
  The recursive function calls $n$ times and the function call stack takes $O(n)$ space.

### Approach 2: Recursion Based on Observation

This solution is based on the idea from [@Mohamed Mamdouh](https://leetcode.com/problems/k-th-symbol-in-grammar/solutions/4205730/100-easy-iterative-approach-explained-intuition/).

```text
Row1: 0
Row2: 01
Row3: 0110
Row4: 01101001
Row5: 0110100110010110
```

```text
Row1: 0
Row2: 0 | 1
Row3: 01 | 10
Row4: 0110 | 1001
Row5: 01101001 | 10010110
```

Observe from rows numbers, we can find:

- **Row-to-row relationship**: the first half of the current row is the same as previous
row.
- **Within-row relationship**: the 2nd half is the reverse of the 1st half (i.e., previous
row from row-to-row relationship).

**Note**: To flip $x$ where $x$ is 0 or 1, we can perform $x' = 1 - x$.

=== "python"
    ```python
    class Solution:
        def kthGrammar(self, n: int, k: int) -> int:
            # Base case
            if n == 1:
                return 0

            mid = (1 << (n - 1)) // 2

            if k > mid:
                # If k is in the 2nd half, it is the reversed value of the first half in previous row
                return 1 - self.kthGrammar(n - 1, k - mid)
            else:
                # Same as the previous row
                return self.kthGrammar(n - 1, k)
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  Each recursion call will reduce $n$ by 1 until reaching 1 and takes $O(1)$ for
  calculation. so the time complexity is $O(n)$.
- Space complexity: $O(n)$  
  The recursive function calls $n$ times and the function call stack takes $O(n)$ space.

### Approach 3: Iteration Based on Observation

Based on the previous observation, we can also use the iteration method to solve the
problem.

=== "python"
    ```python
    class Solution:
        def kthGrammar(self, n: int, k: int) -> int:
            are_values_same = True  # (1)

            n_total = 1 << (n - 1)  # (2)

            while n_total > 1:
                n_total //= 2

                # If k is in the 2nd half, change it to the fist half an toggle the flag
                if k > n_total:
                    k -= n_total
                    are_values_same = not are_values_same

            return 0 if are_values_same else 1
    ```

    1. Initialize a flag to track if kth value is the same as the first element. By default, assume no flip.
    2. Number of elements in the nth row, which is $2^{n - 1}$.

#### Complexity Analysis of Approach 3

- Time complexity: $O(1)$  
  The while loop starts with $2^n$ elements and each iteration reduce the number of
  elements by half. So the time complexity is $O(\log (2^n)) = O(n)$.
- Space complexity: $O(1)$  
  Use limited variables.

### Approach 4: Bit Count

From previous observation, we can see that we start with $0$ and flip it $x$ number of
times for `kth` element in the `nth` row. Then we need to determine the number of flips required.

In previous approach, a flip happens at each subtraction. `k` is reduced until reaching
1,

$$k - 2^m - 2^k - 2^j - \cdots = 1$$

Therefore, the number of flips
is equal to the number of subtractions performed.

Re-array above equation, we get $k - 1 = 2^m + 2^k + 2^j$ which is the binary
representation of $k - 1$. Determining the number of flips becomes count number of 1-bits
in the binary representation of `k - 1`.

=== "python"
    ```python
    class Solution:
        def kthGrammar(self, n: int, k: int) -> int:
            count = bin(k - 1).count('1')
            return 0 if count % 2 == 0 else 1
    ```

#### Complexity Analysis of Approach 4

- Time complexity: $O(\log k)$  
    - Convert the number to binary takes $O(\log k)$.
    - Count the 1-bits takes $O(\log k)$ for $\log k$ bits.
    - The overall time complexity is $O(\log k)$.
- Space complexity: $O(1)$  
  Only use limited variable like `count`.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach                                    | Time Complexity | Space Complexity
--------------------------------------------|-----------------|-----------------
Approach - Recursion on Binary Tree Pattern | $O(n)$          | $O(n)$
Approach - Recursion on Observation         | $O(n)$          | $O(n)$
Approach - Iteration on Observation         | $O(n)$          | $O(1)$
Approach - Bit Count                        | $O(\log k)$     | $O(1)$

## Test
