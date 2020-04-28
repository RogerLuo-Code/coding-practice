# LeetCode Problem - Find K Closest Elements  

## Problem Description  
[LeetCode Problem 658:](https://leetcode.com/problems/find-k-closest-elements/) Given a sorted array, two integers k and x, find the k closest elements to x in the array. The result should also be sorted in ascending order. If there is a tie, the smaller elements are always preferred.

## Clarification and potential variations
* Find k elements vs. kth element?
* Sorted vs unsorted?
* Duplecate elements (target, or any element in the result) handling? 
* return data - sorted or uns0rted? ascending or descending? what about empty?
* K <=0 and K > array length?

## Approaches  
1. For unsorted array, sort the element first by absolute difference values to the target. The result is in the first k elements.   
2. For sorted array, we can use binary search to speed up the search with the following two steps:   
  1). Use binary search to find two closest elements around the target  
  2). Find k closest elements from starting postions of step 1)  

### Approcach 1
Sort the element first by absolute difference values to the target. The result is in the first k elements. Before return, remember to sort the k elements since it requires the result sorted in ascending order. This approach can be used for both sorted and unsorted array. 

* To use `Collections.sort`, the input array is copied to an array list. 
* `Collection.sort` is used twice -- 1) sort the whole array based on distance from target and 2) sort the k elements in the result based on the value 
* [`Collection.sort` uses mergesort](https://docs.oracle.com/en/java/javase/14/docs/api/java.base/java/util/List.html#sort(java.util.Comparator)) and has $n \log n$ comparison for general case. 
* The [`subList` function of ArrayList](https://docs.oracle.com/en/java/javase/14/docs/api/java.base/java/util/ArrayList.html#subList) return a view of the portion of original list. Any operations on the sub list is actully happening on the original list. 
* The total number of executions (inclusing array copy and sort): $n + \mathcal{O}(n \log n) + \mathcal{O}(k \log k)$

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
       
        // Sort to return elments in order
        Collections.sort(arrList);
        return arrList;
    }
}
```

### Approach 2
Approach 2 has two different methods to find k smallest elements:    
* Have two pointers starting at positions from step 1) and move to left or right based on the comparison result.  
*  Use binary search idea again     
If `arr[pointLeft - k/2]` is closer to target compared with `arr[pointLeft + k/2]`, then all elements from `pointLeft - k/2` to `pointLeft` should be included in the result.  
Next step compare `arr[pointLeft - k/2 - k/4]` and `arr[pointRight + k/4`  
Using recursion will be 
`k, (p1, p1+1, k)`, `k/2, (p1 - k/2, p2 + 1, k - k/2)`,   
This method can achive $\mathcal{O}(\log k)$ time complexity on find indices but still need $\mathcal{O}(k)$ to return elements since copying is conducted 1 position at a time. 

    

