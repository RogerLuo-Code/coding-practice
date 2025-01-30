# The Top K Problem

Use the Heap data structure to obtain top K's largest or smallest elements.

## Approach 1 - Heap with All Elements

### Top K Largest Elements Using Approach 1

1. Construct a **Max** Heap.
2. Add all elements into the Max Heap (heapify).
3. Traverse and pop the top element (max value) and store the value into the result array.
4. Repeat step 3 $K$ times until finding K largest elements.

Note that

- The result array stores $K$ largest elements.
- The element for the $K$th pop is the K-th largest element.

### Top K Smallest Elements Using Approach 1

1. Construct a **Min** Heap.
2. Add all elements into the Min Heap (heapify).
3. Traverse and pop the top element (min value) and store the value into the result array.
4. Repeat step 3 until finding the K smallest elements.

Note that

- The result array stores $K$ smallest elements.
- The element for the $K$th pop is the K-th smallest element.

### Complexity Analysis of Approach 1

- Time complexity: $O(N + K \log N)$  
    - Constructing a max heap by heapify an array (step 2) takes $O(N)$ time.
    - Pop element from the heap takes $O(\log N)$ time and this process repeat $K$ times.
    - So the total time complexity is $O(N) + O(K \log N) = O(N + K \log N)$.
- Space complexity: $O(N)$  
    The heap stores all $N$ elements.

## Approach 2 - Heap with K Elements

### Top K Largest Elements Using Approach 2

1. Construct a **Min** Heap with size $K$.
2. Add elements to the Min Heap one by one until there are $K$ elements.
3. Compare the new element with the min element of the heap:
    - If new element <= min, proceed to the next element.
    - If new element > min, pop the min element from the heap and add the new element.
    The new element (larger) has a higher chance to be the top K largest elements.
4. Repeat step 2 and 3 until all elements have been processed.

Note that

- The $K$ elements in the Min Heap are the $K$ largest elements.
- The top element in the Min Heap is the $K$-th largest element.

### Top K Smallest Elements Using Approach 2

1. Construct a **Max** Heap with size $K$.
2. Add elements to the Max Heap one by one until there are $K$ elements (or heapify the
first K elements).
3. Compare the new element with the max element of the heap:
    - If new element >= max, proceed to the next element.
    - If new element < max, pop the max element from the heap and add the new element.
4. Repeat step 2 and 3 until all elements have been processed.

Note that

- The $K$ elements in the Max Heap are the $K$ smallest elements.
- The top element in the Max Heap is the $K$-th smallest element.

### Complexity Analysis of Approach 2

- Time complexity: $O(N \log K)$  
    - Adding $K$ items one by one to the heap takes takes $O(K \log K)$. Yet, heapifying
    the first $K$ items takes $O(K)$.
    - Popping element from the heap takes $O(\log K)$ since the heap size is $K$. In the
    worst case, it may pop $N - K$ times. So the time complexity is $O((N - K) \log K)$.
    - So the total time complexity is 
        - $O(K \log K) + O((N - K) \log K) = O(N \log K)$.
        - or $O(K) + O((N - K) \log K) = O(K + (N - K) \log K)$ with heapify.
- Space complexity: $O(K)$  
    The heap stores at most $K$ elements.

## Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach    | Time Complexity   | Space Complexity |
------------| ---------------   | ---------------- |
Approach 1 - All Elements  |  $O(N + K \log N)$           | $O(N)$ |
Approach 2 - $K$ Elements  |  $O(N \log K)$           | $O(K)$  |
