---
tags:
    - Linked List
---

# LC1721. Swapping Nodes in a Linked List
## Problem Description
[LeetCode Problem 1721](https://leetcode.com/problems/swapping-nodes-in-a-linked-list/): You are given the `head` of a linked list, and an integer `k`.

Return _the head of the linked list after **swapping** the values of the_ `kth` _node from the beginning and the_ `kth` _node from the end (the list is **1-indexed**)._

## Clarification

## Assumption

## Solution
### Approach - Two Pointers
Use two pointers `p_1` and `p_k` starting from head to 

- Find the k-th node from the front by moving `p_k` pointer k steps
- Find the k-th last element by moving both `p_1` and `p_k` together until `p_k` reaches the end. Note that `p_1` and `p_1` maintains the same distance `k` nodes.

=== "Python"
    ```python
    class Solution:
        def swapNodes(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
            p_1, p_k = head, head

            for _ in range(1, k):
                p_k = p_k.next

            node_k_begin = p_k

            while p_k.next:
                p_1 = p_1.next
                p_k = p_k.next

            node_k_end = p_1

            node_k_begin.val, node_k_end.val = node_k_end.val, node_k_begin.val

            return head
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Go through the whole linked list once
* Space complexity: $O(1)$  
	Only use two pointers

### Approach - Stack
Use stack to 
- store nodes and find the k-th node from the front
- pop nodes and find the k-th last element

=== "Python"
```python
from collections import deque

class Solution:
    def swapNodes(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        stack = deque()
        i = 1
        current = head

        while current:
            stack.append(current)
            if i == k:
                node_k_begin = current
            current = current.next
            i += 1

        i = 1
        while stack:
            current = stack.pop()
            if i == k:
                node_k_end = current
                break
            i += 1

        stack.clear()

        temp = node_k_begin.val
        node_k_begin.val = node_k_end.val
        node_k_end.val = temp

        return head
```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Go through the whole linke list once. 
* Space complexity: $O(n)$  
	Store the whole linked list in stack.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Two Pointers |  $O(n)$ 	   	   	| $O(1)$  
Approach - Stack |  $O(n)$      		| $O(n)$

## Test