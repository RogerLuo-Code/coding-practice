---
tags:
    - Linked List
    - Stack
---

# LC92. Reverse Linked List II
## Problem Description
[LeetCode Problem 92](https://leetcode.com/problems/reverse-linked-list-ii): Given the `head` of a singly linked list and two integers `left` and `right` where `left <= right`, reverse the nodes of the list from position `left` to position `right`, and return _the reversed list_.

## Clarification

## Assumption

## Solution
### Approach - Iteration
The problem can be solved using iterations. [@hi-malik](https://leetcode.com/problems/reverse-linked-list-ii/solutions/2311084/java-c-tried-to-explain-every-step/) explains really well how to solve this problme using an iterative method. The basic idea is to reverse the node one-by-one by using 3 pointers, `prev`, `curr`, and `forw`:

- `curr.next = forw.next`
- `forw.next = curr.next or prev.next`, not sure and need to use an example to find whether to use `curr.next` or `prev.next`
- `prev.next = forw`
- `forw = curr.next`

Moreover, a dummy head is used to handle the case where `left = 1` and `prev` is assigned with the dummy head.

=== "Python"
    ```python
    class Solution:
        def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
            dummy = ListNode(0, head)
            prev = dummy

            for i in range(left - 1): # 0 ~ left - 2
                prev = prev.next  # 1 ~ left - 1

            curr = prev.next # left
            for i in range(right - left):
                forw = curr.next
                curr.next = forw.next
                forw.next = prev.next
                prev.next = forw

            return dummy.next
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Iteration through the list $O(right)$ time and worst case $O(n)$
* Space complexity: $O(1)$  
	Store 4 pointers (prev, curr, forw, and dummy)

### Approach - Stack
Use stack to store the sublist that need to be reversed. After filling it up, then pop it up one by one and reverse the sublist easily. [@vanAmsen](https://leetcode.com/problems/reverse-linked-list-ii/solutions/4011862/92-40-two-pointers-stack-recursion/) provides a good solution on using stack.

In Python, using `deque` is better than `list` in expanding memory when growing stack.

=== "Python"
    ```python
    from collections import deque

    class Solution:
        def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
            dummy = ListNode(0, head)
            prev = dummy
            stack = deque()

            for _ in range(left - 1):
                prev = prev.next  # prev: 1 ~ left - 1

            current = prev.next # left

            for _ in range(right - left + 1):
                stack.append(current)
                current = current.next

            while stack:
                prev.next = stack.pop()
                prev = prev.next

            prev.next = current

            return dummy.next
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Need to go through the linked list in worst case, which takes $O(n)$ time when right == n.
* Space complexity: $O(n)$  
	Need $O(n)$ space for stack. 

### Approach - Recursion
The problem can be solved using recursion but difficult to find clean solution. [WarrenChen](https://leetcode.com/problems/reverse-linked-list-ii/solutions/30673/why-nobody-does-it-with-recursion-shouldn-t-the-code-be-simpler/) shares a recursive method that is relative easy to follow.

=== "Python"
    ```python
    class Solution:
        def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
            if left == right:
                return head

            if left > 1:
                head.next = self.reverseBetween(head.next, left - 1, right - 1) # head will be changed in side of the function
                return head
            else:
                next = head.next
                new_head = self.reverseBetween(next, 1, right - 1)
                next_next = next.next
                next.next = head
                head.next = next_next
                return new_head
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Need to do recursion $O(right)$ time and worst case is $O(n)$ when right == n.
* Space complexity: $O(n)$  
	Need $O(n)$ space to store recursion function call.  

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - iteration |  $O(n)$ 	   	   	| $O(1)$  
Approach - stack |  $O(n)$      		| $O(n)$
Approach - recursion |  $O(n)$      		| $O(n)$

## Test
