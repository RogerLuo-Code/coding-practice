---
tags:
    - Linked List
    - Stack
---

# LC206. Reverse Linked List
## Problem Description
[LeetCode Problem 206](https://leetcode.com/problems/reverse-linked-list/): Given the head of a singly linked list, reverse the list, and return the reversed list. For example, change `1 -> 2 -> 3 -> 4 -> 5` to `5 -> 4 -> 3 -> 2 -> 1`.

## Clarification
- singly linked list

## Assumption

## Solution
### Approach - Iteration
The problem can be solved via iteration. For each node, switch pointing direction from right to left. [@Ajna](https://leetcode.com/problems/reverse-linked-list/solutions/803955/c-iterative-vs-recursive-solutions-compared-and-explained-99-time-85-space/) provides some good explanations.


![](assets/reverse-linked-list.gif)

=== "Python"
    ```python
    class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        prev_node = None
        while head is not None:
            next_node = head.next
            head.next = prev_node
            prev_node = head
            head = next_node

        return prev_node
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Go through the whole linked list
* Space complexity: $O(1)$  
	Only need to store previous, current and next nodes.

### Approach - Recursion
The problem can be solved via recursive methods. There are two different ways:

1. Create a new helper function and find that it is easy to understand and clear
2. Re-use the existing function signature. 

Refer to [@tusizi](https://leetcode.com/problems/reverse-linked-list/solutions/58127/python-iterative-and-recursive-solution/) solution and comments from @christopherpace86

=== "Python"
    ```python
    class Solution:
        def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
            return self._reverseList(head)

        def _reverseList(self, curr: Optional[ListNode], prev: Optional[ListNode]=None) -> Optional[ListNode]:
            if not curr:
                return prev

            next = curr.next
            curr.next = prev
            return self._reverseList(next, curr)
    ```


function call
```
call #1: curr: 1, prev: None, next: 2, reverse [1, 2, 3, 4, 5]
         reverse link from 1 -> 2 to 1 -> none
         return 5
call #2: curr: 2, prev: 1, next: 3, reverse [2, 3, 4, 5]
         reverse linke form 2 -> 3 to 2 -> 1
         return 5
call #3: curr: 3, prev: 2, next 4, reverse [3, 4, 5]
         reverse link from 3 -> 4 to 3 -> 2
         return 5
call #4  curr: 4, prev: 3, next: 5, reverse [4, 5]
        reverse link from 4 -> 5 to 4 -> 3
        return 5
call #5  curr: 5, prev: 4, next: none, reverse [5]
        reverse link from 5 -> none to 5 -> 4;
        return 5
call #6 curr: none, prev: 5 base case
        return 5
```

=== "Python - Recursion II"
    ```python
    class Solution:
        def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
            if not head or not head.next:
                return head

            node = self.reverseList(head.next)
            head.next.next = head
            head.next = None
            return node
    ```

Function call
```
call #1: head: 1
         node: 5
         add link: 1 -> <- 2
         remove link: 1 <- 2
         return 5
call #2: head: 2
         node: 5
         add link: 2 -> <- 3
         remove link: 2 <- 3
         return 5
call #3: head: 3
         node: 5
         add link: 3 -> <- 4
         remoe linke: 3 <- 4
         return 5
call #4: head: 4, 
        node: 5 (after return)
        Add link <-, so 4 -> <- 5  (<- added)
        remove link (->),  4 <- 5
        return 5
call #5: head: 5, return 5
```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Go through the whole linked list and therefore is $O(n)$  
* Space complexity: $O(n)$  
	Recursive call to store function pointers and at most $n$ times. 

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Iteration |  $O(n)$ 	   	   	| $O(1)$  
Approach - Recursion |  $O(n)$      	| $O(n)$

## Test