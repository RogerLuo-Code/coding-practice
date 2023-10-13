---
tags:
    - Linked List
---

# LC143. Reorder List
## Problem Description
[LeetCode Problem 143](https://leetcode.com/problems/reorder-list/): You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln

_Reorder the list to be on the following form:_

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …

You may not modify the values in the list's nodes. Only nodes themselves may be changed.

## Clarification
- Re-order the node not the value

## Assumption

## Solution
### Approach - Stack
Use stack to store nodes. Then use one pointer, `p1`, go from head, and the other pointer, `p2`, go from end of nodes by popping from stack. Reorder the list, use `p1` and `p2`. When `p1 == p2` or `p1.next = p2`, finish the reordering

=== "Python"
    ```python
    from collections import deque

    class Solution:
        def reorderList(self, head: Optional[ListNode]) -> None:
            """
            Do not return anything, modify head in-place instead.
            """
            stack = deque()

            slow = head
            fast = head
            while fast and fast.next:
                stack.append(slow)
                slow = slow.next
                fast = fast.next.next

            front = head
            while front and stack:
                tail = stack.pop()

                if front is tail:
                    front.next = None
                    break
                elif front.next is tail:
                    tail.next = None
                    break
                else:
                    nxt = front.next
                    front.next = tail
                    tail.next = nxt
                    front = nxt
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	It takes $n$ steps to store nodes in stack and $n/2$ steps to reorder the list. So the time complexity is $O(n)$.
* Space complexity: $O(n)$  
	Use stack to store $n$ nodes.

### Approach - Split, Reverse and Merge
The problem can be solved by the following steps:
1. Split the list by two halves
2. Reverse the 2nd half
3. Merge the 1st half and the reversed 2nd half by reordering

=== "Python"
    ```python
    class Solution:
        def reorderList(self, head: Optional[ListNode]) -> None:
            """
            Do not return anything, modify head in-place instead.
            """

            if head is None or head.next is None or head.next.next is None:
                return

            head_2ndHalf = self.splitListByHalf(head)

            head_2ndHalf = self.reverseList(head_2ndHalf)

            self.mergeList(head, head_2ndHalf)

        def splitListByHalf(self, head: Optional[ListNode]) -> Optional[ListNode]:
            """
            Split the list by half and return the head of 2nd half.
            The 1st half of list will end with None
            """

            slow = head
            fast = head
            while fast and fast.next:
                prev = slow
                slow = slow.next
                fast = fast.next.next

            prev.next = None # 1st half of list end with None
            return slow

        def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
            prev = None
            curr = head

            while curr:
                nxt = curr.next
                curr.next = prev
                prev = curr
                curr = nxt

            return prev

        def mergeList(self, head1: Optional[ListNode], head2: Optional[ListNode]) -> None:
            p1 = head1
            p2 = head2

            while p1 and p2:
                nxt1 = p1.next
                nxt2 = p2.next
                p1.next = p2
                if nxt1:
                    p2.next = nxt1
                p1 = nxt1
                p2 = nxt2
    ```

=== "Java"
    ```java
    class Solution {
        public void reorderList(ListNode head) {
            // If empty, 1 or 2 nodes, no need to reorder and return
            if (head == null || head.next == null || head.next.next == null) return;

            ListNode h2 = splitListByHalf(head);

            // Reverse the 2nd half
            ListNode l2 = reverseList(h2);

            mergeList(head, l2);

        }

        private ListNode splitListByHalf(ListNode head) {
            ListNode slow = head;
            ListNode fast = head;
            ListNode prev = head;

            // Find the start of 2nd half use a slow and fast pointers
            // After while loop, slow is the start node of the 2nd half
            while (fast != null && fast.next != null) {
                prev = slow;
                slow = slow.next;
                fast = fast.next.next;
            }
            prev.next = null; // the end node of the first half point to null
            return slow;
        }

        private ListNode reverseList(ListNode head) {
            ListNode prev = null;
            ListNode curr = head;
            ListNode next;

            while (curr != null) {
                next = curr.next;
                curr.next = prev;
                prev = curr;
                curr = next;
            }

            return prev;
        }

        private void mergeList(ListNode l1, ListNode l2) {
            // Pairing
            // number of nodes in 2nd half == number of nodes in 1st half (even number nodes)
            // number of nodes in 2nd half == number of nodes in 1st half + 1 (odd number nodes)
            ListNode p1 = l1;
            ListNode p2 = l2;
            ListNode n1;  // hold next node of the first half
            ListNode n2;  // hold next node of the 2nd half
            while (p1 != null) {
                n1 = p1.next;
                n2 = p2.next;
                p1.next = p2;
                if (n1 != null) p2.next = n1;
                p1 = n1;
                p2 = n2;
            }

        }
    }
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	It takes $n/2$ steps to split the list, $n/2$ steps to reverse the list, and $n/2$ steps to merge the list. So the total steps are $3n/2$ and time complexity is $O(n)$
* Space complexity: $O(1)$  
	Just use several pointers

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Stack |  $O(n)$ 	   	   	| $O(n)$  
Approach - Split, reverse, merge |  $O(n)$      		| $O(1)$

## Test