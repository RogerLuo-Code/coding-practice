---
tags:
- Binary Search
---

# LC702. Search in a Sorted Array of Unknown Size

## Problem Description
[LeetCode Problem 702](https:leetcode.com/problems/search-in-a-sorted-array-of-unknown-size/): This is an **_interactive problem_**.

You have a sorted array of **unique** elements and an **unknown size**. You do not have an access to the array but you can use the `ArrayReader` interface to access it. You can call `ArrayReader.get(i)` that:

- returns the value at the `ith` index (**0-indexed**) of the secret array (i.e., `secret[i]`), or
- returns `231 - 1` if the `i` is out of the boundary of the array.

You are also given an integer `target`.

Return the index `k` of the hidden array where `secret[k] == target` or return `-1` otherwise.

You must write an algorithm with `O(log n)` runtime complexity.

## Clarification
  - Data type? integer
  - Sorted vs. unsorted?
  - Ascending order or descending order?
  - ArrayReader question:
      - What value to return when element doesn't exist?
      - zero-based indexing?
  - How large the array size could be? Exceed the max value allowed of integer?
  - Any duplicates? what to return if target has duplicates

## Assumption
- the array size < Integer.MAX_VALUE;
- zero-based indexing
- target < 2^31 - 1

## Solution
### Approach - Binary Search
Since the array is **sorted**, we can  

1. Define search limits, i.e., left and right boundaries  
If target is outside the boundaries, then it should be on the right and extend the boundaries `left = right` and `right = right * 2`. Some considerations:  
    - End the search when `reader.get(right) >= target`
    - `right = right * 2` vs. `right = right * 10` (both work for elements with duplicates)
    - tricky method: since all the elements are **unique**, there are at most `right = target - reader.get(0)` elements from index 0 to the index of target. If the element at the upper bound index does not exist, the search array will contain some `2^31 - 1` in the end. For example, `[-1, 2, 5, 8, 2^31 - 1, 2^31 - 1]`.
2. Perform classic binary search within the boundaries  


=== "Python"
    ```python
    class Solution:
        def search(self, reader: 'ArrayReader', target: int) -> int:
            left, right = 0, 1

            while reader.get(right) < target:
                left, right = right, right * 2

            while left <= right:
                mid = (left + right) // 2
                value = reader.get(mid)
                if value == target:
                    return mid
                elif target < value:
                    right = mid - 1
                else:
                    left = mid + 1

            return -1
    ```


=== "Java"
    ```java
    class Solution {
        public int search(ArrayReader reader, int target) {
            int left = 0;
            int right = 1;

            // Search boundaries [Left, Right] to include target
            while ((reader.get(right) < target)) {
                if (reader.get(right) == 2147483647)
                    return -1;

                left = right;
                if (right < Integer.MAX_VALUE/2)
                    right *= 2;  // or right <<= 1, double right until finding the right boundary (i.e., right > target)
                else{
                    right = Integer.MAX_VALUE;
                    break;
                }
            }
            // left = right/2;

            int mid;
            int val;  // value of reader.get(mid)
            // classic binary search
            while (left <= right) {
                mid = left + (right - left)/2;

                val = reader.get(mid);
                if (val == 2147483647)
                    right = mid - 1;
                else if (target < val)
                    right = mid - 1;
                else if (target > val)
                    left = mid + 1;
                else
                    return mid;
            }

            return -1;
        }
    }
    ```

#### Complexity Analysis
* **Time complexity**: $\mathcal{O}(\log T)$, where $T$ is an index of target value   
There are two operations:

  - Find search boundaries: the boundary is $2^k < T \leq 2^{k+1}$ and needs $k = \log T$ steps to find the boundaries 
  - Binaries search within the boundaries: There are $2^{k+1} - 2^k = 2^k = 2^{\log T} = T$ elements. It takes $\log T$ steps for binary search.  
The total steps are $\log T + \log T$. Therefore, the time complexity is $\mathcal{O}(\log T)$  

* **Space complexity**: $\mathcal{O}(1)$, since it only update several variables in finding boundaries and performing binary search. 

**Alternative**: use `right *= 10` instead of `right *= 2`  
- Find search boundaries: the boundary is $10^k < T \leq 10^{k+1}$ and needs $k = \log_{10} T$ steps to find the boundaries    
- Binaries search within the boundaries: There are $10^{k+1} - 10^k = 9*10^k = 9*10^{\log_{10} T} = 9T$ elements. It takes $\log_2 9T$ steps for bineary search.  

Comparison between `right *= 2` and `right *= 10`:  

|   | Find Boundaries  |  Binary Search  |
|------|------|------ |
| right *= 2 | $\log_2 T$ | $\log_2 T$ |
| right *= 10 | $\log_{10} T$ | $\log_2 9T$ |

Which one is better? When $T > 23$, 10 times update is faster. However, even T is really big (e.g. $10^{30}$), the  difference between 10 times and 2 times is still small (69 steps less). So using either one in implementation is fine.

10 times - 2 times   
= $\log_{10} T + log_2 9T - \log_2T - \log_2 T$  
= $\log_{10} T - \log_2T + log_2 9T - \log_2 T$  
= $\log_{10} T - \log_2T + log_2 9$

$\log_{10} 24 - \log_2 24 + log_2 9 = - 0.035$  
$\log_{10} 10^{30} - \log_2 10^{30} + log_2 9 = - 68.81$

## Test
- Test corner cases: empty array, array size > Integer.MAX_VALUE, target doesn't exist
- Test general case