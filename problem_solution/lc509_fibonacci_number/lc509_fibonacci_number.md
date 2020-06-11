# LeetCode Problem 509 - Fibonacci Number

## Problem Description
[LeetCode Problem 509](hhttps://leetcode.com/problems/fibonacci-number/): The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,
```
F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), for N > 1.
```
Given N, calculate F(N).

## Analysis
* Clarification:
  - data type?
  - how large the n could be?
* Go through examples
* Solution:
  - Assumption: number >= 0
  - Input/Output: int; int
  - Corner case
  - Algorithm: recursive, iterative, direct
  - Time/space complexity
* Coding
* Test
  - Test base cases: N = 0, 1, or 2
  - Test general cases

## Approach
There are four different methods to compute Fibonacci number:
* Recursive method
* Iterative method
* Closed-form solution using Binet's formula
* Matrix exponential

### Approach 1a - Recursive method
#### Algorithm
Use recursion, F(N) = F(N - 1) + F(N - 2), to compute the Fibonacci number. 
![Fibonacci example](https://leetcode.com/problems/fibonacci-number/Figures/509/fibonacciRecursion5.png)

#### Implementation
```java
public int fib(int N) {
    if (N <= 1)
        return N;
    else
        return fib(N - 1) + fib(N - 2);
}
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(2^n)$.  
The amount of operations needed, for each level of recursion, grows exponentially (1 -> 2 -> 4 -> 8 -> ... -> $2^n$) as the depth approaches N. So time complexity is $\mathcal{O} (1 + 2 + 4 + 8 + \cdots + 2^n) = \mathcal{O}(2^{n+1})$

* **Space complexity**: $\mathcal{O}(n)$  
Space for recursive function call statck. It is proportional to the leve of recursion tree in this case (the **max** size of stack required for the recursion function calls), since each recursion function call only need $\mathcal{O}(1)$ space. This has the potential to be bad in cases that there isn't enough physical memory to handle the increasingly growing stack, leading to a `StackOverflowError`. The [Java docs](https://docs.oracle.com/javase/7/docs/api/java/lang/StackOverflowError.html) have a good explanation of this, describing it as an error that occurs because an application recurses too deeply.

### Approach 1b - Recursive method + Memoization
#### Algorithm
Improve from Approach 1a, use memoization to store the pre-computed answers since many cases will be caculated multiple times.   

[@Frimish](https://leetcode.com/problems/fibonacci-number/discuss/223199/Java-O(2N)-greater-O(N)-greater-O(logN))
> For example, when you calculate fib(N), you have to calculate fib(N - 1) and fib (N - 2), and when you calcuate fib(N - 1), you have to calculate fib(N - 2) and fib (N - 3). Obivously, the fib(N - 2) is calculated repetitively.
Here, we come up with the memoization, the cache, to avoid the repeatitive computation. Once we have computed one status, we store the result into a cache. If the status has been computed before, we get the result from the cache directly. In this way, every status will be computed once.
So the the time complexity is O(N)
The space complexity is O(N)

#### Implementation
```java
class Solution {
    private Integer[] cache;
    
    public int fib(int N) {
        if (N <= 1)
            return N;
        else {
            cache = new Integer[N + 1];
            cache[0] = 0;
            cache[1] = 1;
            return memoize(N);
        }    
    }
    
    private int memoize(int N) {
        if (cache[N] != null)
            return cache[N];
        else {
            cache[N] = memoize(N - 1) + memoize(N - 2);
            return cache[N];
        }
            
    }
}
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(n)$   
Fib(0), Fib(1), ..., Fib(N) all computed once and therefore the complexity is $\mathcal{O}(n)$. 

* **Space complexity**: $\mathcal{O}(n)$  
Need space to account for the **max** size of the stack in memory. The stack keeps track of the recursive function calls.

### Approach 2 - Iterative method

#### Algorithm

#### Implementation
```java
public int fib(int N) {
    if (N <= 1)
        return N;
    
    int fibPrev1 = 1;
    int fibPrev2 = 0;
    int fibCurr = 0; 
    
    for (int k = 2; k <= N; k++) {
        fibCurr = fibPrev1 + fibPrev2;
        fibPrev2 = fibPrev1;
        fibPrev1 = fibCurr;
    }
    
    return fibCurr;
}
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(n)$  
Each number will be visited at least once. The time it takes to do this is directly proportionate to Fibonacci number, n.
* **Space complexity**: $\mathcal{O}(1)$  
This requires 1 unit of Space for the integer $n$ and 3 units of Space to store the computed values for every loop iteration. The amount of space doesn't change so this is constant Space complexity.

### Approach 3 - Closed-form solution

#### Algorithm

#### Implementation
```java
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(1)$  
Constant time complexity since no loops or recursion and the time is simply based on the calcuation using Binet's formula.
* **Space complexity**: $\mathcal{O}(1)$ 
The space used is the sapce needed for store the ratio value.  

### Approach 4 - Matrix exponential

#### Algorithm

#### Implementation
```java
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(\log n)$  
For matrix power calculation, it can achieve time complexity, $\mathcal{O}(\log{n})$, by using [Square and Multiply algorithm](https://en.wikipedia.org/wiki/Exponentiation_by_squaring#Computational_complexity). Since the matrix power $n$ can be represented by a binary number with at most $\log{n}$ bits (i.e., $\log{n}$ steps in Square and Multiply algorithm). 

* **Space complexity**: $\mathcal{O}(\log n)$  
The size of the stack in memory is proportionate to the function calls to matrix power.

### Complexity Summary
|     | Time Complexity | Space Complexity  
| ----- | ----- | ----- |  
| Approach 1 | $\mathcal{O}(n\log n)$ | $\mathcal{O}(n)$ |  
| Approach 2 | $\mathcal{O}(\log n + k)$ | $\mathcal{O}(k)$ | 