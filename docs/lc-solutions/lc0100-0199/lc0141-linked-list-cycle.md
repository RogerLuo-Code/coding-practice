---
tags:
    - Linked List
    - Slow/Fast Pointers
---

# LC141. Linked List Cycle
## Problem Description
[LeetCode Problem 141](https://leetcode.com/problems/linked-list-cycle/): Given `head`, the head of a linked list, determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the `next` pointer. Internally, `pos` is used to denote the index of the node that tail's `next` pointer is connected to. **Note that `pos` is not passed as a parameter**.

Return `true` _if there is a cycle in the linked list_. Otherwise, return `false`.

## Clarification
- Definition of a cycle

## Assumption

## Solution
### Approach - slow/fast pointers
The problem can be solved using slow/fast pointers:
- slow pointer moves one step every execution
- fast pointer moves two steps every execution
If there is a cycle, the two pointers will meet.

Mathematically, we are looking for $(v_{fast} - v_{slow}) * \text{n_steps} = \text{length} * n$, where 

- $v_{fast}$ is the speed of fast pointer
- $v_{slow}$ is the speed of slow pointer
- `n_steps` is the number of steps taken before meet
- `length` is the length of the linked list
- `n` is integer. We can always find a `n` to satisfy the equation, e.g., $n = v_{fast} - v_{slow}$.

=== "Python"
    ```python
    class Solution:
        def hasCycle(self, head: Optional[ListNode]) -> bool:
            if head is None or head.next is None:
                return False

            slow, fast = head, head

            while fast and fast.next:
                slow = slow.next
                fast = fast.next.next

                if slow == fast:
                    return True

            return False
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	It has go through the whole list at least once to let two pointers meet.
* Space complexity: $O(1)$  
	Use two pointers.

## Test