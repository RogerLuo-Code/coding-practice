# Recursion

A recursive algorithm contains the following key components:
1. Base case (i.e., when to stop)
2. Work toward base case
3. Recursive call

## Key points
* On the surface, function calls itself
* Essentially, boil down a big problem to smaller ones (size n depends on size n-1, or n-2, ..., or n/2)
* Implementation:
    - Base case: smallest problem to solve  
    - Recursive rule: how to make the problem smaller
* If recursive function calls are too deep (e.g., n or n^2), there isn't enough physical memory to handle the increasingly growing stack, leading to a `StackOverflowError`. The [Java docs](https://docs.oracle.com/javase/7/docs/api/java/lang/StackOverflowError.html) have a good explanation of this, describing it as an error that occurs because an application recurses too deeply. More over, recursive function call needs special consideration when implementing on an embedded controller which has limitied function call stack.