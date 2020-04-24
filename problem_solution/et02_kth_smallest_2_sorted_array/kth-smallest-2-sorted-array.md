# Extended Problem 02 

## Problem
Find $k$-th smallest elements in two sorted array 

## Clarification
* How big the $k$ will be?
* Diffferent array size? Is one array size much smaller than the other?
* $k$-th correponds to index $k-1$ for zero-based indexing?
* Both array are sorted?

## Ideas
* Method 1: Direct compare elements one by one between two arrays until k-th smallest element found. 

* Method 2: extend binary search to exclude k/2 elements each execution. 

## Approaches
### Approach 1: brutal force  

### Approach 2: binary search + recursion  
Use binary search together with recursion to find $k$-th smallest elements.

Recusion base cases:
* `aLeft >= a.length`
* `bLeft >= b.length`
* `k == 1`

Special consideration: if a.length is too small, then remove elemnts from b first.
For example, a has one element and b has 10 elements. b[4] won't be the k-th smallest elements and therefore the elements before it can be removed.  




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
        int aMid = aLeft + k/2 - 1;
        int bMid = bLeft + k/2 - 1;

        // Special case:
        // if a.size too small, then remove elments from b first. Vice versa.
        int aVal = aMid >= a.length ? Integer.MAX_VALUE : a[aMid];
        int bVal = bMid >= b.length ? Integer.MAX_VALUE : b[bMid];

        if (aVal < bVal)
            return kth(a, aMid+1, b, bLeft, k - k/2);
        else
            return kth(a, aLeft, b, bMid+1, k - k/2);

    }
```

### Approach 3: binary search + iterative




## Analysis (Time & Space)



