# Implement pow(x, n), which calculates x raised to the power n (x^n).
# Note: n is a 32-bit signed integer, within the range [-2^31, 2^31 - 1]

# Brute force
# Time complexity: O(n)
# Space complexity: O(1)
def myPow(x: float, n: int) -> float:
    if (n < 0):
        x = 1.0/x
        n = -n
    ans = 1.0
    for _ in range(n):
        ans = ans*x
    return ans 

# Recursive method
def myPow2a(x: float, n: int) -> float:
    # special case
    if n == 0:
        return 1.0
    # if x == 1.0:
    #     return 1
    # if x == -1:
    #     if (n&1) != 0:
    #         return -1
    #     else:
    #         return 1
    # Note that Python uses arbitrary-precision integer and won't encounter 
    # overflow issue  
    # if n == -2**31:
    #     return 0

    if n < 0:
        x = 1.0/x
        n = -1*n  # In python, no overflow issue
    
    half = myPow2a(x, n//2)
    if (n%2 == 0):
        ans = half*half
    else:
        ans = (half*half)*x
        
    return ans

# Iterative method
def myPow3(x: float, n: int) -> float:
    if n < 0:
        x = 1.0/x
        n = -1*n  # In python, no overflow issue

    res = 1.0
    while (n>0):
        if (n&1):
            res *= x
        # update x for next bit
        x *= x
        n >>= 1
    return res

# Test 
import time
pow_func = [myPow, myPow2a, myPow3]
x = 2
n_range = 100
for n in range(0, n_range, 10):
    for k, f in enumerate(pow_func):
        t0 = time.time()
        res = f(x, n)
        te = time.time()
        print('Method {} value: {}'.format(k, res))
        print('Method {} time: {} seconds '.format(k, te-t0))
