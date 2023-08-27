---
tags:
    - Array
    - Dequeue
    - Prefix Sum
---

# LC862. Shortest Subarray with Sum at Least K
## Problem Description
[LeetCode Problem 862](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/): Given an integer array `nums` and an integer `k`, return _the length of the shortest non-empty **subarray** of_ `nums` _with a sum of at least_ `k`. If there is no such **subarray**, return `-1`.

A **subarray** is a **contiguous** part of an array.

## Clarification
- Integer array
- Includes both positive and negative numbers
- return length of the shortest subarrays with `sum >= k`

## Assumption
- `long int` can cover the sum of subarrays

## Solution
### Approach - Brute Force
Compute sum of all possible subarrays using two nested for loops. If `sum >= k`, update the minimal length of subarray.

=== "Python"
    ```python
    class Solution:
    def shortestSubarray(self, nums: List[int], k: int) -> int:
        sum = 0
        count = len(nums) + 1

        for i in range(len(nums)):
            sum = 0
            for j in range(i, len(nums)):
                sum += nums[j]

                if sum >= k:
                    count = min(count, j - i + 1)

        return count if count < len(nums) + 1 else -1

    ```

=== "C++"
    ```cpp
    class Solution {
    public:
        int shortestSubarray(vector<int>& nums, int k) {
            typedef vector<int>::size_type vec_size;
            vec_size n = nums.size();
            int sum = 0; // sum between i and j;
            int minLength = n + 1;
            int length = 0;

            for (vec_size i = 0; i < n; i++) {
                sum = 0;
                for (vec_size j = i; j < n; j ++) {
                    sum += nums[j]; 
                    if (sum >= k) {
                        length = j - i + 1;
                        if (length < minLength) {
                            minLength = length;
                        }
                    }
                }
            }

            return (minLength == n + 1) ? -1 : minLength;
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n^2)$  
	Since it use two nested for-loops to find all possible subarrays, it takes $O(n^2)$   
* Space complexity: $O(1)$  
	Only use several local variables. 

### Approach - Prefix sum + Deque
We can think about the problem in terms of cumulative sum, where 
- `cusum(i)` is the sum of subarray from index `0` to `i`. 
- `cusum(j) - cusum(i)` is the sum of subarray from index `i+1` to `j`
So the problem is converted to find `cusum(y) - cusum(x) >= k` for the subarray from index `x+1` to `y` (with length `y - (x + 1) + 1 = y - x`) and update the shorted length if `y - x` is smaller.

There are two important ways to optimize the solution ([@mrv2671988](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/discuss/549959/Video-Solution-and-Java-Deque-Code)gives a good explanation):
1. If indices `x < y1 < y2` (x is the last element, $y_1$ is the new element and $y_2$ is the future element) and assume `cusum(y1) - cusum(x) >= k`, then for any `y2` after `y1` (i.e. `y2 > y1`) that satisfies `cusum(y2) - cusum(x) >= k`, it will have a longer length `y2 - x > y1 - x`. **So no need to consider `x` for `y2` after finding the first `y1` and updating the length**.
```
cusum array [a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11]
					x        y1          y2
```
2. If indices `x1 < x2 < y` (x_1 is the last element, x_2 is the new element, y is the future element) and assume `cusum(y) - cusum(x1) >= k`  and `cusum(x1) >= cusum(x2)` (i.e., **negative sum** of subarray from `x1+1` to `x2`), then `cusum(y) - cusum(x2) >= cusum(y) - cusum(x1) >= k` with shorter length `y - x2 < y - x1`.  **So no need to consider `x1` if there is `cusum(x2) <= cusum(x1)`** 
```
cusum array [a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11]
				   x1       x2          y
```

Based on point 2, if we use a data structure to store previous `cusum(x)`, it will be an increased order with increase index. Then we can take advantage of this property:

- Use point 1 to check whether to remove the minimum value (i.e., the first element) in the data structure. 
	- If the first element (minimum value) doesn't satisfying the equation `cusum(y) - cusum(x) >= k`, no need to check the rest of data
	- If satisfying the equation, remove the minimum value based on point 1
- Use point 2 above to determine whether to remove the last element (maximum value) in the data structure before storing the current index
To effective support the operations: insert the element in the end, read/drop the element in the end, read/pop the element in the front, we use `deque` structure.

=== "Python"
    ```python
    class Solution:
    def shortestSubarray(self, nums: List[int], k: int) -> int:
        d = collections.deque()
        prefix_sum = 0
        prefix_sum_array = [0] * len(nums)
        min_size = len(nums) + 1

        for i in range(len(nums)):
            prefix_sum += nums[i]
            prefix_sum_array[i] = prefix_sum

            if prefix_sum >= k:
                min_size = min(min_size, i + 1)

            while d and (prefix_sum - prefix_sum_array[d[0]]) >= k:
                min_size = min(min_size, i - d[0])
                d.popleft()

            while d and prefix_sum <= prefix_sum_array[d[-1]]:
                d.pop()

            d.append(i)

        return min_size if min_size < len(nums) + 1 else -1
    ```

=== "C++"
    ```cpp
    class Solution {
    public:
        int shortestSubarray(vector<int>& nums, int k) {
            typedef vector<int>::size_type vec_size;
            vec_size n = nums.size();
            int res = n + 1; // n+1 is impossible
            deque<vec_size> d;

            vector<long> cusum(n+1, 0);
            for (vec_size i = 0; i < n + 1; i++) {
                if (i > 0) {
                    cusum[i] = cusum[i-1] + nums[i-1];
                }

                if (cusum[i] >= k) {
                    res = (i+1 < res) ? i+1 : res;
                }

                while (d.size() > 0 && cusum[i] - cusum[d.front()] >= k) {
                    res = ((i - d.front()) < res) ? i - d.front() : res;
                    d.pop_front();
                }

                while (d.size() > 0 && cusum[i] <= cusum[d.back()]) {
                    d.pop_back();
                }
                d.push_back(i);
            }
            return res <= n ? res : -1;
        }
    };
    ```

**Potential improvements**: use deque of pair to store `<index, cusum>` instead of just index which requires sum array.

=== "Python"
    ```python
    class Solution:
    def shortestSubarray(self, nums: List[int], k: int) -> int:
        d = collections.deque()
        prefix_sum = 0
        min_size = len(nums) + 1

        for i, num in enumerate(nums):
            prefix_sum += num

            if prefix_sum >= k:
                min_size = min(min_size, i + 1)

            while d and (prefix_sum - d[0][1]) >= k:
                min_size = min(min_size, i - d[0][0])
                d.popleft()

            while d and prefix_sum <= d[-1][1]:
                d.pop()

            d.append([i, prefix_sum])

        return min_size if min_size < len(nums) + 1 else -1
    ```

=== "C++"
    ```cpp
    class Solution {
    public:
        vector<int>::size_type shortestSubarray(vector<int>& nums, int k) {
            typedef vector<int>::size_type vec_size;
            deque<pair<vec_size, long int>> dq; // deque of pair <index, cusum>
            long int sum = 0;
            vec_size n = nums.size();
            vec_size minLength = n + 1;
            vec_size length;

            for (vec_size i = 0; i < n; i++) {
                sum += nums[i];

                if (sum >= k) {
                    minLength = (i + 1 < minLength) ? i+1 : minLength;
                }

                while (!dq.empty() && (sum - (dq.front()).second >= k)) {
                    length = i - (dq.front()).first; // should always >= 0 no need to worry about unsigned integer overflow
                    minLength = (length < minLength) ? length : minLength;
                    dq.pop_front();
                }

                while (!dq.empty() && sum <= (dq.back()).second) {
                    dq.pop_back();
                }

                dq.push_back({i, sum});
            }
            return minLength <= n ? minLength : -1;
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Every index will be pushed exact once and every index will be popped at most once.  
* Space complexity: $O(n)$  
	The `cusum` array will take $O(n)$ space and the deque structure will take $O(n)$ space. So the total space complexity is $O(n)$.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Brute Force |  $O(n^2)$ 	   	   	| $O(1)$  
Approach - Prefix Sum + Deque |  $O(n)$      		| $O(n)$

## Test
### Common Errors
- Forget to check whether queue is empty before popping elements
- Use `if` statement not `while`

## References
