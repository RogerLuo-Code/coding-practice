---
tags:
    - Linked List
    - Slow/Fast Pointers
---

# LC876. Middle of the Linked List
## Problem Description
[LeetCode Problem 876](https://leetcode.com/problems/middle-of-the-linked-list/): Given the `head` of a singly linked list, return _the middle node of the linked list_.

If there are two middle nodes, return **the second middle** node.

## Clarification
- definition of middle, especially for even number of array
- return node value or node?

## Assumption
- no loop in the linked list

## Solution
### Approach - slow/fast pointers
Use two pointers, `slow` and `fast` pointers. Each execution, `slow` pointer moves 1 step while `fast` pointer moves 2 steps. When `fast` pointer arrives at the end, `slow` will arrive right in the middle.

=== "Python"
    ```python
    class Solution:
        def middleNode(self, head: Optional[ListNode]) -> Optional[ListNode]:
            slow = head
            fast = head

            while fast and fast.next:
                slow = slow.next
                fast = fast.next.next

            return slow
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	It takes $n/2$ steps to find the middle. Therefore, the time complexity is $O(n)$.
* Space complexity: $O(1)$
	It only needs two pointers to go through the list. Therefore, the space complexity is $O(1)$.

### Approach - b
Descriptions

```python
source code 
```

#### Complexity Analysis
* Time complexity: $O()$  
	Explanation  
* Space complexity: $O()$
	Explanation

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - a |  $O()$ 	   	   	| $O()$  
Approach - b |  $O()$      		| $O()$

## Test