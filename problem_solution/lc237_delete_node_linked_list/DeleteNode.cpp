// Solution:
//  - since it is a singly-linked list, we don't the node before the deleted node
//  - What we can do is to modify the current node with the value and connection of next node. Remember to delete next node to release memory
//  - Assumption the node to be deleted is no the tail of the list
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode* next = node->next;
        
        // Update the current node to duplicate the next node
        node->val = next->val;
        node->next = next->next;
        
        // Delete next node
        delete next;
    }
};