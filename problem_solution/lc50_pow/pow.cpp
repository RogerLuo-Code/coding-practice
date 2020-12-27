// Clarification:
//  - n can be negative and zero
//  - n is integer
//  - x can be negative and zero
// Solution:
//  - brutal force, for loop until n
//  - use x^n = x^(n/2) * x^(n/2) when n is odd or x^n = x^(n/2) * x^(n/2)*x when n is even

// #include <limits> // numeric_limits, quiet_NaN
// #include <cmath> // fabs

class Solution {
public:
    double myPow(double x, int n) {
        
        // Corner case: x is near 0.0
        if  (fabs(x) < numeric_limits<double>::epsilon()) {
            if (n == 0) { // Define 0^0 as 1
                return 1;
            }
            else if (n > 0) {
                return 0;
            }
            else {
                return numeric_limits<double>::quiet_NaN();
            }
            
        }
        
        // n is minimum integer, -n will cause overflow
        if (n == numeric_limits<int>::lowest()) {
            return myPow(x, n+1)*(1/x);
        }
        
        // negative n
        if (n < 0) {
            n = -n;
            x = 1/x;
        }
        
        // base case of recursion
        if (n == 0) {
            return 1;
        }
        
        if (n == 1) {
            return x;
        }
        
        
        // Method 1: Recursion
//         double half = myPow(x, n/2);
        
//         if (n%2 == 0) {
//             return half*half;
//         }
//         else {
//             return half*half*x;
//         }  
        
        // Method 2: Iteration
        double result = 1;
        while (n > 0) {
            if ((n & 0x1) == 1) {
                result *= x;
            }
            x *= x;
            n = n >> 1;
        }
        
        return result;
        
    }
};