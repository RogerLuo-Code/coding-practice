"""206 Reverse Linked List II
Test solution of LC problem 206 locally
"""

#    None <- 3 5]
#            h
#              p
#           lp
# i: 2
# l: 1
# r: 2
# lp_prev: none
# lp: 1
# rp: 2
# rp_next: none

from typing import Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
        i = 1
        prev = None
        left_node_prev = None
        # right_node = None
        # left_node = None
        # right_node_after = None
        dummy = ListNode(0, head)
        pointer = head
        while i <= right and pointer and left != right:
            if i == left - 1:
                left_node_prev = pointer
            elif i == left:
                left_node = pointer
            elif i == right:
                right_node = pointer
                right_node_after = pointer.next

            next_node = pointer.next
            if i >= left and i <= right:
                pointer.next = prev
                prev = pointer

            if i == right:
                if not left_node_prev:
                    dummy.next = right_node
                elif left_node_prev and right_node and left_node_prev != right_node:
                    left_node_prev.next = right_node
                if left_node and right_node_after and left_node != right_node_after:
                    left_node.next = right_node_after

            pointer = next_node
            i += 1

        return dummy.next


if __name__ == "__main__":
    node_list = []
    node_list.append(None)
    for i in range(1, 6):
        node_list.append(ListNode(i, None))

    for i in range(1, 5):
        node_list[i].next = node_list[i + 1]

    solution = Solution()
    solution.reverseBetween(node_list[1], 2, 4)
