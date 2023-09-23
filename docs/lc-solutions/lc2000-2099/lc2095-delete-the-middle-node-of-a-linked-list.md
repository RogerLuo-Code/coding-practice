---
tags:
    - Linked List
    - Slow/Fast Pointers
---

# LC2095. Delete the Middle Node of a Linked List
## Problem Description
[LeetCode Problem 2095](https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/): You are given the `head` of a linked list. **Delete** the **middle node**, and return _the_ `head` _of the modified linked list_.

The **middle node** of a linked list of size `n` is the `⌊n / 2⌋th`node from the **start** using **0-based indexing**, where `⌊x⌋`denotes the largest integer less than or equal to `x`.

- For `n` = `1`, `2`, `3`, `4`, and `5`, the middle nodes are `0`, `1`, `1`, `2`, and `2`, respectively.

## Clarification
- know the head and delete the middle
- definition of the middle

## Assumption

## Solution
### Approach - Slow/fast pointers
Use slow and fast pointers to find the middle. The fast pointer move as twice faster as the slow pointer. Let **fast pointer goes first**, when it reaches the end. The slower pointer's next node is the middle specified by the condition.

???+ note
    If both fast and slow pointers starts from the **same** node, when fast pointers reaches the end, the slow pointer is the **middle** node. 

=== "Python"
    ```python
    class Solution:
        def deleteMiddle(self, head: Optional[ListNode]) -> Optional[ListNode]:
            if head is None or head.next is None:
                return None

            slow = head
            fast = head.next.next # (1)

            while fast and fast.next:
                fast = fast.next.next
                slow = slow.next

            slow.next = slow.next.next
            return head
    ```

    1. The fast pointer moves early. So the slow pointer will stays at the node before the middle one when fast reaches the end.

#### Complexity Analysis
* Time complexity: $O(n)$  
	It takes $n/2$ steps to go through the linked list and 1 step to remove the node. So the time complexity is $O(n)$.  
* Space complexity: $O(1)$  
	Just use two pointers to iterate through the list.

## Test
- Test empty node
- Test list with just one node