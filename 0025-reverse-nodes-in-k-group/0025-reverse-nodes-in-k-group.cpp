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
    ListNode* reverseKGroup(ListNode* head, int k) {

        if(head==NULL) return head;

        ListNode *ans=new ListNode(0);
        ans->next=head;

        ListNode *a=ans;
        ListNode *b=head;

        while(1){

            int c=0;
            ListNode *t=b;

            while(t!=NULL && c<k){
                t=t->next;
                c++;
            }

            if(c<k) break;

            ListNode *p=t;
            ListNode *q=b;

            while(c--){
                ListNode *x=q->next;
                q->next=p;
                p=q;
                q=x;
            }

            a->next=p;

            a=b;
            b=t;
        }

        return ans->next;
    }
};