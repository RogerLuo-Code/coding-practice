---
tags:
    - Array
    - Prefix Sum
    - Hash Table
---

# LC974. Subarray Sums Divisible by K
## Problem Description
[LeetCode Problem 974](https://leetcode.com/problems/subarray-sums-divisible-by-k/): Given an integer array `nums` and an integer `k`, return _the number of non-empty **subarrays** that have a sum divisible by_ `k`.

A **subarray** is a **contiguous** part of an array.

## Clarification
- Meaning of **contiguous**: not mean unbroken block of memory but more about consecutive elements (i.e., indices are adjacent and in continuous range)
- $0/k$ is considered as divisible? Yes

## Assumption
- $k \neq 0$
- $k > 0$

## Solution
### Approach - Brute Force  
The straightforward method is to compute sum between index `i` and `j` for any possible subarray using two for-loops. If `sum % k == 0`, increase the count. 

```cpp
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int count = 0;
        int sum; 
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            sum = 0;
            for (int j = i; j < nums.size(); j++) {
                sum += nums[j];           
                if (sum % k == 0) {
                    count++;
                }
            }
        }
        return count;      
    }
}; 
```

#### Complexity Analysis
* Time complexity: $O(n^2)$  
	Since using two for-loops to iterate all possible subarray combinations, it takes $O(n^2)$ time complexity. 
* Space complexity: $O(1)$
	It uses constant space complexity since just using two pointers and two variables `sum` and `count`. 

### Approach - Prefix Sum + Remainder
We can view the problem from different angle, using cumulative sum (or prefix sum). we know that `cusum(i) - cusum(j)` is the sum of subarray from index `i+1` to `j`. If the sum of the subarray is divisible by `k`, `cusum(i)` and `cusum(j)` should have the same remainder. 

Why is this true? Let's start from the basics. The quotient $q$ and the remainder $r$ of $a$ divided by $n$ satisfy the following conditions: $n = k q + r$ with $|r| < |k|$.  For $sum_i = k q_i + r_i$ and $sum_j = k q_j + r_j$, $sum_i - sum_j = k (q_i - q_j) + (r_i - r_j)$. if $sum_i - sum_j$ is divisible by $k$ (sum of subarray from `i+1` to `j` is also divisible by $k$), it means $r_i = r_j$.

So we iterate through the array and compute the cumulative sum. For any given $sum_i$, we can check whether there exists $sum_j$ computed previously that have the same remainder as $sum_i$. Note that there may be multiple $sum_j$ satisfy this condition. To effectively store previous computed $sum_j$ with number of appearances and retrieve this information later, we can use 

- hashmap to store `<remainder, number of appearances>`
- vector or array to store number of appearances. Array size is $k$ and index $0$ to $k-1$ correspond remainders.  

???+ Note

    For negative numbers, `n % k` returns **signed** remainder. For any negative remainder, it has an equivalent positive one. For example, $-1 = 0 * 4 + (-1) = -1*4 + 3$. To handle missing count, we can convert negative remainder to the positive one by `+k`.


- Use hashmap to store remainders

=== "Python"
    ```python
    class Solution:
    def subarraysDivByK(self, nums: List[int], k: int) -> int:
        remainder_freq_map = {0:1} # (1)
        count = 0
        prefix_sum = 0
        for num in nums:
            prefix_sum += num

            remainder = prefix_sum % k

            if remainder < 0:
                remainder += k

            if remainder in remainder_freq_map:
                count += remainder_freq_map[remainder]
                remainder_freq_map[remainder] += 1
            else:
                remainder_freq_map[remainder] = 1

        return count
    ```

    1. When `prefix_sum % k == 0`, it should count as `1`. So reminder count needs to be initialized as 1 for correct counting.

=== "C++"
    ```cpp
    class Solution {
    public:
        int subarraysDivByK(vector<int>& nums, int k) {
            unordered_map<int, int> remainderCount;
            int count = 0;
            int sum = 0;
            int remainder;

            for (int num : nums) {
                sum += num;

                remainder = sum % k;
                if (remainder < 0) {
                    remainder += k;
                }

                if (remainder == 0) {
                    count++;
                }

                if (remainderCount.find(remainder) != remainderCount.end()) {
                    count += remainderCount[remainder];
                }

                remainderCount[remainder]++;

            }

            return count;
        }
    };
    ```

* Use vector to store remainders
=== "Python"
    ```python
    class Solution:
    def subarraysDivByK(self, nums: List[int], k: int) -> int:
        remainder_freq = [0] * k
        remainder_freq[0] = 1
        count = 0
        prefix_sum = 0
        for num in nums:
            prefix_sum += num

            remainder = prefix_sum % k

            if remainder < 0:
                remainder += k

            count += remainder_freq[remainder]
            remainder_freq[remainder] += 1

        return count
    ```

=== "C++"
    ```cpp
    class Solution {
    public:
        int subarraysDivByK(vector<int>& nums, int k) {
            vector<int> remainderArray(k, 0);
            int count = 0;
            int sum = 0;
            int remainder;

            for (int num : nums) {
                sum += num;

                remainder = sum % k;
                if (remainder < 0) {
                    remainder += k; // convert to negative remainder to positive ones
                }

                if (remainder == 0) {
                    count++;
                }
                count += remainderArray[remainder];
                remainderArray[remainder]++;
            }
            return count;
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Since it just iterates the array once, it takes $O(n)$ time complexity.
* Space complexity: $O(k)$  
	It needs to store remainders, which is from $0$ to $k-1$, at most $k$.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Brute Force |  $O(n^2)$ 	   	   	| $O(1)$  
Approach - Prefix Sum + Remainder |  $O(n)$      		| $O(k)$

## Test
- **Negative** number

## Mistakes
- Not initialize `count`, causing result with random number