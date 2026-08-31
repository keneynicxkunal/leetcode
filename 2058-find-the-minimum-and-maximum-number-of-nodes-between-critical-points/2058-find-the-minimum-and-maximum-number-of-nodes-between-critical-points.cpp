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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        
        int firstCritical = -1;
        int prevCritical = -1;
        int minDistance = INT_MAX;
        int maxDistance = -1;

        ListNode* prev = head;
        ListNode* curr = head->next;

        int index = 1;

        while (curr != nullptr && curr->next != nullptr) {
            
            ListNode* next = curr->next;

            // Check local maxima or local minima
            bool isCritical =
                (curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val);

            if (isCritical) {
                
                // First critical point
                if (firstCritical == -1) {
                    firstCritical = index;
                    prevCritical = index;
                }
                else {
                    // Distance from previous critical point
                    minDistance = min(minDistance,
                                      index - prevCritical);

                    // Distance from first critical point
                    maxDistance = index - firstCritical;

                    prevCritical = index;
                }
            }

            prev = curr;
            curr = next;
            index++;
        }

        // Fewer than two critical points
        if (maxDistance == -1) {
            return {-1, -1};
        }

        return {minDistance, maxDistance};
    }
};