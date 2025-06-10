// wrt to sort linked list 

#include<iostream>
using namespace std;
class node{
    public:
    int data;
    node * next;
    node(int val){
        data=val;
        next=NULL;
    }
};
class list{
    node * head=NULL;
    public:
    void push_back(int val){
        node * newnode=new node(val);
        if(head==NULL){
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
    void sort(){
        if(head==nullptr){
            return;
        }
        else{
            node * temp=head;
            while(temp!=nullptr){
                node * ptr=temp->next;
                while(ptr!=nullptr){
                    if(ptr->data>temp->data){
                        swap(temp->data,ptr->data);
                    }
                    ptr=ptr->next;
                }
                temp=temp->next;
            }
        }
    }
    void print(){
        if(head==nullptr){
            return ;
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
    ll.sort();
    ll.print();
}


// wrt program to murge to linked list 

// wrt program to murge to linked list 

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
void push_front(int val){
    node * newnode=new node(val);
    if(head==nullptr){
        head=newnode;
    }
    else{
        newnode->next=head;
        head=newnode;
    }
}
void pop_front(){
    if(head==nullptr){
        return;

    }
    else{
        node * ptr=head;
        head=head->next;
        delete ptr;
    }
}
void pop_back(){
    if(head==nullptr){
        return;
    }
    else{
        node * temp=head;
        while(temp->next->next!=nullptr){
            temp=temp->next;
        }
        temp->next=nullptr;
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
void merge(list &l){
    if(head==nullptr){
        return;
    }
    else{
        node * temp=head;
        while(temp->next!=nullptr){
            temp=temp->next;
        }
        
        // node * ptr=l.head;
        // while(ptr!=nullptr){
        //   node * newnode=new node(ptr->data);
        //   temp->next=newnode;
        //   temp=temp->next;
        //   ptr=ptr->next;
        // }

        // 2nd way
        temp->next=l.head;

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
        ll.push_front(val);
    }
    list l2;
         while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        l2.push_front(val);
    }
    ll.print();
    cout<<endl;
    l2.print();
    cout<<endl;
    ll.merge(l2);
    cout<<endl;
    ll.print();


}

// DOUBLE LINKKIST

// / create double ll
#include<iostream>
using namespace std;
class node{
    public:
    int data;
    node *next;
    node *pre;
    node(int val){
        data=val;
        next=nullptr;
        pre=nullptr;
    }
};
class list{
    node * head=nullptr;
    node * tail=nullptr;
    public:
    void push_back(int val){
    node * newnode=new node(val);{
        if(head==nullptr && tail==nullptr){
            head=tail=newnode;
        }
        else{
            node * temp=head;
            while(temp->next!=nullptr){
                temp=temp->next;
            }
            newnode->pre=temp;
            temp->next=newnode;
            tail=newnode;
        }
    }
}
    void print(){
        if(head==nullptr && tail==nullptr){
            return;

        }
        else{
            node * temp=tail;
            while(temp!=nullptr){
                cout<<temp->data<<" ";
                temp=temp->pre;
            }
        }
    }
    
};
int main(){
list ll;
ll.push_back(15);
ll.push_back(13);
ll.push_back(12);
ll.print();

}

/ // wrt a program for insert element in double ll

#include<iostream>
using namespace std;
class node{
    public:
    int data;
    node * next;
    node * pre;
    node(int val){
        data=val;
        next=nullptr;
        pre=nullptr;
    }
};
class list{
    node * head=nullptr;
    node * tail=nullptr;
    public:
    void push_front(int val){
        node * newnode=new node(val);
        if(head==nullptr && tail==nullptr){
            head=tail=newnode;
        }
        else{
            head->pre=newnode;
            newnode->next=head;
            head=newnode;
        }
    
    }
    void insert(int val,int pos){
        if(head==nullptr){
            return ;
        }
        else{
            node * newnode=new node(val);
             if (pos == 0) {
                newnode->next = head;
                head->pre = newnode;
                head = newnode;
                    return;
                 }
            node * temp=head;
            // edge case
            for(int i=1;i<pos-1 && temp->next!=nullptr;i++){
                temp=temp->next;
            }
            newnode->pre=temp;
            newnode->next=temp->next;
            // edge case
            if(temp->next!=nullptr){
                temp->next->pre=newnode;
            }
            temp->next=newnode;
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
    ll.push_front(10);
    ll.push_front(15);
    ll.push_front(20);
    ll.push_front(30);
    ll.print();
    cout<<endl;
    ll.insert(101,2);
    ll.print();
}


/ // wrp to delete element from double ll

#include<iostream>
using namespace std;
class node{
    public:
    int data;
    node* next;
    node * pre;
    node(int val){
        data=val;
        next=nullptr;
        pre=nullptr;
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
            newnode->pre=temp;
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
    void deleteelememnt(int pos){
        if(head==nullptr){
            return;
        }
        else{
             node * temp=head;
            if(pos==1){

                head=head->next;
                head->pre=nullptr;

            }
            else{
                for(int i=1;i<pos-1 && temp->next!=nullptr;i++){
                    temp=temp->next;
                }
                temp->next=temp->next->next;
                temp->next->next->pre=temp;
            }
        }
    }
};
int main(){
    list ll;
    ll.push_back(10);
     ll.push_back(20);
      ll.push_back(30);
       ll.push_back(10);
       ll.print();
       cout<<endl;
       ll.deleteelememnt(2);
       ll.print();
}


// // wrp to delete largest element from double ll;

#include<iostream>
#include<climits>
using namespace std;
class node{
    public:
    int data;
    node * next;
    node * pre;
    node(int val){
        data=val;
        next=pre=nullptr;
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
        newnode->pre=temp;
    }

}
int findLargest(){
    if(head==nullptr){
        return -1;
    }
    else{
        int val=INT_MIN;
        node * temp=head;
        while(temp!=nullptr){
            if(temp->data>val){
                val=temp->data;
            }
            temp=temp->next;
        }
        return val;
    }
}
void deleteLargest(){
if(head==nullptr){
    return;
}
else{
    int large=findLargest();
    node * temp=head;
    if(head->data==large){
        head=head->next;
      // edge case
        if(head != nullptr) head->pre = nullptr;
    }
    else{
        while(temp->next->data!=large){
            temp=temp->next;
        }
        temp->next=temp->next->next;
      // edge case
        if(temp->next->next!=nullptr){
        temp->next->next->pre=temp;
        }
    }
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
    ll.push_back(10);
    ll.push_back(20);
    ll.push_back(25);
    ll.push_back(30);
    ll.push_back(25);
    ll.deleteLargest();
    ll.print();
}




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

        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode * pre=head;
        ListNode * curr=head->next;
        while(curr!=nullptr){
             if(pre->val==curr->val){
                ListNode * temp=curr;
                
                pre->next=curr->next;
                 curr=curr->next;
                delete temp;
               

             }
             else{
                pre=pre->next;
                curr=curr->next;
             }
           
        }
        return head;

    }
};
