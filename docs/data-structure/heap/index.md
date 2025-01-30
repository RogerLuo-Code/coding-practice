---
tags:
    - Data Structure
---

# Heap

## Introduction

Heap is a tree-based data structure that satisfies the heap property:

- The value of each node must be no greater than (or no less than) the value of its
child nodes.

Heap is not a [priority queue](../../abstract-data-type/priority-queue.md) but a way to
implement it.

There are two kinds of heaps:

- **Max Heap**: Each node in the Heap has a value no less than its child nodes.
Therefore, the top element (root node) has the largest value in the Heap.
- **Min Heap**:Each node in the Heap has a value no larger than its child nodes.
Therefore, the top element (root node) has the smallest value in the Heap.

## Common Operations

- `heapify`: create a heap out of given array of elements.
- `push`: Add an element into the heap.
- `peek`: find a maximum item of a max-heap, or a minimum item of a min-heap.
- `pop`: returns the ono of maximum value from a max heap (or minimum value from a min)
and remove it from the heap.
- `size`: return the number of items in the heap.

Usual space an time complexity:

|Heap method|Time complexity|Space complexity|
|---|---|---|
|`heapify`|$O(N)$|$O(N)$|
|`push`|$O(\log⁡N)$|$O(1)$|
|`peak`|$O(1)$|$O(1)$|
|`pop`|$O(\log⁡N)$|$O(1)$|
|`size`|$O(1)$|$O(1)$|

$N$ is the number of elements in the heap.

???+ "Creating a Heap from an array"
    - Create an empty heap and insert elements one by one takes $O(N \log N) time. It
    goes through $N$ elements and insert each of them takes $O(\log N)$ time.
    - `Heapify` directly takes $O(N)$ time. It considers an array as a tree and swap
    values to form a heap. The max number of swaps is $N$.

## Variants

- Binary heap
- Min-Max heap
- Fibonacci heap
- ...

## Built-in Libraries

Python provides `heapq` for min heap.

## Applications of Heap

- [Heap Sort](../../algorithms/sorting/heap-sort.md)
- [The Top-K problem](top-k-problem.md)
- [The K-th element](kth-element.md)

## References

- [Wiki - Heap](https://en.wikipedia.org/wiki/Heap_(data_structure))