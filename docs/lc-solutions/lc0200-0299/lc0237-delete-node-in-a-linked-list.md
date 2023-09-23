---
tags:
    - Linked List
---

# LC237. Delete Node in a Linked List
## Problem Description
[LeetCode Problem 237](https://leetcode.com/problems/delete-node-in-a-linked-list/): There is a singly-linked list `head` and we want to delete a node `node` in it.

You are given the node to be deleted `node`. You will **not be given access** to the first node of `head`.

All the values of the linked list are **unique**, and it is guaranteed that the given node `node` is not the last node in the linked list.

Delete the given node. Note that by deleting the node, we do not mean removing it from memory. We mean:

- The value of the given node should not exist in the linked list.
- The number of nodes in the linked list should decrease by one.
- All the values before `node` should be in the same order.
- All the values after `node` should be in the same order.

## Clarification
- Give `node` to be deleted but not the head
- Not remove it from memory just remove the value from the list

## Assumption

## Solution
### Approach - Delete value
Without knowing the previous node, it is not possible to delete the current node. Since the given node is not a tail node and all node values are unique, we can delete the next node instead and coping its value to the current node.

???+ Note
    Remember to delete the node from memory.

=== "Python"
    ```python
    class Solution:
        def deleteNode(self, node):
            """
            :type node: ListNode
            :rtype: void Do not return anything, modify node in-place instead.
            """

            if node.next:
                next_node = node.next
                node.val = next_node.val
                node.next = next_node.next

                next_node.next = None
                del next_node
    ```

#### Complexity Analysis
* Time complexity: $O(1)$  
	Since only 1 node is to be deleted. 
* Space complexity: $O(1)$  
	Use constant space to track the next node.

## Test