# ET03 Find k-th Largest Elements in m Sorted Array  

## problem Description

## Approaches
* Converr the problem to one lienar space and use binary search
  - Scan all arrays and find the min and the max value.
  THe min and max determine the lower and upper bound of the search sapce 
  - Use binary search to find k-th largest element   
  `mid = lower + (upper -lower)/2` and count total number of elements (l) in all arrays ` < mid`.  
  case 1: l == k --> find solution mid  
  case 2: l < k --> lower = mid + 1  
  case 3: l > k --> upper = mid + 1


## Complexity Analysis  
* **Time complexity**: 
total number of search $\log(max - min)*m*\log(arr.length)$ where $\log(max - min)$ is binary search steps and $m*\log(arr.length)$ counter number of smaller elements in m arrays