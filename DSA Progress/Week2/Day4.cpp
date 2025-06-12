// / STL Conatainer
// #include<list>
// it's header file for linklist

// push_back() it is function for push the element at the end
// push_front() it is function for push the element at the front
// pop_back() it is use to remove the element from back (it remove the last element)
// pop_front() is pop the element from the front

// size()  it give total no of element

// Function	                                  Description
// insert(position, value)	           Insert element at given iterator position
// erase(position)	                     Remove element at given iterator position
// reverse()	                              Reverse the list
// sort()	                            Sort the list in ascending order
// empty()	                             Returns true if the list is empty
// begin()	                                Iterator to first element
// end()	                             Iterator to past-the-end elemen
// front()                             Value of first element (modifiable)
// back()		                         Value of last element (modifiable)


#include<list>
#include<iostream>
using namespace std;
void print(list<int>::iterator it,list<int>::iterator end){
while (it!=end)
{
    cout<<*it;
    it++;

    /* code */
}


}
int main(){
    list<int>ll;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        ll.push_back(val);
    }
            // cout<<*ll.end();
// std::list (and other STL containers),
//  ll.end() points to a position just after the last node — not to the last node itself.
   
// print(ll.begin(),ll.end());
    // i am passing iterator 

cout<<ll.front();
cout<<ll.back();
cout<<ll.size();

}


/ split linklist from middle 

#include<iostream>
using namespace std;
class node{
    public:
    int data;
    node * next;
    node(int val){
        data=val;
        next=nullptr;
    }
};
class list{
    node * head=nullptr;
    public:
    void push_back(int val){
        node * newnode=new node(val);
        if(head==nullptr){
            head=newnode;
        }
        else{
            node * temp=head;
            while(temp->next!=nullptr){
                temp=temp->next;
            }
            temp->next=newnode;
        }
    }
    void split(){
        if(head==nullptr){
            return;
        }
        else{
            node * fast=head;
            node * slow=head;
            node * pre=slow;
            while(fast!=nullptr && fast->next!=nullptr){
                pre=slow;
                slow=slow->next;
                fast=fast->next->next;
            }
            pre->next=nullptr;
            head=slow;
        }
    }
    void print(){
        if(head==nullptr){
            return;
        }
        else{
            node * temp=head;
            while(temp!=nullptr){
                cout<<temp->data<<" ";
                temp=temp->next;
            }
        }
    }
};
int main(){
    list ll;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        ll.push_back(val);
    }
    ll.print();
    cout<<endl;
    ll.split();
    ll.print();
}



21. Merge Two Sorted Lists

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

       
        ListNode *dummy=new ListNode();
      // creted dummy object; from there next poniter actual data will be store 
        ListNode * head=dummy;
      // we store the dummy node address for head pointer -> this object next pointer store the head pointer addresss
        if(list1==nullptr && list2==nullptr){
            return head->next;
        }
        ListNode * i=list1;
        ListNode * j=list2;
        while(i!=nullptr && j!=nullptr){
            if(i->val<j->val){
                ListNode * temp=new ListNode(i->val);
              // if i list val has small value then create object and move the pointer  of i
              dummy->next=temp;
              // dummy start pointing this node
                i=i->next;
            }
            else{
                 ListNode * temp=new ListNode(j->val);
                dummy->next=temp;
                j=j->next;
            }
            dummy=dummy->next;
          // after inserting node move the dummy node ->now dummy node pointing the last node ->by every insertion dummy will point last node
        }

      // checking any of list is left after complition of one list
        while(i!=nullptr){
            ListNode * temp=new ListNode(i->val);
                dummy->next=temp;
                i=i->next;
                dummy=dummy->next;
        }
        while(j!=nullptr){
            ListNode * temp=new ListNode(j->val);
                dummy->next=temp;
                j=j->next;
                dummy=dummy->next;
        }
        return head->next;

    }
};

// done for today(not happy)
