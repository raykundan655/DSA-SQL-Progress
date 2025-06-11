// circular linked list
using namespace std;
#include<iostream>
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
        node *newnode=new node(val);
        if(head==nullptr){
            head=newnode;
            newnode->next=head;

        }
        else{
            node * temp=head;
            while(temp->next!=head){
                temp=temp->next;
            }
            temp->next=newnode;
            newnode->next=head;
        }

    }
    void print(){
        if(head==nullptr){
            return;
        }
        else{
            node * temp=head;
            cout<<temp->data<<" ";
            temp=temp->next;
            while(temp!=head){
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
}

// Double circular list
#include<iostream>
using namespace std;
class node{
    public:
    int data;
    node * next;
    node * pre;
    node(int val){
        data=val;
        pre=next=nullptr;
    }
};
class list{
    node * head=nullptr;
    public:
    void push_back(int val){
        node * newnode=new node(val);
        if(head==nullptr){
            head=newnode;
            head->next=head;
            head->pre=head;
        }
        else{
            node * temp=head;
            while(temp->next!=head){
                temp=temp->next;
            }
            temp->next=newnode;
            newnode->pre=temp;
            newnode->next=head;
            head->pre=newnode;

        }
    }
    void push_front(int val){
        node * newnode=new node(val);
        if(head==nullptr){
            head=newnode;
            newnode->next=head;
            newnode->pre=head;
        }
        else{
            node * last=head->pre;
            newnode->next=head;
            newnode->pre=last;
            last->next=newnode;
            head->pre=newnode;
            head=newnode;
        }
    }
    void pop_front(){
        if(head==nullptr){
            return;
        }
        else{
            // if only one node is there
            if(head==head->next){
                head=nullptr;
            }
            else{
            node * last=head->pre;
            head=head->next;
            last->next=head;
            head->pre=last;
            }
        }
    }
    void pop_back(){
        if(head==nullptr){
            return;

        }
        else{
            if(head==head->next){
                head=nullptr;

            }
            else{
                node * temp=head;
                while(temp->next->next!=head){
                    temp=temp->next;
                }
                temp->next=head;
                head->pre=temp;
            }
        }
    }

    void print(){
        if(head==nullptr){
            return;
        }
        else{
            node * temp=head;
            cout<<temp->data<<" ";
            temp=temp->next;
            while(temp!=head){
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
}

// floyd's algo
// it is use detect the cycle in linklist
// we maintain two pointer 
// slow ,fast
// slow will take one step but fast will take 2 step if cycle exist then they will met at any point

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
            newnode->next=head;
        }
        else{
            node * temp=head;
            while(temp->next!=head){
                temp=temp->next;
            }
            temp->next=newnode;
            newnode->next=head;
        }
    }
    void push_front(int val){
        node * newnode=new node(val);
        if(head==nullptr){
            head=newnode;
            head->next=head;
        }
        else{
           
            node * temp=head;
            while(temp->next!=head){
                temp=temp->next;
            }
            temp->next=newnode;
             newnode->next=head;
            head=newnode;
        }
    }
    bool cycle(){
        if(head==nullptr){
            return false;
        }
        else{
            node * slow=head;
            node * fast=head;
            while(fast!=nullptr && fast->next!=nullptr){
                slow=slow->next;
                fast=fast->next->next;
                if(slow==fast){
                    return true;
                }
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
    cout<<ll.cycle();
}


// detect and remove the cycle 
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
    node *  head=nullptr;
    public:
    void push_front(int val){
        node * newnode=new node(val);
        if(head=newnode){
            head=newnode;
            head->next=head;
        }
        else{
            node * temp=head;
            while(temp->next!=head){
                temp=temp->next;
            }
            newnode->next=head;
            temp->next=newnode;
            head=newnode;
        }

    }
    void detectionAndRemoval(){
        if(head==nullptr){
            return ;
        }
       
            bool flag=false;
            node * fast=head;
            node* slow=head;
            while(fast!=nullptr && fast->next!=nullptr){
                slow=slow->next;
                fast=fast->next->next;
                if(slow==fast){
                    flag=true;
                    break;
                }
            }

            if(!flag){
                cout<<"cycle is not exist";
                return;
            }
            slow=head;
            // if the cycle form at the head;
            if(slow==fast){
                while(fast->next!=slow){
                    fast=fast->next;
                }
                fast->next=nullptr;
            }
              
            else{
                node * pre=fast;
                while(slow!=fast){
                    slow=slow->next;
                    pre=fast;
                    fast=fast->next;
                }
                pre->next=nullptr;
            }
            
        }
bool detection(){
        if(head==nullptr){
            return false;
        }
        else{
            node * slow=head;
            node * fast=head;
            while(fast!=nullptr && fast->next!=nullptr){
                slow=slow->next;
                fast=fast->next->next;
                if(slow==fast){
                    return true;
                }
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
        ll.push_front(val);
    }
    cout<<ll.detection();
    ll.detectionAndRemoval();
    cout<<ll.detection();
}
