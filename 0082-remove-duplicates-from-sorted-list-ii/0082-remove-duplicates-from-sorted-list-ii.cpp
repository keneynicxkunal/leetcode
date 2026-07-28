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
    ListNode* deleteDuplicates(ListNode* head) {

        ListNode *d=new ListNode(0);
        d->next=head;

        ListNode *a=d;
        ListNode *b=head;

        while(b!=NULL){

            int f=0;

            while(b->next!=NULL && b->val==b->next->val){
                b=b->next;
                f=1;
            }

            if(f){
                a->next=b->next;
            }
            else{
                a=a->next;
            }

            b=b->next;
        }

        return d->next;
    }
};