---
tags:
    - Array
---

# LC189. Rotate Array
## Problem Description
[LeetCode Problem 189](https://leetcode.com/problems/rotate-array/): Given an array, rotate the array to the right by `k` steps, where `k` is non-negative.

## Clarification
- Rotate to the right: fill the left with the elements coming out of the right
- $k$ is non-negative

## Assumption

## Solution
There are 3 different approaches to solve the problem:

1. Brute force using two loops to  rotate the array
2. Use additional array
3. Reverse

Note that we have `k = k % n` to handle the case where $k >= n$. 

### Approach - Brute Force
The straightforward approach is to rotate all the elements of the array $k$ times and each time move all elements to the right by $1$ step.

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        typedef vector<int>::size_type vec_size;
        vec_size n = nums.size();
        int temp; 
        for (int i = 0; i < k; i++) {
            temp = nums[n-1];
            for (vec_size j = n - 1; j >= 1; j--) {
                nums[j] = nums[j-1];
            }
            nums[0] = temp;
        }
    }
};
```

#### Complexity Analysis
* Time complexity: $O(n \times k)$    
	It takes $O(n)$ to shift all elements by one step. Since it is shifted $k$ times, the time complexity is $O(n \times k)$.
* Space complexity: $O(1)$
	Just use `temp` and indices with constant space.

### Approach - Using Extra Array
We use an extra array to place element of the array at its correct position, i.e., the number at index `i` in the original array is placed at the index `(i + k) % length of array` in the new array. Then, copy the elements from the new array to the original one. 

=== "Python"
    ```python
    class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        # Method 1: swap with temperary array
        k %= len(nums)
        temp = nums[-k:]
        nums[k:] = nums[:-k]
        nums[:k] = temp
    ```

=== "C++"
    ```cpp
    class Solution {
    public:
        void rotate(vector<int>& nums, int k) {
            typedef vector<int>::size_type vec_size;
            vec_size n = nums.size();
            vector<int> aux(n);

            // Save rotated array to the auxiliary array
            for (vec_size i = 0; i < n; i++) {
                aux[(i + k) % n] = nums[i];
            }

            // Copy the value back
            for (vec_size i = 0; i < n; i++) {
                nums[i] = aux[i];
            }
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	It takes $O(n)$ to put the numbers in the new array and $O(n)$ to copy the values to the original array. So the time complexity is $O(n) = O(n) + O(n)$ 
* Space complexity: $O(n)$
	Needs a new array with the same size of the original array.

### Approach - Reverse
The following approach is shared by [@danny6514](https://leetcode.com/problems/rotate-array/discuss/54250/Easy-to-read-Java-solution) and explained by [@xingyze](https://leetcode.com/problems/rotate-array/discuss/54250/Easy-to-read-Java-solution): 

1.  Reverse all the elements of the array, "--->-->" to "<--<---"
3. Reverse the first $k$ elements "<--", we can get "--><---"
4. Reverse the rest $n-k$ elements "<---", we can get "-->--->"

=== "Python"
    ```python
    class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        k %= len(nums)
        n = len(nums)
        self.reverse(nums, 0, n - 1)
        self.reverse(nums, 0, k - 1)
        self.reverse(nums, k, n - 1)

    def reverse(self, nums: List[int], start: int, end: int) -> None:
        while start < end:
            temp = nums[start]
            nums[start] = nums[end]
            nums[end] = temp
            start += 1
            end -= 1
    ```

=== "C++"
    ```cpp
    class Solution {
    public:
        void rotate(vector<int>& nums, int k) {
            vector<int>::size_type n = nums.size();
            if (n <= 1) return; // k % 0 is undefined and no need to rotate for zero or 1 element
            k = k % n; // make sure k is within [0, n)
            // If no element to rotate or rotate 0 time, return
            if (k < 1) return;

            reverse(nums, 0, n - 1);
            reverse(nums, 0, k - 1);
            reverse(nums, k, n - 1);
        }

    private:
        void reverse(vector<int>& nums, vector<int>::size_type begin, vector<int>::size_type end) {
            while (begin < end) {
                swap(nums[begin], nums[end]);
                begin++;
                if (end == 0) {
                    break;
                }
                else {
                    end--;
                }
            }
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	The array is reversed total of two times. So the time complexity is $O(n) = O(n) + O(n)$ 
* Space complexity: $O(1)$
	Just use some pointers of constant space. 

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Brute Force |  $O(n \times k)$ 	   	   	| $O(1)$  
Approach - Use Extra Array |  $O(n)$          | $O(n)$
Approach - Reverse |  $O(n)$      		| $O(1)$

## Test