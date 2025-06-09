// basic logic of push_back(),push_front(),print
#include<iostream>
using namespace std;
// it's blue print of node every node has two property
class node{
    public:
    int data;
    node * next;
    node(int val){
        data=val;
        next=nullptr;
    }
};

// linked list is collection of node  ->it has head pointer that always point to the first node
class list{
    node * head;
    node * tail;
    public:
    list(){
        head=NULL;
        tail=NULL;
    }
    void push_front(int val){
      // node is creted
        node *newnode=new node(val);
      if(head==NULL){
          // if head is not pointing any where means linked list is empty so head will be point toward first element
            head=newnode;
        }
        else{
          // if linked list already have node then connect newnode to linked list in front and move the head to front node
        newnode->next=head;
        head=newnode;
        }
    }
    void push_back(int val){
         node * newnode=new node(val);
        if(head==nullptr){
          // if head is null it's mean list list is empty so that node is fist or last so head will be point that node 
          
            head=newnode;
        }
        else{

          // else node travels to last node then connect new node at the last
        node *ptr=head;
        while(ptr->next!=NULL){
            ptr=ptr->next;
        }
        head->next=newnode;

    }

    }
    void print(){
        node * temp=head;
        while(temp!=NULL){
            cout<<temp->data<<" ";
            temp=temp->next;

        }
    }
};
int main(){

    list ll;
    // ll.push_back(15);
    // ll.push_back(20);
    // ll.print();
    ll.push_front(15);
    ll.push_front(20);
    ll.print();
}


/ insert element at the particular postion
// #include<iostream>
// using namespace std;
// class node{
//     public:
//     int data;
//     node * next;
//     node(int val){
//         data=val;
//         next=NULL;
//     }
// };
// class list{
//     node * head;
//     public:
//     list(){
//         head=NULL;
//     }
//     void push_front(int val){
//         node * newnode=new node(val);
//         if(head==NULL){
//             head=newnode;
//         }
//         else{
//             newnode->next=head;
//             head=newnode;
//         }
//     }
//     void insert(int val,int pos){
//         if(head==NULL){
//             return;
//         }
//         else{
//             node * newnode=new node(val);
//             node * temp=head;
//            for(int i=1;i<pos-1;i++){
//             temp=temp->next;
//            }
//            newnode->next=temp->next;
//            temp->next=newnode;
//         }
//     }
//     void print(){
//         if(head==nullptr){
//             return;
//         }
//         node * temp=head;
//         while(temp!=nullptr){
//             cout<<temp->data<<" ";
//             temp=temp->next;
//         }
//     }
// };
// int main(){
//     list ll;
//     ll.push_front(5);
//     ll.push_front(10);
//     ll.push_front(15);
//     ll.push_front(20);
//     ll.push_front(25);
//     ll.insert(100,2);
//     ll.print();
// }

// pop_back(),pop_front()

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
    void pop_back(){
        if(head==NULL){
            return;
        }
        else{
            node * temp=head;
          // temp->next access the object property ,temp->next->next propety jaha point kar raha ush object ki propety ko access kar raha hai
            while(temp->next->next!=NULL){
                temp=temp->next;
            }
            node * ptr=temp->next;
            temp->next=NULL;
            delete ptr;
        }
    }
    void pop_front(){
        if(head==NULL){
            return;
        }
        else{
            node * ptr=head;
            head=head->next;
            ptr->next=NULL;
            delete ptr;
        }
    }
    void print(){
        if(head==NULL){
            return ;
        }
        else{
            node * temp=head;
            while(temp!=NULL){
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
    ll.push_back(30);
    // ll.print();
    ll.pop_front();
    // ll.print();
    ll.pop_back();
    ll.print();
}



// iterative search
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
node * head=NULL;
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
void print(){
    if(head==nullptr){
        return ;
    }
    else{
        node * temp=head;
        while(temp!=head){
            cout<<temp->data<<" ";
            temp=temp->next;
        }

    }

}

int  find(int key){
    if(head==nullptr){
        return -1;
    }
    else{
        int pos=0;
        node * temp=head;
        while(temp!=nullptr){
            if(temp->data==key){
                return pos;
            }
            else{
                pos++;
                temp=temp->next;
            }
        }
    }
}


};
int main(){
   list ll;
   ll.push_front(10);
   ll.push_front(20);
   ll.push_front(30);
   cout<<ll.find(20); 
}

// reverse the linklist
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
    void reverse(){
        if(head==nullptr){
            return;
        }
        else{
            node * curr=head;
            node * prev=nullptr;
            while(curr!=nullptr){
                node * next=curr->next;
                // next store next address
                curr->next=prev;
                prev=curr;
                curr=next;
                // curr ponit to next address
            }
            head=prev;
            // prev is on last node now
        }
    }
    void print(){
        if(head==nullptr){
            return;
        }
        else{
            node * ptr=head;
            while(ptr!=nullptr){
                cout<<ptr->data<<" ";
                ptr=ptr->next;
            }
        }
    }
};
int main(){
    list ll;
    ll.push_front(5);
    ll.push_front(10);
    ll.push_front(15);
    ll.print();
    ll.reverse();
    cout<<endl;
    ll.print();
}



