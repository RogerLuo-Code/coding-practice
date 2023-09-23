---
tags:
    - Linked List
---

# LC234. Palindrome Linked List
## Problem Description
[LeetCode Problem 234](https://leetcode.com/problems/palindrome-linked-list/): Given the `head` of a singly linked list, return `true` _if_ it is a __palindrome__ or `false` _otherwise_.

## Clarification

## Assumption

## Solution
### Approach - Use Array
Go through the linked list and create an array to store its values. Then compare the array to its reverse to find out if it's a palindrome.

=== "Python"
    ```python
    class Solution:
        def isPalindrome(self, head: Optional[ListNode]) -> bool:
            value_list = []
            curr = head
            while curr:
                value_list.append(curr.val)
                curr = curr.next

            start = 0
            end = len(value_list) - 1
            while start != end and end >= 0:
                if value_list[start] != value_list[end]:
                    return False
                start = start + 1
                end = end - 1
            return True
    ```

#### Complexity Analysis
* Time complexity: $O(n)$  
	Go through the whole linked list.  
* Space complexity: $O(n)$  
	Need an additional array store values of $n$ nodes.

### Approach - Reverse 2nd half
Find the middle of the linked list and reverse the 2nd half of the linked list. Then compare two halves, one starts from the head and the other starts from the head of the **reversed** 2nd half. 

=== "Python"
```python
class Solution:
    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        slow, fast = head, head

        # Find the middle
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next

        # Reverse the 2nd half list
        reversed_head_2nd_half = self.reverse(slow)

        # Compare two halves for palindrome
        is_palindrome = True
        pointer_1st_half = head
        pointer_2nd_half = reversed_head_2nd_half
        while pointer_2nd_half:
            if pointer_1st_half.val != pointer_2nd_half.val:
                is_palindrome = False
                break

            pointer_1st_half = pointer_1st_half.next
            pointer_2nd_half = pointer_2nd_half.next

        # Reverse the 2nd half back
        _ = self.reverse(reversed_head_2nd_half)

        return is_palindrome
```

#### Complexity Analysis
* Time complexity: $O(n)$  
	It takes $n/2$ steps to find the middle, and $n/2$ steps to reverse the 2nd half, $n/2$ steps to compare two halves, and then $n/2$ steps to reverse the 2nd half back. So the time complexity is $O(n)$
* Space complexity: $O(1)$  
	Just use several pointers.

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - Use Array |  $O(n)$ 	   	   	| $O(n)$  
Approach - Reverse 2nd half |  $O(n)$      		| $O(1)$

## Test