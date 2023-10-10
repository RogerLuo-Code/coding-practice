---
tags:
    - Linked List
---

# LC2. Add Two Numbers
## Problem Description
[LeetCode Problem 2](https://leetcode.com/problems/add-two-numbers/): You are given two **non-empty** linked lists representing two non-negative integers. The digits are stored in **reverse order**, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

## Clarification
- two linked list have different number of nodes
- Modify the existing node?
- Reverse order

## Assumption

## Solution
### Approach - Elementary Math
Follow the elementary math on sum, begin by summing the least-significant digits, which are the heads of l1 and l2. Summing two digits may **overflow** and needs additional variable `carry` to store overflow value.

=== "Python"
    ```python
    class Solution:
        def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
            dummy = ListNode(-1, None)

            p1 = l1
            p2 = l2
            p = dummy
            carry = 0
            while p1 or p2 or carry > 0:
                if p1 is None:
                    val1 = 0
                else:
                    val1 = p1.val
                    p1 = p1.next

                if p2 is None:
                    val2 = 0
                else:
                    val2 = p2.val
                    p2 = p2.next

                sum_node = val1 + val2 + carry
                carry = sum_node // 10
                p.next = ListNode(sum_node % 10, None)

                p = p.next

            return dummy.next
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Need to go through $max(n_1, n_2)$ nodes, where $n_1$ is the number of nodes of l1 and $n_2$ is the number of nodes of l2.
* Space complexity: $O(n)$  
	Need to create a linked list to store the sum, which contains at most $max(n1, n2) + 1$ nodes.

## Test
- one list is longer than the other
- one list is an empty list
- the sum could have an extra carry of one at the end