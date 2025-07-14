// Middle of the Linked List
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
    ListNode* middleNode(ListNode* head) {
        if(head==nullptr){
            return head;
        }
        else{
            ListNode * fast=head,*slow=head;
            while(fast!=nullptr && fast->next!=nullptr){
                
                slow=slow->next;
                fast=fast->next->next;
            }
                   head=slow;
                   return head;
        }
    }
};


// Remove Linked List Elements
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
    ListNode* removeElements(ListNode* head, int val) {
        if(head==nullptr){
            return head;
        }
        else{
            while( head!=nullptr && head->val==val){
                ListNode * pre=head;
                head=head->next;
                delete pre;
            }
            
                ListNode * temp=head;
                while(temp!=nullptr && temp->next!=nullptr){
                    if(temp->next->val==val){
                        if(temp->next->next!=nullptr){
                            ListNode* pre=temp->next;
                            temp->next=temp->next->next;
                            delete pre;
                        }
                        else{
                            temp->next=nullptr;
                        }
                    }
                    else{
                    temp=temp->next;
                    }
                }
            }
            return head;
        
    }
};

// Delete Node in a Linked List
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
        ListNode *pre=node;
        while(node->next!=nullptr){
            swap(node->val,node->next->val);
            pre=node;
            node=node->next;
        }
        pre->next=nullptr;
        delete node;
    }
};

// 2. Add Two Numbers
// (this is wrong sol'n according to question beacuse num given in reverse order but i have solve this by assuming it in normal order)

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int num1=l1->val;
        int num2=l2->val;
        

        ListNode * temp1=l1->next;
        ListNode * temp2=l2->next;

        while(temp1!=nullptr){
            num1=num1*10+temp1->val;
            temp1=temp1->next;
        }
         while(temp2!=nullptr){
            num2=num2*10+temp2->val;
            temp2=temp2->next;
        }
        int num3=num1+num2;
        

         ListNode * dummy=new  ListNode();
          ListNode * head=dummy;
          if(num3==0){
            return new ListNode(0);
        }
          while(num3>0){
            int rem=num3%10;
             ListNode * newnode=new  ListNode(rem);
             dummy->next=newnode;
             dummy=newnode;
             num3=num3/10;
          }
          return head->next;

        
    }
};

// correct approch
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
       
        ListNode * dummy=new  ListNode();
        ListNode * curr=dummy;
        int carray=0;
        while(l1!=nullptr || l2!=nullptr){
            int sum=carray;
            // adding number in reverse order 
            if(l1!=nullptr){
                sum+=l1->val;
                l1=l1->next;
            }
            if(l2!=nullptr){
                sum+=l2->val;
                l2=l2->next;
            }
            carray=sum/10;
            // transfer the carray for next number
            sum=sum%10;
            curr->next=new ListNode(sum);
            curr=curr->next;
            
        }
         if (carray > 0) {
            curr->next = new ListNode(carray);
        }

        return dummy->next;

        
    }
};

// 2 4 3   both number in reverse order  
// 5 6 4
// -------
// 7
//   10 1->crray pass to next number carray=sum/10 and  10%10 =0 is sum 
//      7+1 ->1 is carray that come from previous

// 141. Linked List Cycle
// floyed algo for dtection of cycle
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
    bool hasCycle(ListNode *head) {
        bool flag=false;
        if(head==nullptr){
            return flag;
        }
        else{
            ListNode * slow=head,*fast=head;
            while(fast!=nullptr && fast->next!=nullptr){
            
                slow=slow->next;
                fast=fast->next->next;
                    if(fast==slow){
                    return true;
                }
            }
            return false;

        }
    }
};

// 160. Intersection of Two Linked Lists

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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        
        ListNode * ptr=headA;
        ListNode * ptr1=headB;
        
        while(ptr!=nullptr){
             ListNode * curr=ptr1;
            while(curr!=nullptr){
               
                if(curr==ptr){
                    return ptr;
                }
                curr=curr->next;
            }
            ptr=ptr->next;
        }
        return nullptr;
    }
};

// brute force approch 
