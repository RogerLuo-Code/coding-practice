# Binary Search Algorithm

## Introduction

Binary search is a search algorithm that finds the position of a target value within a
**sorted** array.

Worst-case performance: $O(\log n)$
Best-case performance: $O(1)$
Average performance: $O(\log n)$
Worst-case space complexity: $O(1)$

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

## References

- [wiki - binary search algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm)
- [LeetCode answer on forgetting the binary search pattern](https://leetcode.com/problems/search-insert-position/solutions/249092/Come-on-forget-the-binary-search-patterntemplate!-Try-understand-it/)
- [Python bisect implementation](https://github.com/python/cpython/blob/3.9/Lib/bisect.py#L15-L35)
