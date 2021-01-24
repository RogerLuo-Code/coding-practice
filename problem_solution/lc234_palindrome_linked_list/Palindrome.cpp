// Clarification:
//  - What is palindrome?
// Solution:
//  - Create a vector<int> to store all values while iterate through the whole list
//  - Then check the vector<int>
//  -
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
    bool isPalindrome(ListNode* head) {
        // Mehtod 1:
//         if (head == nullptr) return true;
        
//         vector<int> values;
        
//         // Go through linked list and store all values
//         for (ListNode* p = head; p != nullptr; p = p->next) {
//             values.push_back(p->val);
//         }
        
//         // Check whether it is palindrome
//         int i = 0;
//         int j = values.size() - 1;
        
//         while (i <= j) {
//             if (values[i] != values[j]) {
//                 return false;
//             }
//             i++;
//             j--;
//         }
        
//         return true;
        
        
        // Method 2:
        if (head == nullptr) return true;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Reverse the right half 
        ListNode* p2ndHalf = reverse(slow);
        ListNode* p = head;
        
        while (p2ndHalf != nullptr) {
            if (p2ndHalf->val != p->val) {
                return false;
            }
            p2ndHalf = p2ndHalf->next;
            p = p->next;
        }
        
        return true;   
    }
    
    ListNode* reverse(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next = nullptr;
        
        while (curr != nullptr) {
            next= curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};