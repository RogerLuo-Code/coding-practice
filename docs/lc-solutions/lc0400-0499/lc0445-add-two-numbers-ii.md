---
tags:
    - Linked List
---

# LC445. Add Two Numbers II
## Problem Description
[LeetCode Problem 445](https://leetcode.com/problems/add-two-numbers-ii/): You are given two **non-empty** linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

## Clarification

## Assumption

## Solution
### Approach - Reverse
For the list, the **most** significant digit comes first and each node includes a single digit. A basic addition of two numbers start with the **least** significant digits. So we need to 

1. Reverse the given lists to get the least significant digits first same as [LC206 reverse linked list](../lc0200-0299/lc0206-reverse-linked-list.md). 
2. Then we can iterate over the reversed lists to perform the addition same as [LC2 Add two numbers](../lc0001-0099/lc0002-add-two-numbers.md). 
Once get the result list, reverse it.
3. Reverse the result list since the required result start with the most significant digit

=== "Python"
    ```python
    class Solution:
        def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
            l1_reversed = self.reverseList(l1)
            l2_reversed = self.reverseList(l2)

            sum_list = self.addTwoNumbersInternal(l1_reversed, l2_reversed)
            return self.reverseList(sum_list)

        def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
            prev = None
            curr = head

            while curr:
                nxt = curr.next
                curr.next = prev
                prev = curr
                curr = nxt

            return prev

        def addTwoNumbersInternal(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
            dummy_head = ListNode(-1, None)
            carry = 0
            tail = dummy_head

            while l1 or l2 or carry:
                if l1:
                    digit1 = l1.val
                    l1 = l1.next
                else:
                    digit1 = 0

                if l2:
                    digit2 = l2.val
                    l2 = l2.next
                else:
                    digit2 = 0

                total = digit1 + digit2 + carry
                digit = total % 10
                carry = total // 10

                new_node = ListNode(digit, None)
                tail.next = new_node
                tail = tail.next

            return dummy_head.next
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Assume $n_1$ and $n_2$ are the number of nodes in `l1` and `l2` respectively. It takes $n_1$ steps to reverse l1 list, $n_2$ steps to reverse l2 list, at most $\max(n_1, n_2) + 1$ steps to do addition, and another $\max(n_1, n_2) + 1$ steps for reversing the list. So total steps is $n_1 + n_2 + 2 \max(n_1, n_2)$.
* Space complexity: $O(n)$  
	Need to create a new list with at most $\max(n_1, n_2) + 1$ nodes. Except that, just use several pointers with $O(1)$ space. 

### Approach - Stack
In the previous approach, we reverse the linked lists to access the least significant digits first. We can also use stacks to access the least significant digits first, pushing the most significant digit to the bottom and the least significant digit to the top. Then perform digit-wise addition by popping up values from stack and considering any carry-over.

=== "Python"
    ```python
    from collections import deque

    class Solution:
        def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
            stack1 = deque()
            stack2 = deque()

            curr = l1
            while curr:
                stack1.append(curr.val)
                curr = curr.next

            curr = l2
            while curr:
                stack2.append(curr.val)
                curr = curr.next

            carry = 0
            prev = None
            while stack1 or stack2 or carry > 0:
                if stack1:
                    digit1 = stack1.pop()
                else:
                    digit1 = 0

                if stack2:
                    digit2 = stack2.pop()
                else:
                    digit2 = 0

                total = digit1 + digit2 + carry
                digit = total % 10
                carry = total // 10

                curr = ListNode(digit, prev)
                prev = curr

            return curr
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	It takes $n_1$ steps to push l1 list to stack, $n_2$ steps to push l2 list to stack, and at most $\max(n_1, n_2) + 1$ to do addition.  So the total steps are $n_1 + n_2 + \max(n_1, n_2)$
* Space complexity: $O(n)$  
	Besides new list with at most $\max(n_1, n_2) + 1$ nodes and two stacks to store $n_1$ and $n_2$ nodes respectively.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Reverse |  $O(n)$ 	   	   	| $O(1)$ except result 
Approach - Stack |  $O(n)$      		| $O(n)$ except result

## Test