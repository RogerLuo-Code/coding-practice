// Clarification:
//  - remove nodes with target value
// Solution:
//  - iterate all nodes, remove the node when haing the value
//  - remove head, middle, and tail

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    // NULL   1 -> 2 -> 3, val = 2
    //  p/n   c
    //   p     c    n
    //        p    c    n
    //        p         c/n
    ListNode* removeElements(ListNode* head, int val) {
        if (head == nullptr) return head;
        
//         ListNode* prev = nullptr;
//         ListNode* curr = head;
//         ListNode* next = nullptr;
        
//         while (curr != nullptr) {
//             next = curr->next;
//             if (curr->val == val) {
//                 // remove node
                
//                 if (prev == nullptr) {
//                     // curr node is the head
//                     delete curr;
//                     curr = next;
//                     head = next;
//                 }
//                 else {
//                     delete curr;
//                     prev->next = next;
//                     curr = next;
//                 }
//             }
//             else {
//                 prev = curr;
//                 curr = next;
//             }    
//         }
        
//         return head;
        
        // Use dummy head
        ListNode* dummyHead = new ListNode(-1, head);
        ListNode* next = nullptr;
        
        ListNode* curr = dummyHead;
        while (curr->next != nullptr) {
            if (curr->next->val == val) {
                next = curr->next;
                curr->next = next->next;
                delete next;
            }
            else {
                curr = curr->next;
            }
        }
        
        return dummyHead->next;
    }
};