class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // Dummy node handles the case when left == 1
        ListNode dummy(0);
        dummy.next = head;

        // prev will point to the node before the reversal
        ListNode* prev = &dummy;

        // Move prev to position left - 1
        for (int i = 1; i < left; i++) {
            prev = prev->next;
        }

        // Reverse nodes from left to right
        ListNode* curr = prev->next;

        for (int i = 0; i < right - left; i++) {
            ListNode* nextNode = curr->next;

            curr->next = nextNode->next;
            nextNode->next = prev->next;
            prev->next = nextNode;
        }

        return dummy.next;
    }
};