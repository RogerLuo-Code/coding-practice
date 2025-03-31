---
tags:
    - Linked List
---

# 21. Merge Two Sorted Lists

## Problem Description

[LeetCode Problem 21](https://leetcode.com/problems/merge-two-sorted-lists/): You are
given the heads of two sorted linked lists `list1` and `list2`.

Merge the two lists into one **sorted** list. The list should be made by splicing
together the nodes of the first two lists.

Return _the head of the merged linked list_.

## Clarification

- Two lists may have different length. May be empty
- Two lists are sorted
- Merge nodes or merge values

## Assumption

## Solution

### Approach 1: Iteration

Start with a dummy head and then compare list1 and list 2 one node at a time. Add nodes
with smaller value to the list. Need to handle situation where either list 1 or list 2
ends first.

=== "Python"
    ```python
    class Solution:
        def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
            dummy_head = ListNode(-1, None)

            p = dummy_head
            while list1 or list2:
                if list1 is None:
                    p.next = list2
                    list2 = list2.next
                elif list2 is None:
                    p.next = list1
                    list1 = list1.next
                else:
                    if list1.val <= list2.val:
                        p.next = list1
                        list1 = list1.next
                    else:
                        p.next = list2
                        list2 = list2.next

                p = p.next

            return dummy_head.next
    ```

=== "Java"
    ```java
    class Solution {
        public ListNode mergeTwoLists(ListNode l1, ListNode l2) {

            // Handle corner case
            if (l1 == null && l2 == null) return null;
            if (l1 == null) return l2;
            if (l2 == null) return l1;

            ListNode dummyHead = new ListNode(-1);
            ListNode p = dummyHead; // pointer for the new linked list starting from dummy head
            ListNode p1 = l1; // pointer for l1 linked list
            ListNode p2 = l2; // pointer for l2 linked list

            while (p1 != null || p2 != null) {
                if (p1 == null) {
                    p.next = p2;
                    p2 = p2.next;
                }
                else if (p2 == null) {
                    p.next = p1;
                    p1 = p1.next;
                }
                else {
                    if (p1.val <= p2.val) {
                        p.next = p1;
                        p1 = p1.next;
                    }
                    else {
                        p.next = p2;
                        p2 = p2.next;
                    }
                }

                p = p.next;
            }

            return dummyHead.next;

        }
    }
    ```

#### Complexity Analysis

- Time complexity: $O(n + m)$  
  The number of iterations of the while loop equals to the sum of the lengths of the two
  lists, $n + m$.
- Space complexity: $O(1)$  
  Only use several pointers.

### Approach 2: Recursion

This problem can also be solved using recursion.

=== "Python"
    ```python
    class Solution:
        def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
            # Base case
            if list1 is None:
                return list2

            if list2 is None:
                return list1

            # Recursion
            if list1.val <= list2.val:
                list1.next = self.mergeTwoLists(list1.next, list2)
                return list1
            else:
                list2.next = self.mergeTwoLists(list1, list2.next)
                return list2
    ```

=== "Java"
    ```java
    class Solution {
        public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
            // Base case:
            if (l1 == null) return l2;
            if (l2 == null) return l1;

            // Recursively break down problem into a smaller one
            if (l1.val <= l2.val) {
                l1.next = mergeTwoLists(l1.next, l2);
                return l1;
            }
            else {
                l2.next = mergeTwoLists(l1, l2.next);
                return l2;
            }

        }
    }
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n + m)$  
  It will go through both lists (total $n + m$ nodes) one node at a time.
- Space complexity: $O(n + m)$  
  Auxiliary stack space due to recursive function calls. The recursive function will be
  called $n + m$ times.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different approaches:

Approach             | Time Complexity | Space Complexity
---------------------|-----------------|-----------------
Approach - iteration | $O(n + m)$      | $O(1)$
Approach - recursion | $O(n + m)$      | $O(n + m)$

## Test
