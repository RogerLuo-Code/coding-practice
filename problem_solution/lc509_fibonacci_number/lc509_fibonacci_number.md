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
Need space to account for the **max** size of the stack in memory (number of recursive function calls is proportional to n, $\mathcal{O}(n)$) and the size of cache is proportional to N ($\mathcal{O}(n)$). Therefore, space complexity $\mathcal{O}(n) + \mathcal{O}(n) \rightarrow \mathcal{O}(n)$ 

### Approach 1c - Recursive method + memoization (Fast)

#### Algorithm
Based on [Dijkstar's notes](http://www.cs.utexas.edu/users/EWD/ewd06xx/EWD654.PDF), there is [a quicker method](http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fibonacci/fibFormula.html) to compute Fibonacci number $F(2n-1) = F(n-1)^2 + F(n)^2$ and $F(2n) = (2 F(n-1) + F(n) ) F(n)$

#### Implementation
```java
class Solution {
    private Integer[] cache;
    
    public int fib(int N) {
        if (N <= 1)
            return N;
        else {
            // int nCache = (int)(Math.log(N) / Math.log(2));
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
            if (N % 2 == 0) {
                int m = N/2;
                cache[N] = (2*memoize(m - 1) + memoize(m))*memoize(m);
                return cache[N];
            }
            else {
                int m = (N + 1)/2;
                cache[N] = memoize(m - 1)*memoize(m - 1) + memoize(m)*memoize(m);
                return cache[N];
            }
        }
    }
}
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(\log n)$  
For Fib(N), it needs to compute $2 \log n$ values. For example, F(1000) needs F(500) and F(499); F(500) and F(499) needs F(250) and F(249); F(250) and F(249) needs F(124) and F(125); ...; and so on. The time complexity is $\mathcal{O}(\log n)$.

* **Space complexity**: $\mathcal{O}(n)$  
Need space to account for the **max** size of the stack in memory (number of recursive function calls is proportional to n, $\mathcal{O}(\log n)$) and the size of cache is proportional to N ($\mathcal{O}(n)$). Therefore, space complexity $\mathcal{O}(\log n) + \mathcal{O}(n) \rightarrow \mathcal{O}(n)$ 

### Approach 2 - Iterative method

#### Algorithm
Store two previous Fibonacci numbers and update them as iterating to N. Using equation: fib(N) = fib(N - 1) + fib(N - 2)

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

### Approach 3a - Matrix exponentiation recursive

#### Algorithm
The nth Fibonacci number can be obtained from the following matrix equation:
$\begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^n = \begin{bmatrix} f_{n+1} & f_n \\ f_n & f_{n-1} \end{bmatrix}$. 


#### Implementation
```java
public class Fibonacci {
    public int fib(int N) {
        // Using matrix exponentiation
        // [[1, 1], [1, 0]]^n = [[fib(n+1), fib(n)], [fib(n), fib(n-1)]]
        if (N <= 1)
            return N;
        
        int[][] a = new int[][]{{1, 1}, {1, 0}};
        int[][] result = matrixPow(a, N);
        
        return result[1][0];
        
    }

    private int[][] matrixPow(int[][] a, int n) {
        // assume n > 1
        if (a.length != a[0].length)
            return new int[0][];
        
        // Base case
        if (n == 1) {
            return a;    
        }

        int[][] half = matrixPow(a, n/2);
        if (n%2 == 0)
            return matrixMultiply(half, half);
        else
            return matrixMultiply(matrixMultiply(half, half), a);
    }

    private int[][] matrixMultiply(int[][] a, int[][] b) {
        if (a == null || a.length == 0 || b == null || b.length == 0)
            return new int[0][];

        int aRow = a.length;
        int aCol = a[0].length;
        int bRow = b.length;
        int bCol = b[0].length;
        int[][] result = new int[aRow][bCol];

        // Requirement for matrix multiplication
        if (aCol != bRow)
            return new int[0][];

        // Matrix multiplication element by element    
        for (int i = 0; i < aRow; i++) {
            for (int j = 0; j < bCol; j++) {
                for (int k = 0; k < aCol; k++) {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return result;
    }    
}
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(\log n)$  
For matrix power calculation, it can achieve time complexity, $\mathcal{O}(\log{n})$, by using [Square and Multiply algorithm](https://en.wikipedia.org/wiki/Exponentiation_by_squaring#Computational_complexity). Since the matrix power $n$ can be represented by a binary number with at most $\log{n}$ bits (i.e., $\log{n}$ steps in Square and Multiply algorithm). 

* **Space complexity**: $\mathcal{O}(\log n)$  
The size of the stack in memory is proportionate to the function calls to matrix power plus the memory used to compute the matrices multiplication.

### Approach 3b - Matrix exponentiation iterative

#### Algorithm
The nth Fibonacci number can be obtained from the following matrix equation:
$\begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^n = \begin{bmatrix} f_{n+1} & f_n \\ f_n & f_{n-1} \end{bmatrix}$. 


#### Implementation
```java
class Solution {
    public int fib(int N) {
        if (N <= 1)
            return N;
        
        int[][] a = new int[][]{{1, 1}, {1, 0}};
        int[][] result = matrixPowIterative(a, N);
        
        return result[1][0]; 
    }
    
    private int[][] matrixPowIterative(int[][] a, int n) {
        // assume n > 1
        if (a.length != a[0].length)
            return new int[0][];

        int aRow = a.length;
        int[][] result = new int[aRow][aRow];
        for (int i = 0; i < aRow; i++){
            result[i][i] = 1;
        }
        
        if (n == 0)
            return result;

        if (n == 1)
            return a;

        for (; n > 0; n = n/2){
            if ((n & 0x1) == 1)
                // result = matrixMultiply(result, a);
                multiply(result, a);

            // a = matrixMultiply(a, a);
            multiply(a, a);
        }
        
        return result;
    }

    private int[][] matrixMultiply(int[][] a, int[][] b) {
        if (a == null || a.length == 0 || b == null || b.length == 0)
            return new int[0][];

        int aRow = a.length;
        int aCol = a[0].length;
        int bRow = b.length;
        int bCol = b[0].length;
        int[][] result = new int[aRow][bCol];

        // Requirement for matrix multiplication
        if (aCol != bRow)
            return new int[0][];

        // Matrix multiplication element by element    
        for (int i = 0; i < aRow; i++) {
            for (int j = 0; j < bCol; j++) {
                for (int k = 0; k < aCol; k++) {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return result;
    }

    void multiply(int[][] A, int[][] B) {
        int x = A[0][0] * B[0][0] + A[0][1] * B[1][0];
        int y = A[0][0] * B[0][1] + A[0][1] * B[1][1];
        int z = A[1][0] * B[0][0] + A[1][1] * B[1][0];
        int w = A[1][0] * B[0][1] + A[1][1] * B[1][1];

        A[0][0] = x;
        A[0][1] = y;
        A[1][0] = z;
        A[1][1] = w;
    }
}
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(\log n)$  
For matrix power calculation, it can achieve time complexity, $\mathcal{O}(\log{n})$, by using [Square and Multiply algorithm](https://en.wikipedia.org/wiki/Exponentiation_by_squaring#Computational_complexity). Since the matrix power $n$ can be represented by a binary number with at most $\log{n}$ bits (i.e., $\log{n}$ steps in Square and Multiply algorithm). 

* **Space complexity**: $\mathcal{O}(1)$ or $\mathcal{O}(\log n)$?  
If using multiply function specifically for Fibonacci matrix exponenentiation, the time complexity is $\mathcal{O}(1)$ since it only use fixed number of variables. If using matrixMultiply function for generic matrix multiplication,  a new 2d array will be created for each function call. The function is called $\log n$ times, so the the space complexity is $\mathcal{O}(\log n)$?.



### Approach 4 - Closed-form solution

#### Algorithm
Use the golden ratio formula to calculate the Nth Fibonacci number: $Fib(N) = \frac{\varphi^n - \psi^n}{\varphi - \psi} = \frac{\varphi^n - \psi^n}{\sqrt{5}}$
where $\varphi = \frac{1+\sqrt{5}}{2} \approx 1.6180339887$ is the golden ratio and $\psi = \frac{1 - \sqrt{5}}{2} = 1 - \varphi = -\frac{1}{\varphi} \approx -0.6180339887$. 
The limit of ratio of consecutive Fibonacci numbers converges to the golden ration $\varphi$:
$\lim_{n \rightarrow \infty} \frac{F_{n+1}}{F_n} = \varphi$.

For implementation, we use $Fib(N) = \frac{\varphi^n}{\sqrt{5}}$, since $\psi^n = (-0.62)^n$ becomes very small when n is very large. We just need to make sure when N = 0, 1, and 2, the equation returns the right value.
#### Implementation
```java
public int fib(int N) {
    double goldenRatio = (1 + Math.sqrt(5)) / 2;
    
    return (int)Math.round(Math.pow(goldenRatio, N)/ Math.sqrt(5));
}
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(\log n)$  
The time complexity of floating-point exponentiation (Math.pow) function is $\mathcal{O}(\log n)$ 
* **Space complexity**: $\mathcal{O}(1)$ 
The space used is the sapce needed for store the ratio value.  



### Complexity Summary
|     | Time Complexity | Space Complexity  
| ----- | ----- | ----- |  
| Approach 1a - Recursive | $\mathcal{O}(2^n)$  | $\mathcal{O}(n)$ |  
| Approach 1b - Recursive + memoization | $\mathcal{O}(n)$    | $\mathcal{O}(n)$ | 
| Approach 1c - Recursive + memoization (fast) | $\mathcal{O}(\log n)$    | $\mathcal{O}(n)$ |  
| Approach 2 - Iterative| $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | 
| Approach 3a - Matrix recursive| $\mathcal{O}(\log n)$ | $\mathcal{O}(\log n)$ |  
| Approach 3b - Matrix iterative | $\mathcal{O}(\log n)$ | $\mathcal{O}(1)$ |  
| Approach 4 - Closed-form | $\mathcal{O}(\log n)$ | $\mathcal{O}(1)$ | 