---
tags:
    - Linked List
---

# LC23. Merge k Sorted Lists
## Problem Description
[LeetCode Problem 23](https://leetcode.com/problems/merge-k-sorted-lists/): You are given an array of `k` linked-lists `lists`, each linked-list is sorted in ascending order.

_Merge all the linked-lists into one sorted linked-list and return it._

## Clarification

## Assumption

## Solution
### Approach - Recursion
Break down merge k lists into subproblem of merge two lists by recursively merging two sub-lists.

=== "Python"
    ```python
    class Solution:
        def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
            n = len(lists)
            # Base case
            if not lists:
                return None
            elif n == 1:
                return lists[0]
            elif n == 2:
                return self.mergeTwoLists(lists[0], lists[1])

            return self.mergeTwoLists(self.mergeKLists(lists[0:n//2]), self.mergeKLists(lists[n//2:]))

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

#### Complexity Analysis
* Time complexity: $O(k n \log_2 k)$  
	We can pply the same idea as the merge sort algorithm, by merging the first array with the second, the third with the fourth, and so on and then repeatedly apply this until all of the arrays have been merged. We do $O(kn)$ work to merge the k arrays of size n into k/2 arrays of size 2n, and then continue doing $O(kn)$ work $O(log_2k)$ times until we have a single array of size kn. Thus, the running time of this approach is $O(kn log k)$
    ```
           1             1 list with kn elements
         /   \
        1     2          2 sub lists with (k/2)n elements
      /  \   /  \
     1    2 3   4        4 sub lists with (k/4)n elements
     ....                k/2 sub lists with 2n elements
     ...                 k sub lists with n elements
    ```
* Space complexity: $O(\log_2 k)$  
	The function recursive call depth is $\log_2 k$.

### Approach - Iteration
Descriptions

=== "Java"
    ```java
    class Solution {
        public ListNode mergeKLists(ListNode[] lists) {
            if (lists == null || lists.length == 0) return null;

            int n = lists.length;

            for (int step = 1; step < n; step = 2*step) {
                for (int i = 0; i < n - step; i = i + 2*step) {
                    lists[i] = merge2Lists(lists[i], lists[i+step]);
                }
            }

            return lists[0];

        }

        private ListNode merge2Lists(ListNode l1, ListNode l2) {
            if (l1 == null) return l2;
            if (l2 == null) return l1;

            ListNode dummyHead = new ListNode(-1);
            ListNode p = dummyHead; 

            while (l1 != null || l2 != null) {
                if (l1 == null) {
                    p.next = l2;
                    break;
                }
                else if (l2 == null) {
                    p.next = l1;
                    break;
                }
                else if (l1.val <= l2.val) {
                    p.next = l1;
                    l1 = l1.next;
                }
                else {
                    p.next = l2;
                    l2 = l2.next;
                }
                p = p.next;
            }

            return dummyHead.next;
        }
    }
    ```

#### Complexity Analysis
* Time complexity: $O()$  
	Explanation  
* Space complexity: $O()$  
	Explanation

### Comparison of Different Approaches
The table below summarize the time complexity and space complexity of different approaches:

Approach 	 | Time Complexity 	| Space Complexity  
------------ | --------------- 	| ----------------
Approach - a |  $O()$ 	   	   	| $O()$  
Approach - b |  $O()$      		| $O()$

## Test