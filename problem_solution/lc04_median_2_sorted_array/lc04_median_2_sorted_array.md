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
* When total number of elments, n, is odd, the median is (n + 1)/2 th element. 
* When n is even, the median is the average of (n + 1)/2, (n + 1)/2 + 1 elements 

#### Algorithm

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
* **Time complexity**: $\mathcal{O}()$
* **Space complexity**: $\mathcal{O}()$

### Approach 2
**Median definition**: the median is the value separating the higher half from the lower half. 

**references**:  
* [Good explanation video](https://www.youtube.com/watch?v=LPFhl65R7ww&t=1013s)
* [Example solution](https://github.com/mission-peace/interview/blob/master/src/com/interview/binarysearch/MedianOfTwoSortedArrayOfDifferentLength.java)


#### Algorithm
 * Take minimum size of two array. Possible number of partitions are from 0 to m in m size array.
 * Try every cut in binary search way. When you cut first array at i then you cut second array at (m + n + 1)/2 - i
 * Now try to find the i where a[i-1] <= b[j] and b[j-1] <= a[i]. So this i is partition around which lies the median.

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
* **Time complexity**: $\mathcal{O}(\log \min(m, n))$
* **Space complexity**: $\mathcal{O}(1)$

### Complexity Summary
|     | Time Complexity | Space Complexity  
| ----- | ----- | ----- |  
| Approach 1 | $\mathcal{O}(n\log n)$ | $\mathcal{O}(n)$ |  
| Approach 2 | $\mathcal{O}(\log \min(m, n))$ | $\mathcal{O}(1)$ | 