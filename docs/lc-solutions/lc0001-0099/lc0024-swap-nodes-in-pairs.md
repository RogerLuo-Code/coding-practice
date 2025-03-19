---
tags:
    - Linked List
---

# 24. Swap Nodes in Paris

## Problem Description

[LeetCode Problem 24](https://leetcode.com/problems/swap-nodes-in-pairs/): Given a
linked list, swap every two adjacent nodes and return its head. You must solve the
problem without modifying the values in the list's nodes (i.e., only nodes themselves
may be changed.)

## Clarification

- Swap nodes by pairs (not reversal of the whole linked list)

## Assumption

-

## Solution

### Approach 1: Recursion

We can use recursion method to swap the first two nodes and recursively process the rest.

=== "Python"
    ```python
    class Solution:
        def swapPairs(self, head: Optional[ListNode]) -> Optional[ListNode]:
            if head is None or head.next is None:
                return head

            new_head = head.next
            head.next = self.swapPairs(head.next.next)
            new_head.next = head

            return new_head
    ```

#### Complexity Analysis of Approach 1

- Time complexity: $O(n)$  
  Need to go through all $n$ nodes.
- Space complexity: $O(n)$  
  Recursion call stack will take $O(n)$ for $n$ recursive function calls.

### Approach 2: Iteration

We can use iteration method to swap the nodes on the go. We use a **dummy node** to
simplify handling the head swap and maintain a pointer (`prev`) to track the previous
node. Then swap each pair by adjusting links.

=== "python"
    ```python
    class Solution:
        def swapPairs(self, head: Optional[ListNode]) -> Optional[ListNode]:
            if head is None or head.next is None:
                return head

            dummy_head = ListNode(-1)
            prev_node = dummy_head
            curr_node = head

            while curr_node and curr_node.next:
                next_node = curr_node.next

                # Swap
                prev_node.next = next_node
                curr_node.next = next_node.next
                next_node.next = curr_node

                # Update prev and curr for next swap
                prev_node = curr_node
                curr_node = curr_node.next

            return dummy_head.next
    ```

#### Complexity Analysis of Approach 2

- Time complexity: $O(n)$  
  Go through all $n$ nodes.
- Space complexity: $O(n)$  
  Only use limited variables like dummy, prev, curr.

### Comparison of Different Approaches

The table below summarize the time complexity and space complexity of different
approaches:

Approach   | Time Complexity | Space Complexity
-----------|-----------------|-----------------
Approach - Recursion | $O(n)$          | $O(n)$
Approach - Iteration | $O(n)$          | $O(1)$

## Test

- Empty list (None)
- Only one node (`[1]`)
- Odd number of nodes (`[1,2,3]`) → The last node remains in place
