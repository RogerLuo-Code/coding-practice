---
tags:
    - Array
    - Two Pointers
    - Sliding Window
---

# LC713. Subarray Product Less Than K
## Problem Description
[LeetCode Problem 713](https://leetcode.com/problems/subarray-product-less-than-k/): Given an array of integers `nums` and an integer `k`, return _the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than_ `k`.

## Clarification
- integer array
- find number of subarrays with product < k
- positive elements
- positive k? `k==0`?

## Assumption
- Product of subarray won't cause overflow of long long int
- Array elements are positive
- `k >= 0`

## Solution
### Approach - Sliding Window
The problem can be solved using a sliding window method with two pointers:

- Expand the sliding window by adding a new number on the right (right pointer, `j`)
- If `product >= k`, shrink the window by removing the number from the left (left pointer, `i`) until the subarray with `product < k` again
	- Note subarray could be empty and therefore needs add condition `left <= right`. So the while loop ends at `left == right + 1` when no subarray satisfies the condition
- Each step introduces `x` new subarrays, where `x`  is the size of the current window `j - i + 1`
	- For example, for window (5, 2), when 6 is introduced, it adds 3 new subarray
		- (6)
		- (2, 6)
		- (5, 2, 6)
	- Then in nexts step when 3 is introduce, it may add 4 new subarrays
		- (3)
		- (6, 3)
		- (2, 6, 3)
		- (5, 2, 6, 3) : depending k, may not satisfy the condition, 

=== "Python"
    ```python
    class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        product = 1
        count = 0
        left = 0

        for right in range(len(nums)):
            product *= nums[right]

            while product >= k and left <= right:
                product = product // nums[left]
                left += 1

            count += right - left + 1 # (1)

        return count
    ```

    1. When subarray is empty, `left = right + 1` and therefore `right - left + 1 = 0`

=== "C++"
    ```cpp
    class Solution {
    public:
        int numSubarrayProductLessThanK(vector<int>& nums, int k) {
            typedef vector<int>::size_type vec_size;
            vec_size left = 0;
            long long int product = 1;
            int count = 0;

            for (vec_size right = 0; right < nums.size(); right++) {
                product *= nums[right];

                while (product >= k && left <= right) {
                    product /= nums[left++];
                }

                count += right + 1 - left;
            }

            return count;
        }
    };
    ```

When product of subarray is too large, we can use `log` function to convert `A*B*C >= k` to `log(A*B*C) = log(A) + log(B) + log(C) >= log(k)`.
Yet, due to numerical issue of floating point, we need to use `math.isclose` to check whether the summation is equal to `log(k)`.

```python
import math

class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        if k == 0:
            return 0

        prefix_sum = 0
        count = 0
        left = 0
        log_k = math.log(k)

        for right in range(len(nums)):
            prefix_sum += math.log(nums[right])

            while (prefix_sum > log_k or math.isclose(prefix_sum, log_k)) and left <= right:
                prefix_sum -= math.log(nums[left])
                left += 1

            count += right - left + 1

        return count
```

#### Complexity Analysis
* Time complexity: $O(n)$  
	The `right` pointers is increased by $n$ times 
* Space complexity: $O(1)$  
	Use limit local variables with constant space. 

## Test