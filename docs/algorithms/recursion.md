# Recursion

A recursive algorithm contains the following key components:

1. Base case (i.e., when to stop)
2. Work toward base case
3. Recursive call

## Key points

* On the surface, function calls itself
* Essentially, boil down a big problem to smaller ones (size n depends on size n-1, or n-2, ..., or n/2)
* Implementation:

  * Base case: smallest problem to solve 
  * Recursive rule: how to make the problem smaller

* If recursive function calls are too deep (e.g., n or n^2), there isn't enough physical memory to handle the increasingly growing stack, leading to a `StackOverflowError`. The [Java docs](https://docs.oracle.com/javase/7/docs/api/java/lang/StackOverflowError.html) have a good explanation of this, describing it as an error that occurs because an application recurses too deeply. More over, recursive function call needs special consideration when implementing on an embedded controller which has limited function call stack.

## How Recursion Works Internally:

1. **Function Stack:**

* Each time a function calls itself, a new stack frame is created.
* The current state (local variables, node being processed, etc.) is saved on the stack until the function returns.
* This is why recursion can use a lot of memory if the tree is deep, leading to a space complexity of **O(n)** in the worst case.

2. **Returning to the Caller:**

* After processing the left subtree, the function returns to the previous caller, where it resumes execution (processes the root, then the right subtree).
* Recursion ensures that the execution "goes back" to the previous step in the correct order.
