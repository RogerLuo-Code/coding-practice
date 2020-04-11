# Compute Fibonacci numbers 
# Refer to https://en.wikipedia.org/wiki/Fibonacci_number

import time
n_fib = 12

# Method 1: Recursive method, taking a long time for large n
def fib(n):
    if n <= 1:
        return n
    else:
     	return fib(n-1) + fib(n-2)
    
f1_t0 = time.time()
f1 = fib(n_fib)
f1_te = time.time()
print('Method 1 value: ', f1)
print('Method 1 time: ', f1_te - f1_t0, ' seconds')

# Method 2: Iterative method
def fib2(n):
    a,b = 0, 1
    for _ in range(n):
        a, b = b, a+b
    return a
    # if n <= 1:
    #     return n
    # else: 
    #     values = [0, 1, 1]
    #     for k in range(3, n+1, 1):  # since range is exclusive, we nee to put n+1 to include n 
    #         values[0:2] = values[1:3]
    #         values[2] = sum(values[0:2])
    #     return values[2]
f2_t0 = time.time()
f2 = fib2(n_fib)
f2_te = time.time()
print('Method 2 value: ', f2)
print('Method 2 time: ', f2_te - f2_t0, ' seconds')

# Method 3: Closed-form solution (Binet's formula)
def fib3(n):
    sqrt5 = 2.23606797749979 # 5**0.5, or math.sqrt(5)
    phi = (1 + sqrt5)/2
    f = round((phi**n - (-phi)**(-n))/sqrt5)
    return f
f3_t0 = time.time()
f3 = fib3(n_fib)
f3_te = time.time()
print('Method 3 value: ', f3)
print('Method 3 time: ', f3_te - f3_t0, ' seconds')

# Method 4: Matrix exponential
import numpy as np 
def fib4(n):
    f_m = np.linalg.matrix_power(np.array([[1, 1], [1, 0]]), n)
    return f_m[0, 1]
f4_t0 = time.time()
f4 = fib4(n_fib)
f4_te = time.time()
print('Method 4 value: ', f4)
print('Method 4 time: ', f4_te - f4_t0, ' seconds')
