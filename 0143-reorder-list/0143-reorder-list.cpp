class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;

        // Step 1 : Find Middle
        ListNode *slow = head;
        ListNode *fast = head;

        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2 : Reverse Second Half
        ListNode *prev = NULL;
        ListNode *curr = slow->next;
        slow->next = NULL;

        while (curr) {
            ListNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // Step 3 : Merge
        ListNode *first = head;
        ListNode *second = prev;

        while (second) {
            ListNode *temp1 = first->next;
            ListNode *temp2 = second->next;

            first->next = second;
            second->next = temp1;

            first = temp1;
            second = temp2;
        }
    }
};