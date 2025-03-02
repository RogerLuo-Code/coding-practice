# Recursion

A recursive algorithm contains the following key components:

1. Base case (i.e., when to stop)
2. Work toward base case
3. Recursive call

## Key points

- On the surface, function calls itself
- Essentially, boil down a big problem to smaller ones (size n depends on size n-1, or
n-2, ..., or n/2)
- Implementation:

    - Base case: smallest problem to solve
    - Recursive rule: how to make the problem smaller

- If recursive function calls are too deep (e.g., n or n^2), there isn't enough physical
memory to handle the increasingly growing stack, leading to a `StackOverflowError`. The
[Java docs](https://docs.oracle.com/javase/7/docs/api/java/lang/StackOverflowError.html)
have a good explanation of this, describing it as an error that occurs because an
application recurses too deeply. More over, recursive function call needs special
consideration when implementing on an embedded controller which has limited function
call stack.

## How Recursion Works Internally

- **Function Stack:**
    - Each time a function calls itself, a new stack frame is created.
    - The current state (local variables, node being processed, etc.) is saved on the stack
    until the function returns.
    - This is why recursion can use a lot of memory if the tree is deep, leading to a space
    complexity of **O(n)** in the worst case.

- **Returning to the Caller:**
    - After processing the left subtree, the function returns to the previous caller, where
    it resumes execution (processes the root, then the right subtree).
    - Recursion ensures that the execution "goes back" to the previous step in the
    correct order.

## Applications

### Solve Tree Problem Recursively

#### Top-Down Solution

**Top-down** means that in each recursive call, we will visit the node first to
come up with some values, and pass these values to its children when calling the
function recursively.

```pseudocode
top_down(root, params):
    return specific value for null node  # base case
    update the answer if needed
    left_ans = top_down(root.left, left_params)
    right_ans = top+down(root.right, right_params)
    return the answer if needed
```

Before trying the top-down recursive solution, ask the following two questions:

1. Can you determine some parameters to help the node know its answer?
2. Can you use these parameters and the value of the node itself to determine what
should be the parameters passed to its children.

#### Bottom-Up Solution

**Bottom-up** means that in each recursive call, we will first call the function
recursively for all the children nodes and then come up with the answer according to the
returned values and the value of the current node itself.

```pseudocode
bottom_up(root):
    return specific value for null node
    left_ans = bottom_up(root.left)
    right_ans = bottom_up(root.right)
    calculate answer based on left_ans, right_ans, root.val
    return answers
```

Before trying the bottom-up recursive solution, ask the following question:

- If you know the answer of a node's children, can you calculate the answer of that node?
