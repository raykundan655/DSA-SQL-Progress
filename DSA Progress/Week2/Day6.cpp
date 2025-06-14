// 234. Palindrome Linked List
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
        int num=0;
        if(head==nullptr){
            return false;
        }
        else{
              vector<int>vec;
            ListNode * temp=head;
            while(temp!=nullptr){
              vec.push_back(temp->val);
              temp=temp->next;
            }
            int st=0;
            int end=vec.size()-1;
            while(st<end){
                if(vec[st]!=vec[end]){
                    return false;
                }
                st++;
                end--;
            }
            return true;

           

        }
    }
};

// (reverse the node in b/w left and right)
// Given the head of a singly linked list and two integers 
// left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.


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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(left==right){
            return head;
        }

        vector<ListNode*>vec;
        ListNode * temp=head;
        int ind=1;
        while(temp!=nullptr){
            if(ind>=left && ind<=right){
                vec.push_back(temp);
            }
           temp=temp->next;
           ind++;
        }

        int st=0;
        int end=vec.size()-1;
        while(st<end){
            swap(vec[st]->val,vec[end]->val);
            st++;
            end--;
        }

        return head;

      
    }
};

// 142. Linked List Cycle II(floyd algo)
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
    ListNode *detectCycle(ListNode *head) {
        if(head==nullptr){
            return nullptr;
        }
        else{
            bool falg=false;
            ListNode * slow=head,*fast=head;
            while(fast!=nullptr && fast->next!=nullptr){
                slow=slow->next;
                fast=fast->next->next;
                if(slow==fast){
                    falg=true;
                    break;
                }
            }
            if(!falg){
                return nullptr;
            }
            else{
                slow=head;
                if(slow==fast){
                    return slow;
                }
                else{
                    while(fast!=slow){
                        slow=slow->next;
                        fast=fast->next;
                    }
                    return slow;
                }
            }

        }
    }
};

// 83. Remove Duplicates from Sorted List
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
        if(head==nullptr){
            return nullptr;
        }
        else{
            ListNode * temp=head;
            while(temp->next!=nullptr){
               if(temp->val==temp->next->val){
                
                    temp->next=temp->next->next;
                }
                else{
                    temp=temp->next;
                }
               
            }
            return head;
        }
    }
};

// 61. Rotate List
// Given the head of a linked list, rotate the list to the right by k places
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
        if(head==nullptr || head->next==nullptr) return head;

        int len=0;
        ListNode * temp=head;
        while(temp!=nullptr){
            len++;
            temp=temp->next;
        }
        k=k%len;
        if(k==0) return head;
        
            while(k>0){
                ListNode * temp=head;
                while(temp->next!=nullptr){
                    temp=temp->next;
                }
                int v=temp->val;


                // shifting element toward last
                ListNode * curr=head;
                int currdata=curr->val;
                curr=curr->next;
                while(curr!=nullptr){
                    int temp=curr->val;
                    
                    curr->val=currdata;
                    currdata=temp;
                    curr=curr->next;
                }
                // adding last element into first
                head->val=v;
                k--;
            

            }
            return head;
        
    }
};
