# Extended Problem 02 - K-th Smallest Elements in Two Sorted Arrays 

## Problem Description
Find $k$-th smallest elements in two sorted arrays of size m and n respectively. 

## Analysis
* Clarification:
    - two sorted arrays with different size. One may be much smaller than the other?
    - how big the $k$ will be?
    - $k$-th correponds to index $k-1$ for zero-based indexing?
    - not empty
    - data type?
 * Go through examples
 * Solution:
    - Assumption: no empty array
    - Input/output: int array, int array; int
    - Algorithm:
    - Time/space complexity:

## Approaches
A straightforward method is to use brutal force to direct compare elements one by one between two sorted arrays until k-th smallest element is found. A much better way is to use binary search, requiring deep understanding of binary search principal. 
* **Idea**: In every iteration, compare first k/2 elements of array A with the first k/2 elements of array B and delete k/2 elements.
* **How to reduce search size?** k -> k/2 -> (k - k/2)/2 ... -> 1
* **How to delete k/2**? If `a[aLeft + k/2 - 1] <= b[bLeft + k/2 - 1]`, delete elements from `a[aLeft]` to `a[aLeft + k/2 - 1]` since `a[aLeft + k/2 - 1]` is smaller than the k-th smallest element and therefore the k-th smallest element can not be among `a[aLeft]` to `a[aLeft + k/2 - 1]`. `aLeft` is the array A's left border to consider from. `bLeft` is the array B's left border to consider from.  **Note** the total number of elements in comparison is k (k/2 elements from `aLeft` to `aLeft + k/2 - 1` and k/2 elements from `bLeft` to `aLeft + k/2 - 1`). if k-th smallest elements is among `a[aLeft]` to `a[aLeft + k/2 - 1]` (assuming `a[m]`), it means that there shouldn't be any element that is larger than `a[m]`. However, at elast `b[bLeft + k/2 - 1]` is larger than `a[m]` since `b[bLeft + k/2 - 1] >= a[aLeft + k/2 - 1] >= a[m]`.
* **Base cases**:
    - If `aLeft > a.length` (finish searching array a), return `b[bLeft + k - 1]`, the k-th smallest element (must in b). 
    - If `bLeft > b.length` (finish searching array b), return `b[aLeft + k - 1]`, the k-th smallest element (must in a). 
    - If `k == 1`,  the k-th smallest elements should be the smaller one of `a[aLeft]` and `b[bLeft]`. Remember the search sapce is reduced from k -> k/2 -> ... -> 1. The k-th smallest elements should be found when `k == 1` 
* **Corner cases**:
    - If `a.length` is too small (doesn't have k/2 elements), remove elements from b first until a has k/2 elements after reducing search space (k).
    - If `b.length` is too small ((doesn't have k/2 elements)), remove elements from a first until b has k/2 elements after reducing search space (k).

There are two different ways to implement this: recursive method and iteration method. 

### Approach 1: Binary search with recursion  
Use binary search together with recursion to find $k$-th smallest elements.

The **base cases** for recursion (when to just out of recursions):
* `aLeft >= a.length`
* `bLeft >= b.length`
* `k == 1`

**Corner cases**: if a.length is too small, then remove elemnts from b first, and vice versa. For impelmentation, we can use `aVal = a[mid] >= a.length ? Integer.MAX_VALUE : a[mid]` with `mid = aLeft + k / 2 - 1` for compare.  


#### Implementation
```java
    public static int kth(int[] a, int aLeft, int[] b, int bLeft, int k){
        // aLeft and bLeft are pointers, pointing to the index whose left elments are excluded 
        // k, number of elements left to search for k-th smallest, reduced by half each iteration
        
        // Base case
        if (aLeft >= a.length){
            return b[bLeft + k - 1];
        }
        if (bLeft >= b.length){
            return a[aLeft + k - 1];
        } 
        if (k == 1){
            return Math.min(a[aLeft], b[bLeft]);
        }
        
        // index starts from left
        // the k/2-th element should be left + k/2 - 1
        int aMid = aLeft + k / 2 - 1;
        int bMid = bLeft + k / 2 - 1;

        // Special case:
        // if a.size too small, then remove elments from b first, and vice versa.
        int aVal = aMid >= a.length ? Integer.MAX_VALUE : a[aMid];
        int bVal = bMid >= b.length ? Integer.MAX_VALUE : b[bMid];

        // Comparison: <= vs. <
        // when encountering duplicates, prioritize a's elements (keep a's elements and remove b's first)
        if (aVal <= bVal)
            return kth(a, aMid + 1, b, bLeft, k - k/2);
        else
            return kth(a, aLeft, b, bMid + 1, k - k/2);

    }
```

### Approach 2: binary search with iteration
#### Implementation
```java
 public int findKSmallest(int[] nums1, int[] nums2, int k) {
        int result = new int[2];
        
        int n1 = nums1.length;
        int n2 = nums2.length;
        int i = 0; // starting index of nums1 array
        int j = 0; // starting index of nums2 array
          
        while (k > 1) {
            // Eliminate k elements based on comparison results
            if (i >= n1) { // finish searching all elments in nums1
                j = j + k - 1;
                return nums2[j];
            }
            else if (j >= n2) { // finish searching all elments in nums1
                i = i + k - 1;
                return nums1[i];
            }
            else if (i + k/2 - 1 >= n1) // not enough elements in nums1
                j = j + k/2;
            else if (j + k/2 - 1 >= n2) // not enought elements in nums2
                i = i + k/2;
            else if (nums1[i + k/2 - 1] <= nums2[j + k/2 - 1])
                i = i + k/2;
            else
                j = j + k/2;
            
            k = k - k/2; // update k to search in next iteration
        }

        // k == 1 
        return Math.min(nums1[i], nums2[j]);
 }
```

### Analysis (Time & Space)
* **Time complexity**: $\mathcal{O}(\log k)$  
Since it uses binary search to search k elements, the time complexity is $\mathcal{O}(\log k)$.
* **Space complexity**: $\mathcal{O}(1)$ as only maintaining indices.  

|     | Time Complexity | Space Complexity  
| ----- | ----- | ----- |  
| Recursive Method| $\mathcal{O}(\log k)$ | $\mathcal{O}(1)$ |  
| Iterative Method | $\mathcal{O}(\log k)$ | $\mathcal{O}(1)$ | 


