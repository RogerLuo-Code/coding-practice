# Binary Search Algorithm

## Introduction

Binary search is a search algorithm that finds the position of a target value within a
**sorted** array.

Worst-case performance: $O(\log n)$
Best-case performance: $O(1)$
Average performance: $O(\log n)$
Worst-case space complexity: $O(1)$

## General Steps

Answering the following questions before coding:

- What is the target item, value, and type? An index, between two indices, or something else.
- What bounds must the target item be within? It's usually easy to use inclusive bounds,
using `low` to represent the lowest possible position of the target and `high` to be the
highest possible position.
- What can we conclude when `isReachable(mid)` returns true ("yes")? Don't accidentally
exclude the target.
- What can we conclude when `isReachable(mid)` returns false ("no")? Don't accidentally
exclude the target.
- How do we know when we've found the target item?
- Which calculation for mid should we use?

## Tips

- How to determine the while loop condition, `l < r`, `l <= r`, or `l < r - 1`?  
  Choose the condition that will not infinity while loop. Check what would happen when
  only two elements and 1 element left in the array. For example,

  ```text
  x  x  x  5   7  x  x  x
          l/m  r
  ```

  We can see what `l = m + 1` and `r = m` can both shrink the size by 1. When just one
  element left,

  ```text
  x  x  x  5    x  x  x  x
          l/m/r
  ```

  `r = m` can't shrink the size any more.

- How to update `mid`?
    - If using `hi = mid - 1`, use the higher midpoint, `mid = (lo + hi + 1) / 2`.
    - If using `lo = mid + 1`, use the lower midpoint, `mid = (lo + hi) / 2`.
    - If using above both, then use either lower or higher midpoint


## References

- [wiki - binary search algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm)
- [LeetCode answer on forgetting the binary search pattern](https://leetcode.com/problems/search-insert-position/solutions/249092/Come-on-forget-the-binary-search-patterntemplate!-Try-understand-it/)
- [Python bisect implementation](https://github.com/python/cpython/blob/3.9/Lib/bisect.py#L15-L35)
