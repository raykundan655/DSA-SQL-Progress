// 328. Odd Even Linked List
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
    ListNode* oddEvenList(ListNode* head) {
        if(head==nullptr){
            return head;
        }
        else{
            int size=0;
            ListNode * temp=head;
            while(temp!=nullptr){
                temp=temp->next;
                size++;
            }
            ListNode * curr=new ListNode();
            ListNode * pre=curr;
            ListNode * tem=head;
            for(int i=0;i<size;i++){
                if(i%2==0){
                    ListNode * ll=new ListNode(tem->val);
                    pre->next=ll;
                   pre=pre->next;
                }
                tem=tem->next;
            }
            tem=head;
            for(int i=0;i<size;i++){
                if(i%2!=0){
                    ListNode * ll=new ListNode(tem->val);
                    pre->next=ll;
                   pre=pre->next;
                }
                tem=tem->next;
            }

            return curr->next;
        }
    }
};
