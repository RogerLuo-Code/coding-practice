# Quick Sort

Quick Sort is a highly efficient sorting algorithm and is based on partitioning of array
into smaller sub-arrays. A large array is divided into two smaller sub-arrays:
the smaller elements and the larger elements.

Quick Sort can be implemented using recursion. The steps are as follows:

1. Choose an element from the array as a **pivot**.
2. **Partitioning**: rearrange the array so that all elements with values less than the
pivot come before it, and all elements with values greater than the pivot come after it.
3. Recursively apply the above steps to the sub-arrays of elements with smaller values
and those with greater values.
4. The base case for the recursion is when the array has one or zero elements, in which
case it is already sorted.

Note that:

- Quick Sort is not a **stable** sort, meaning that the relative order of equal sort
items is not preserved.

## Complexity Analysis

- The average time complexity is $O(n \log n)$, but the worst-case time complexity is
$O(n^2)$, which can occur when the smallest or largest element is always chosen as the pivot.
- The space complexity is $O(\log n)$ due to the recursive stack space.
