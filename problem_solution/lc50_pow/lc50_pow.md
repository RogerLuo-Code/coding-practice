# LeetCode Problem 50 - Pow(x, n)

## Problem Description
[LeetCode Problem 50](https://leetcode.com/problems/powx-n/): Implement pow(x, n), which calculates x raised to the power n ($x^n$).

## Analysis
* Clarification:
  - data type: x, double; n, int
  - x or n can be negative?
  - time complexity requirement
* Go through examples
* Solution:
  - Assumption
  - Input/Output: double, int; double
  - Corner case: `1/x` with `x==0`; `n=-n` when n is Integer.MIN_VALUE 
  - Algorithm
  - Time/space complexity
* Coding
* Test
  - Test corner cases
  - Test general cases

## Approach
The straightforward approach is to use brutal force to multiple x by n times. Yet, there are two more efficent methods:
* Fast Recursive
* Fast Iterative

In all approaches, the `n < 0` case is converted to `n > 0` case by making the following substitution: `x = 1/x` and `n = -n`. However, we need to take care of the corner cases:
* Divide by zero for `1/x`(Implicitly handled by Java)  
For floating point numbers, IEEE754 defines 1.0/0.0 as Infinity, -1.0/0.0 as -Infinity and 0.0/0.0 as NaN. Java follows this and therefore we don't need to deal with division by zero for floating point in Java. Yet, division by zero with `int` will throw an exception.
* Overflow of `n = -n` when is Integer.MIN_VALUE  
In Java, the int is represented by [two's complement form](https://en.wikipedia.org/wiki/Two%27s_complement) with range [-2,147,483,648, 2,147,483,647] or [$-2^{31}$, $2^{31}-1$]. We need to take care of over flow case for the min value: `-(-2,147,483,648) = -2,147,483,648`. There are two ways to deal with this case:
    - Define a 64-bit integer to hold the 32-bit value. No overflow for 32-bit integer calculation. 
    - Add if statement to check the special case `n == -2,147,483,648` and take care of it


### Approach 1 - Fast Recursive
#### Algorithm
If we get the result of $x^{n/2}$, we dont' need to multiply x for another n/2 times. Intead, we can use equation $x^{n} = (x^{n/2})^2$. So we can optimize the calculation based on the equation below:  

$$x^n = \begin{cases}
{(x^{\frac{n}{2}})}^2 & \text{when n is even}\\
(x^{\frac{n}{2}})^2 x & \text{when n is odd}
\end{cases}$$

$$ \text{or } 
x^n = \begin{cases}
{(x^2)}^{\frac{n}{2}}  & \text{when n is even}\\
{(x^2)}^{\frac{n}{2}} x  & \text{when n is odd}
\end{cases}
$$

Refer to [this solution](https://leetcode.com/problems/powx-n/discuss/19546/Short-and-easy-to-understand-solution) for using the second equation. 

#### Implementation
Note the difference between `myPow(x, n/2)*myPow(x, n/2)` and `halfResult = myPow(x, n/2) halfResult*halfResult` on time complexity. 
* `myPow(x, n/2)*myPow(x, n/2)` will call myPow twice for each recursion. The total functions calls grow exponentially: $1 + 2 + 2^2 + \cdots + 2^{\log n} = (1+n)(n/2)$. The time complexity is $\mathcal{O}(n^2)$ and the space complexity is $\mathcal{O}(\log n)$ for recursive function calls.
```
            2^n                     1
        /         \
    2^{n/2}         2^{n/2}         2
    /    \         /       \  
2^{n/4} 2^{n/4} 2^{n/4} 2^{n/4}     2^2
...                                 ...
```
* `halfResult = myPow(x, n/2) halfResult*halfResult` only call myPow function once for each recursion. This can be considered as memoization of above approach. The time complexity is $\mathcal{O}(\log n)$ and the space complexity is $\mathcal{O}(\log n)$ for recursive function calls.
```
    2^n
     |
    2^{n/2}
     |
    2^{n/4}
     |
     ...
```
```java
class Solution {
    public double myPow(double x, int n) {
        if (n < 0) {  
            if (n == Integer.MIN_VALUE)
                return myPow(x, n + 1)*(1/x); // x^n = x^(n+1)*x^(-1)
            else {
                x = 1/x; // For floating point numbers, IEEE754 defines 1.0/0.0 as Infinity, -1.0/0.0 as -Infinity and 0.0/0.0 as NaN. Division by zero with int will throw an exception. 
                n = -n;
            }
        }
     
        if (n == 0) {
            return 1.0; // base case
        }
        
        double halfResult = myPow(x, n/2); 
        if (n % 2 == 0)
            return halfResult*halfResult;
        else
            return halfResult*halfResult*x;
        
    }
    
}
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(\log n)$  
Each time n is reduced by half by using the equation $x^{n} = (x^{n/2})^2$. Thus we need at most $\mathcal{O}(\log n)$ computations to get the result.
* **Space complexity**: $\mathcal{O}(\log n)$  
We need to call the recursion $\mathcal{O}(\log n)$ times and need constant space (store the result of $x^{n/2}$) for each computation. So the space complexity is $\mathcal{O}(\log n)$. 

### Approach 2 - Fast Iterative

#### Algorithm
Using the binary representation of n, equation $x^{a+b} = x^a + x^b$, and above mentioned equation $x^{n} = (x^{n/2})^2$, we can achieve the fast iteration. For exmaple, $x^{(9)_{10}} = x^{(1001)_{2}} = x^{2^3*1 + 2^2*0 + 2^1*0 + 2^0*1} = x^{2^3*1}*x^{2^2*0}*x^{2^1*0}*x^{2^0*1}$. Note that $x^{2^{i}} = x^{2^{i-1}*2} = x^{(2^{i-1} + 2^{i-1})} = x^{2^{i-1}} * x^{2^{i-1}}$. So we have x at bit 0 and double x (i.e., x*x) iteratively.

#### Implementation
```java
class Solution {
    public double myPow(double x, int n) {
        if (n < 0) {  
            if (n == Integer.MIN_VALUE) // handle corner case -Integer.MIN_VALUE = Integer.MIN_VALUE
                return myPow(x, n + 1)*(1/x); // x^n = x^(n+1)*x^(-1)
            else {
                x = 1/x; // For floating point numbers, IEEE754 defines 1.0/0.0 as Infinity, -1.0/0.0 as -Infinity and 0.0/0.0 as NaN. Division by zero with int will throw an exception. 
                n = -n;
            }
        }
     
        if (n == 0) {
            return 1.0; 
        }
        
        double result = 1;
        for (; n > 0; n = n/2) {
            if ((n & 0x1) == 1) 
                result *= x;
            
            x = x*x;
        }
        
        return result;
    }  
}
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(\log n)$  
For power n, it can be represented by at most $\log n$-bit binary. The fast iterative method will multiply x by $\log n$ times.
* **Space complexity**: $\mathcal{O}(1)$  
We only need two variables: product of x and the final result.

### Complexity Summary
|     | Time Complexity | Space Complexity  
| ----- | ----- | ----- |  
| Approach 1 - Fast Recursive | $\mathcal{O}(\log n)$ | $\mathcal{O}(\log n)$ |  
| Approach 2 - Fast Iterative| $\mathcal{O}(\log n)$ | $\mathcal{O}(1)$ | 