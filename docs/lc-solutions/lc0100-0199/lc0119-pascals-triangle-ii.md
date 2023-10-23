---
tags:
    - Array
    - Math
    - Dynamic Programming
---

# LC119. Pascal's Triangle II
## Problem Description
[LeetCode Problem 119](https://leetcode.com/problems/pascals-triangle-ii/): Given an integer `rowIndex`, return the `rowIndexth` (**0-indexed**) row of the **Pascal's triangle**.

In **Pascal's triangle**, each number is the sum of the two numbers directly above it as shown:

![](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)

## Clarification

## Assumption

## Solution
### Approach - Math
Each row (0-indexing) of Pascal's triangle is the [binomial coefficients](https://en.wikipedia.org/wiki/Binomial_coefficient): $C(r, 0),\; C(r, 1),\; \cdots,\; C(r, r)$, where $C(r, 0) = C(r, r) = 1$ and $C(r, k) = \frac{n!}{k! (n-k)!}$.

There are two main recurrence relation can be derived from $C(r, k)$ equation:

1. Between two rows: $C(r, k) = C(r - 1, k - 1) + C(r - 1, k)$, i.e., Pascal's triangle
2. Within a row: $C(r, k) = C(r, k - 1) \frac{r - k + 1}{k}$

??? Derivation
    Derive the 2nd recurrence relation as follows:

	$$ \begin{eqnarray} 
    C(r, k) &=& C(r, k - 1) \frac{r - k + 1}{k} \\ 
    C(r, k + 1) &=& C(r, k) \frac{r - k}{k + 1} \\ 
    C(r, k + 2) &=& C(r, k+ 1) \frac{r - k - 1}{k + 2} \\
	&\vdots&
    \end{eqnarray} $$

	The above equation can be rewritten as:

	$$ \begin{eqnarray} 
    C(r, k') &=& C(r, k' - 1) \frac{r - k' + 1}{k' + 1} ~ \text{with} \; k' = k, k + 1, k + 2, \cdots\\ 
    \end{eqnarray} $$

We can use the 2nd recurrence elation within a row to directly compute consecutive binomial coefficients in the same row.

=== "Python"
	```python
	class Solution:
		def getRow(self, rowIndex: int) -> List[int]:
			row = [1] * (rowIndex + 1)
			for i in range(1, rowIndex):
				row[i] = row[i - 1] * (rowIndex - i + 1) // i

			return row
	```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Directly computing the row elements via $n - 1$ steps for $n$th row of Pascal triangle.
* Space complexity: $O(n)$  
	The result contains $n$ elements for $n$-th row

### Approach - DP Iteration
The problem can be solved by iteratively computing from $0$th to $n$th row of Pascal triangle by using the first recurrence relation shown above.

=== "Python"
	```python
	class Solution:
		def getRow(self, rowIndex: int) -> List[int]:
			if rowIndex == 0:
				return [1]

			if rowIndex == 1:
				return [1, 1]

			row_i_above = [1, 1]
			for i in range(2, rowIndex + 1):
				row_i = [1] * (i + 1)
				for j in range(1, i):
					row_i[j] = row_i_above[j - 1] + row_i_above[j]
				row_i_above = row_i

			return row_i
	```

#### Complexity Analysis
* Time complexity: $O(n^2)$  
	Use two for-loops to go through each element of each row
* Space complexity: $O(n)$  
	Stores two rows' elements

### Approach - DP Recursion
The problem can be solved by recursively call function itself to compute the row above until reach the base cases. The base cases are $[1]$ for $0$th row and $[1, 1]$ for $1$st row.

=== "Python"
	```python
	class Solution:
		def getRow(self, rowIndex: int) -> List[int]:
			# Base case
			if rowIndex == 0:
				return [1]

			if rowIndex == 1:
				return [1, 1]

			# Recursion
			row_above = self.getRow(rowIndex - 1)
			row_current = [1] * (rowIndex + 1)
			for i in range (1, rowIndex):
				row_current[i] = row_above[i-1] + row_above[i]

			return row_current
	```

#### Complexity Analysis
* Time complexity: $O(n^2)$  
	The function will be recursively calling $n$ times and within each function there is a for-loop to go through all elements. Therefore, the time complexity is $O(n)$
* Space complexity: $O(n)$  
	Store two rows + function call stack. 

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Math |  $O(n)$ 	   	   	| $O(n)$  
Approach - DP iteration |  $O(n^2)$      		| $O(n)$
Approach - DP recursion |  $O(n^2)$      		| $O(n)$

## Test