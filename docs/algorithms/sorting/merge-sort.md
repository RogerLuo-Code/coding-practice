# Merge Sort

Merge Sort is a divide-and-conquer algorithm to sort an array. It is based on the
concept of merging two sorted arrays into a single sorted array.

It is particularly useful for sorting linked lists and large datasets that do not fit
into memory.

The algorithm works as follows:

1. **Divide**: Split the array into two halves.
2. **Conquer**: Recursively sort the two halves.
3. **Merge**: Merge the two sorted halves into a single sorted array.
4. **Base Case**: If the array has one or zero elements, it is already sorted.

Note that

- **Stability**: Merge Sort is a stable sort, meaning that it preserves the relative
order of equal elements.
- **In-Place**: Merge Sort is not an in-place sort, as it requires **additional space**
for the temporary arrays used during the merge process.

## Complexity Analysis

- **Time Complexity**: The time complexity of Merge Sort is $O(n \log n)$ in all cases
(best, average, and worst).
- **Space Complexity**: The space complexity is $O(n)$ due to the temporary arrays used
for merging.

## Applications

- Merge Sort is particularly useful for sorting linked lists and large datasets that do
not fit into memory. It is also a good choice for external sorting, where the data is
too large to fit into memory and must be sorted using external storage (like disk drives).
