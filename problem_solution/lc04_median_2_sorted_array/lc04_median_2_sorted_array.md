# LeetCode Problem 4 - Median of Two Sorted Arrays

## Problem Description
[LeetCode Problem 4](https://leetcode.com/problems/median-of-two-sorted-arrays/): There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)). You may assume nums1 and nums2 cannot be both empty.Description

## Analysis
* Clarification:
  - sorted vs. unsorted?
  - different sizes?
  - any duplicates?
  - median definition?
  - data type?
  - time complexity requirement?
* Go through examples
* Solution:
  - Assumption: at least one array is not emepty
  - Input/Output: int[] array, int[] array; double
  - Corner case
  - Algorithm: binary search kth smallest elements or binary search partition position
  - Time/space complexity
* Coding
* Test
  - Test corner cases
  - Test general cases: total number is odd and even

## Approach
Based on definiton and properties of median, we can come up with two different approaches.

### Approach 1
**Median definition**: the median is the "middle" of a sorted list of numbers. $\text{median}(x) = (x \lfloor (n+1)/2 \rfloor + x \lceil (n+1)/2 \rceil)/2$, where $x$ is an ordered list of $n$ numbers, and $\lfloor \cdot \rfloor$ and $\lceil \cdot \rceil$ denotes the [floor and ceiling functions](https://en.wikipedia.org/wiki/Floor_and_ceiling_functions), respectively.
* If n is odd, the median is (n + 1)/2 th element. 
* If n is even, the median is the average of (n + 1)/2 th and (n + 1)/2 + 1 th elements 

Based on the median definition, we can convert the problem to find (m + n + 1)/2 th smallest elements, where m and n are total number of array 1 and array 2, respectively. The algorithm of finding k-th smallest element is explained [here](../et02_kth_smallest_2_sorted_array/et02_kth_smallest_2_sorted_array.md).


#### Implementation
```java
class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        // if (nums1 == null || nums1.length == 0 || nums2 == null || nums2.length == 0)
        //     return Double.NaN;
        
        int k = (nums1.length + nums2.length + 1)/2;
        
        if ((nums1.length + nums2.length)%2 == 0)
            return ((double) findKSmallest(nums1, nums2, k) + (double) findKSmallest(nums1, nums2, k+1))/2;
        else
            return findKSmallest(nums1, nums2, k);
    }
    
    public int findKSmallest(int[] nums1, int[] nums2, int k) {
        int n1 = nums1.length;
        int n2 = nums2.length;
        int i = 0; // starting index of nums1 array
        int j = 0; // starting index of nums2 array
          
        while (k >= 1) {
            // Eliminate k elements based on comparison results
            if (i >= n1) { // finish searching all elments in nums1
                return nums2[j + k - 1];
            }
            else if (j >= n2) { // finish searching all elments in nums1
                return nums1[i + k - 1];
            }
            else if (k == 1)
                return nums1[i] <= nums2[j] ? nums1[i] : nums2[j];
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
        
        return 0;
    }
}
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(\log (m+n))$  
Since binary search is used to find (m + n + 1)/2 th smallest element, the time complexity is $\mathcal{O}(\log ((m + n + 1)/2)) \rightarrow \mathcal{O}(\log (m+n))$
* **Space complexity**: $\mathcal{O}(1)$ as using several internal variables.

### Approach 2
**Median definition**: the median is the value separating the higher half from the lower half. 

**references**:  
* [Good explanation video from Tushar Roy](https://www.youtube.com/watch?v=LPFhl65R7ww&t=1013s)
* [Example solution from Tushar Roy](https://github.com/mission-peace/interview/blob/master/src/com/interview/binarysearch/MedianOfTwoSortedArrayOfDifferentLength.java)
* [LeetCode solution](https://leetcode.com/articles/median-of-two-sorted-arrays/)

Based on the the use of median for dividing, we can find partition position at two arrays and obtain the median value:
1. Cut A into two parts at a random position i:
```
          left_A             |        right_A
    A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]
```
Since A has m elements, so there are m + 1 cuttings (i = 0 ~ m). left_A length is i and right_A length is m - i. Note when `i = 0`, left_A is empty, and when `i = m`, right_A is empty.  

2. Similarly cut B into two parts at a random position j:
```
          left_B             |        right_B
    B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]
```
Since B has n elements, left_B length is j and right_B length is m - j. Note when `j = 0`, left_B is empty, and when `j = n`, right_B is empty.

3. Put left_A and left_B into one set, left_part, and put right_A and right_B into another set, right_part:
```
          left_part          |        right_part
    A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]
    B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]
```
If we can ensure:
* `len(left_part) == len(right_part)` for even number of (m+n), or `len(left_part) == len(right_part) + 1` for odd number of (m+n)   
`i + j = m - i + n - j` when `m + n` is even; `i + j = m - i + n - j + 1` when `m + n` is odd. if `n >= m`, we can simplify `i = 0 ~ m` and `j = (m + n + 1)/2 - i`. Note `(m + n + 1)/2` works for both odd and even caes.ß   
* `max(left_part) <= min(right_part)`
Just check `B[j - 1] <= A[i]` and `A[i - 1] <= B[j]`. Since A and B are sorted, `A[i - 1] <= A[i]` and `B[j - 1] <= B[j]` and therefore no need to compare.   

Then the median can compute from the middle 4 elements (A[i-1], B[j-1], A[i], and B[j]). 
* `max(A[i - 1], B[j - 1])`, when m + n is odd
* `(max(A[i -1], B[j - 1]) + min(A[i], B[j]))/2`, when m + n is even


The **algorithm** is simpled as:
```
Searching i in [0, m] to find an object i such that:
    B[j - 1] <= A[i] and A[i - 1] <= B[j], where j = (m + n + 1)/2 - i
```
We can use binary search method to search i (j is changed acoordingly). There are 3 situtions to consider:
* `B[j - 1] <= A[i]` and `A[i - 1] <= B[j]`  
The object is found and stop searching.
*  `B[j - 1] > A[i]`  
Means A[i] is too small. We need to adjust i to get `B[j - 1] <= A[i]`.
    - Can we increase i?  
    Yes, Because when i is increased (A[i] is increased), j will be decreased (B[j - 1] is decreased). So the search range is changed to [i + 1, right].
    - Can we decrease i?  
    No! Because wehn i is decreased (A[i] is decreased further), j will be increased (B[j - 1] is increased further). Therefore, `B[j - 1] <= A[i]` will be never satisfied.  
* `A[i - 1] > B[j]`  
Means A[i - 1] is too big. And we must decrease i to get `A[i - 1] <= B[j]`. SO the search range is changed to [left, i - 1].

**Edge Case**: `A[i - 1]` doesn't exist when `i == 0`; `A[i]` doesn't exist when `i == m`; `A[j - 1]` doesn't exist when `j == 0`, `A[j]` doesn't exist when `j == n`. We can ignore non-exist elements in the calculation and comparison.

#### Implementation
```java
class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        if ((nums1 == null || nums1.length == 0) && (nums2 == null || nums2.length == 0))
            return Double.NaN;
        
        if (nums1.length > nums2.length)
            return findMedianSortedArrays(nums2, nums1);
        
        int m = nums1.length;
        int n = nums2.length;
        
        int left = 0;
        int right = m; // not m - 1, since this is partition position, which can be 0 ~ m (inclusive)
        int i; // partition position for array nums 1 
        int j; // partition position for array nums 2
        
        // Binary search of partition position
        while (left <= right) {
            i = left + (right - left)/2;
            j = (m + n + 1)/2 - i; // (m + n + 1)/2 is the index of median
            
            // handle edeg cases:
            int maxLeft1 = i == 0 ? Integer.MIN_VALUE : nums1[i - 1];
            int maxLeft2 = j == 0 ? Integer.MIN_VALUE : nums2[j - 1];
            
            int minLeft1 = i == m ? Integer.MAX_VALUE : nums1[i];
            int minLeft2 = j == n ? Integer.MAX_VALUE : nums2[j];
            
            // Corner case: i == 0 or m, j == 0 or n
            if (maxLeft1 > minLeft2)
                right = i - 1;
            else if (maxLeft2 > minLeft1)
                left = i + 1;
            else  { // found: nums1[i - 1] <= nums2[j], nums2[i - 1] <= nums1[i]
                if ((m + n)%2 == 0) // even number
                    return (double) (Math.max(maxLeft1, maxLeft2) + Math.min(minLeft1, minLeft2))/2;
                else
                    return (double) Math.max(maxLeft1, maxLeft2);
            }
        }
        
        return Double.NaN;
    }
}
```

#### Complexity Analysis 
* **Time complexity**: $\mathcal{O}(\log (\min(m, n)))$  
Since we only binary search the array with smaller the size, the time complexity is $\mathcal{O}(\log (\min(m, n)))$ 
* **Space complexity**: $\mathcal{O}(1)$ as using several internal variables. 

### Complexity Summary
|     | Time Complexity | Space Complexity  
| ----- | ----- | ----- |  
| Approach 1 | $\mathcal{O}(\log (m + n))$ | $\mathcal{O}(1)$ |  
| Approach 2 | $\mathcal{O}(\log (\min(m, n)))$ | $\mathcal{O}(1)$ | 