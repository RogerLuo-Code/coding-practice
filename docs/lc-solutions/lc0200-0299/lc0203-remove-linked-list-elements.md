---
tags:
    - Linked List
---

# LC203. Remove Linked List Elements
## Problem Description
[LeetCode Problem 203](https://leetcode.com/problems/remove-linked-list-elements/): Given the `head` of a linked list and an integer `val`, remove all the nodes of the linked list that has `Node.val == val`, and return _the new head_.

## Clarification
- the whole list could be removed

## Assumption

## Solution

### Approach - Iteration
The main idea is to use two pointers,  `prev`, and `curr`, and check the following two conditions while iterating over the list:
- If `curr.val == val`, remove the current node by setting `prev.next = curr.next`
- If `curr.val != val`, simply move the `prev` pointer to `curr` node since it is a valid node and move `curr` to the next one.

=== "Python"
    ```python
    class Solution:
        def removeElements(self, head: Optional[ListNode], val: int) -> Optional[ListNode]:
            dummy = ListNode(-1, head)
            prev = dummy
            curr = head

            while curr:
                if curr.val == val:
                    prev.next = curr.next
                else:
                    prev = curr

                curr = curr.next

            return dummy.next
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Visit every node in the list
* Space complexity: $O(1)$  
	Just use limited variables for pointers and therefore constant space.


### Approach - Recursion
The problem can also be solved via recursion. The main idea to recursively call `removeElements(head.next, val)`. If the node contains the value, simply return `node.next`. Otherwise, return current node.

=== "Python"
    ```python
    class Solution:
    def removeElements(self, head: Optional[ListNode], val: int) -> Optional[ListNode]:
        if head is None:
            return None

        head.next = self.removeElements(head.next, val)

        if head.val == val:
            return head.next
        else:
            return head
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Takes $n$ function calls to go through the whole list
* Space complexity: $O(n)$  
	Function recursive call takes $O(n)$ space

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - iteration |  $O(n)$ 	   	   	| $O(1)$  
Approach - recursion |  $O(n)$      		| $O(n)$

## Test
Consider some edge cases:

- The linked list is empty, i.e., the head node is None
- Multiple nodes with the target value in a row
- The head node has the target value
- All of the nodes have the target value