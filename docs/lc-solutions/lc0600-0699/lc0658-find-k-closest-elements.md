---
tags:
- Binary Search
---

# LC658. Find K Closest Elements
## Problem Description
[LeetCode Problem 658](https://leetcode.com/problems/find-k-closest-elements/): Given a **sorted** integer array `arr`, two integers `k` and `x`, return the `k` closest integers to `x` in the array. The result should also be sorted in ascending order.

An integer `a` is closer to `x` than an integer `b` if:

- `|a - x| < |b - x|`, or
- `|a - x| == |b - x|` and `a < b`)` space.

## Clarification
- Find k elements vs. k-th element?
- Range of k? K <= 0 or k > arr.length?
- Sorted vs unsorted?
- Exact target my not exit and target may be out of array range
- Duplicate elements (target, or any element in the result) handling? 
- Deal with tie case?
- return data - sorted or unsorted? sorted in ascending order or based on distance from x? what about empty?

## Assumptions
- `k <= arr.length`

## Solution
1. For **unsorted** array, sort the element first by absolute difference values to the target (e.g., [using Collection.sort](https://leetcode.com/problems/find-k-closest-elements/solution/)). The result is in the first k elements.   
2. For **sorted** array, we can use binary search to speed up the search. There are two different ways to achieve that:

    - Binary search with two pointers: Use binary search to find two closest elements around the target and move to left or right using two pointers to find k closet elements.
    - [Binary search of a window @lee215](https://leetcode.com/problems/find-k-closest-elements/discuss/106426/JavaC%2B%2BPython-Binary-Search-O(log(N-K)-%2B-K)): using binary search to find index i such that the window `[i, i+k-1]` (inclusive) contains the k closest elements

### Approach - Sorting
Sort the element first by absolute difference values to the target. The result is in the first k elements. Before return, sort the k elements so the result is in ascending order as required. This approach can be used for both sorted and unsorted array. 

* To use `Collections.sort`, the input array is copied to an array list. 
* `Collection.sort` is used twice -- 1) sort the whole array based on distance from target and 2) sort the k elements in the result based on the value 
* [`Collection.sort` uses mergesort](https://docs.oracle.com/en/java/javase/14/docs/api/java.base/java/util/List.html#sort(java.util.Comparator)) and has $n \log n$ comparison for general case. 
* The [`subList` function of ArrayList](https://docs.oracle.com/en/java/javase/14/docs/api/java.base/java/util/ArrayList.html#subList) return a view of the portion of original list. Any operations on the sub list is actually happening on the original list. 
* The total number of executions (including array copy and sort): $n + n \log n + k \log k$

=== "Java"
    ```java
    class Solution {
        public List<Integer> findClosestElements(int[] arr, int k, int x) {

            List<Integer> arrList = new ArrayList<Integer>();

            // Add array values to list
            for (int i=0; i < arr.length; i++)
                arrList.add(arr[i]);

            // Sort with compare funciont defined with lambda expression
            Collections.sort(arrList, (a, b) -> Math.abs(a - x) - Math.abs(b - x));

            // The k closest elements
            arrList = arrList.subList(0, k);

            // Sort again before return so the result in ascending order
            Collections.sort(arrList);
            return arrList;
        }
    }
    ```

#### Complexity Analysis
* **Time complexity**: $O(n \log n)$  
Collections.sort() uses merge sort and has $n \log n$ comparison for general case. The total number of executions (including array copy and sort): $n + n \log n + k \log k$. Therefore, $O(n + n \log n + k \log k) \rightarrow O (n \log n)$ 
* **Space complexity**: $O(n)$  
The in-place sorting does not consume any extra space. However, converting array to list takes additional space. If the input is the list, it will be $O(1)$ since `subList` returns a view, not a separate copy.

### Approach - Binary Search with two pointers
Since the original array is sorted, we can use binary search to speed up the search with the following two steps:   

1. Use binary search to find the index of the target or the index of a smaller element that is closest to target (if target not exists) 
2. Move to left or right (inside-out) using two pointers to find k closet elements. *Alternative way*: shrink the range [index-k-1, index+k+1] where the desired k elements must in.   

**Improvement** on step 2: use binary search idea again     
If `arr[pointLeft - k/2]` is closer to target compared with `arr[pointLeft + k/2]`, then all elements from `pointLeft - k/2` to `pointLeft` should be included in the result.  
Next step compare `arr[pointLeft - k/2 - k/4]` and `arr[pointRight + k/4]`  
Using recursion will be   
`k, (p1, p1+1, k)`  
`k/2, (p1 - k/2, p2 + 1, k - k/2)`,   
This method can achieve $O(\log n + \log k)$ time complexity on find indices but still need $O(\log n + k)$ to return elements since generating k length list needs some time. 

=== "Python"
    ```python
    class Solution:
        def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
            if k <= 0 or k > len(arr):
                return [0]

            left = self.binarySearch(arr, x)
            right = left + 1
            # Expand to left and right to find the k sub array
            for count in range(k):
                if left < 0:
                    right += 1
                elif right > len(arr) - 1:
                    left -= 1
                else:
                    if abs(arr[left] - x) <= abs(arr[right] - x):
                        left -= 1
                    else:
                        right += 1

            return arr[left + 1: right]

        def binarySearch(self, arr: List[int], x: int) -> int:
            left, right = 0, len(arr) - 1

            while left < right - 1:
                mid = (left + right) // 2

                if arr[mid] == x:
                    return mid
                elif arr[mid] < x:
                    left = mid
                else:
                    right = mid

            return left
    ```

=== "Java"
    ```java
    class Solution {
        public List<Integer> findClosestElements(int[] arr, int k, int x) {
            List<Integer> result = new ArrayList<Integer>();

            if (arr == null || arr.length == 0)
                return result; // return array

            // Corner cases for k
            // could return all elements if k > arr.length
            if (k <= 0 || k > arr.length)
                return result; // return new int[0]

            // binary search first
            // then find closest elements from target to left and to right

            int idxLeft = binarySearch(arr, x); // index for the left half, left closet element or equal element
            int idxRight = idxLeft + 1; // index for the right half

            for (int count = 0; count < k; count++){
                if (idxRight >= arr.length  || (idxLeft >= 0 && Math.abs(arr[idxLeft] - x) <= Math.abs(arr[idxRight] - x)))
                    idxLeft--;
                else
                    idxRight++;
            }

            for (int idx = idxLeft+1; idx < idxRight; idx++)
                result.add(arr[idx]);

            return result;
        }

        private int binarySearch(int[] arr, int target){
            // return index of the left closest element to the target
            int left = 0;
            int right = arr.length - 1;
            int middle;

            while (left < right - 1){
                middle = left + (right - left)/2;
                if (target < arr[middle])
                    right = middle;
                else if (target > arr[middle])
                    left = middle;
                else // target == arr[middle]
                    return middle;
            }

            // No need postprocessing, just return the left element
            return left;
        }
    }
    ```

#### Complexity analysis
* **Time complexity**: $O(\log n + k)$.
$O(\log n)$ is for the time of binary search, while $O(k)$ is for moving two pointers to find the range.
* **Space complexity**: $O(k)$ for generating a list with k elements from an array.

### Approach: Binary search of a window
A smart solutions from [@lee215](https://leetcode.com/problems/find-k-closest-elements/discuss/106426/JavaC%2B%2BPython-Binary-Search-O(log(N-K)-%2B-K)): using binary search to find index `i` such that the window `[i, i+k-1]` (inclusive) contains the k closest elements. Move the window to left or right by comparing the distance between `x - arr[mid]` and `arr[mid + k] - x`.

* case 1: x is outside of window and on the left (`x - A[mid] < A[mid + k] - x`), move window to left  
-----x----A[mid]------------A[mid+k]--------
* case 2: x is in the window and close to the left (`x - A[mid] < A[mid + k] - x`), move window to left again   
----A[mid]-----x------------A[mid+k]--------
* case 3: x is in the window close to the right (`x - A[mid] > A[mid + k] - x`), move window to right   
----A[mid]------------x-----A[mid+k]--------
* case 3: x is outside of window and on the right (`x - A[mid] > A[mid + k] - x`), move window to right   
----A[mid]------------------A[mid+k]---x----

**Important** points for implementation:

* Initialize `right = arr.length - k`, so `right + k - 1` will not exceed `arr.length`
* When updating left and right indices, using `mid + 1`, `mid`, or `mid - 1`?

  - if `x - A[mid] > A[mid + k] - x`, it means `A[mid + k]` is closer to x and the window `A[mid + 1] - A[mid + k]` is better than the window `A[mid] - A[mid + k - 1]`. Therefore update `left = mid + 1`
  - if `x - A[mid] < A[mid + k] - x`, it means `A[mid]` is closer to x and the current window `A[mid] - A[mid + k - 1]` or potentially some window on the left is better. Therefore update `right = mid`. Note that it is NOT `mid - 1`, since from the comparison we only know the current window is better and don't know whether the window on the left is better.
  - if `x - A[mid] == A[mid + k] - x`, don't stop here and continue to check the left see whether there is a better window. In the problem description, it requires "If there is a tie, the smaller elements are always preferred." Therefore, update `right = mid` to search smaller elements.
* When to end the while loop for binary search? `left == right`
* For comparison, using absolute value `abs(x - A[mid]` or relative value with sign `x - A[mid]`?  
If `A[mid] == A[mid + k]`, we don't know either to move left or right using absolute value (need additional check). Relative values can tell the direction based on the sign of the value. The absolute value comparison method fails at cases like `A = [1,1,2,2,2,2,2,3,3]`, `x = 3`, `k = 2`. 
* For comparison, `A[mid]` vs. `A[mid + k]`, or `A[mid]` vs. `A[mid + k - 1]`?  
Use `A[mid]` vs. `A[mid + k]`, since we are trying to comparing two windows (A[mid] ~ A[mid + k - 1] vs. A[mid + 1] ~ A[mid + k]) to see which one is better.  

=== "Python"
    ```python
    class Solution:
        def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
            left, right = 0, len(arr) - k

            while left < right:
                mid = (left + right) // 2
                if x - arr[mid] > arr[mid + k] - x:
                    left = mid + 1
                else:
                    right = mid

            return arr[left: left + k]
    ```

=== "Java"
    ```java
    class Solution {
        public List<Integer> findClosestElements(int[] arr, int k, int x) {
            List<Integer> result = new ArrayList<Integer>();

            // Input validation
            if (arr == null || arr.length == 0)
                return result;

            if (k <= 0 || k > arr.length)
                return result;

            int left = 0;
            int right = arr.length - k; // -k here with window consideration
            int mid;

            while (left < right) {
                mid = left + (right - left)/2;

                // compare mid and mid+k not mid+k-1 to see which window is better
                // current window (mid ~ mid+k-1) or next window (mid+1 ~ mid+k)
                if (x - arr[mid] > arr[mid + k] - x)
                    left = mid + 1;
                // else if (x - arr[mid] < arr[mid + k] - x)
                //     right = mid;
                else
                    right = mid;  // for tie case: not return, continue to check the left see whether there is a better window
            }

            // postprocessing left == right
            // window left ~ left + k - 1
            for (int i = left; i < left + k; i++)
                result.add(arr[i]);

            return result;

            // return Arrays.stream(arr, left, left + k).boxed().collect(Collectors.toList());

        }
    }
    ```

#### Complexity Analysis
* **Time complexity**: $O(\log (n - k))$ for finding indices and $O(\log (n - k) + k)$ for returning elements.  
Since the search space of binary search of window is $n-k$ elements, therefore the complexity for finding indices is $O(\log (n - k))$. However to return the elements, it involves k-times copy and therefore time complexity is changed to $O(\log (n - k) + k)$.
* **Space complexity**: $O(k)$ for generating a list with k elements from an array.

### Comparison of Different Approaches

| Approach    | Time Complexity | Space Complexity  
| ----- | ----- | ----- |  
| Approach - sorting | $O(n\log n)$ | $O(n)$ |  
| Approach - binary search with two pointers | $O(\log n + k)$ | $O(k)$ | 
| Approach - binary search of a window | $O(\log (n-k) + k)$ for returning elements | $O(k)$ | 
|             | $O(\log (n-k))$ for returning indices |         |


## Test
- Test corner cases: zero array, invalid k, array with 0, 1, and 2 elements
- Test general cases  