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
    ListNode* rotateRight(ListNode* head, int k) {

        if(head==NULL) return head;
        if(head->next==NULL) return head;

        int n=0;
        ListNode *t=head;

        while(t!=NULL){
            n++;
            if(t->next==NULL) break;
            t=t->next;
        }

        k=k%n;

        if(k==0) return head;

        t->next=head;

        int x=n-k;
        ListNode *p=head;

        while(x>1){
            p=p->next;
            x--;
        }

        ListNode *ans=p->next;
        p->next=NULL;

        return ans;
    }
};