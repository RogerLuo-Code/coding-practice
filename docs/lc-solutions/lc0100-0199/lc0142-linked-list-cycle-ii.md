---
tags:
    - Linked List
    - Slow/Fast Pointers
---

# LC142. Linked List Cycle II
## Problem Description
[LeetCode Problem 142](https://leetcode.com/problems/linked-list-cycle-ii/): Given the `head` of a linked list, return _the node where the cycle begins. If there is no cycle, return_ `null`.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the `next` pointer. Internally, `pos` is used to denote the index of the node that tail's `next` pointer is connected to (**0-indexed**). It is `-1` if there is no cycle. **Note that** `pos` **is not passed as a parameter**.

**Do not modify** the linked list.

## Clarification

## Assumption

## Solution
### Approach - Slow/fast pointers
The problem can be solved by using the Floyd’s cycle detection method to find the meet point, which consists of two phases:

- Phase I: Detect a cycle and find the meeting point if there is a cycle Use a slow pointer that moves 1 step a time and a fast pointer that moves 2 steps a time to detect a cycle and find the meeting point if there is a cycle. Follow the approach in [LC141 Linked List Cycle](lc0141-linked-list-cycle.md)
- Phase II: If there is a cycle, return the entry location of the cycle For analysis, define the following notations:
    - $l_1$: the distance (i.e., number of nodes) between the head and the entry point of the cycle
    - $l_2$: the distance (i.e., number of nodes) between the entry point and the meeting point in the cycle
    - $c$: length of the cycle
    - $n$: number of cycles the fast pointer moves ($n >= 1$)

    ```mermaid
    flowchart LR
        head((H))
        entry((E))
        meet(((M)))

        head --l1--> entry
        entry --l2--> meet
        meet --c - l2--> entry
    ```

    When slow and fast pointers meet,

    - the travel distance of the slow pointer is $l_1 + l_2$
    - the travel distance of the fast pointer is $l_1 + l_2 + nc$
    - since the fast pointer moves **twice** fast as the slow pointer, the travel distance of the fast pointer is twice as the slow pointer,

    $$ \begin{eqnarray} 
    2(l_1 + l_2) &=& l_1 + l_2 + nc \\ 
    l_1 + l_2 &=& nc \\
    l_1 &=& (n−1)c+(c−l_2) 
    \end{eqnarray} $$

    The above equation implies that the distance, $l_1$, between the head and entry point of the cycle is equal to the distance, $c - l_2$, between the meeting point and entry point along the direction of the forward movement. So we can have two pointers with the same speed (1 step a time). One starts from the head and the other starts from the meeting points. When these two pointers meet, the meeting node is where the cycle begins.

=== "Python"
    ```python
    class Solution:
        def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
            if head is None or head.next is None:
                return None

            slow = head
            fast = head
            entry = head

            while fast.next and fast.next.next:
                slow = slow.next
                fast = fast.next.next

                if slow == fast:  # there is a cycle
                    while slow != entry:  # find entry location when slow == entry
                        slow = slow.next
                        entry = entry.next

                    return entry
    ```

=== "C++"
    ```C++
    class Solution {
    public:
        ListNode *detectCycle(ListNode *head) {
            if (head == nullptr || head->next == nullptr) return nullptr;

            ListNode* slow = head;
            ListNode* fast = head;
            ListNode* entry = head;

            while (fast != nullptr && fast->next != nullptr) {
                slow = slow->next;
                fast = fast->next->next;

                // Detect a cycle and find the entry point
                if (slow == fast) {
                    while (entry != slow) {
                        entry = entry->next;
                        slow = slow->next;
                    }

                    return entry;
                }
            }

            return nullptr;
        }
    };
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
    Denotes n as the total number of nodes in the linked list. For time complexity, analyze the following two cases separately:  
    – List has no cycle: The fast pointer reaches the end first. Since it moves two steps a time, the time complexity is O(n/2).  
    – List has a cycle: For Phase I, it takes l1 + l2 iterations to find the meet point. For Phase II, it takes c − l2 iterations to find the entry point of the cycle. So the total number of iterations is l1 + l2 + c − l2 = n.
* Space complexity: $O(1)$  
	Only use several pointers.


## Test