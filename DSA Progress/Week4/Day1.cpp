// Queue
// queue is first in first out data struture(FIFO)

// A queue is a linear data structure that follows the First In, First Out (FIFO) principle. This means the element that is added first is the one removed first.

// Front->|-|-|-|-|-|-|<-Rear
  // element add from rear and pop from front

// No direct access to elements using index.
// No iterators.
// Only access to front(), back(), push(), and pop()

 // real-world or logical sense, a queue does not support direct traversal or random access.

// Basic operation of queue
// push() ->O(1) TC
// pop()  ->O(1) TC
// front() ->O(1) TC

// Enqueue->push()
// dequeue->pop()

//  Single-ended Queue (Normal Queue)
// Follows FIFO (First In, First Out)
// Only one end is used for insertion (rear)
// Only one end is used for deletion/access (front)
//  Enqueue → at rear
//  Dequeue or access → from front
//  You cannot access rear directly in most custom queues
// ✅ You can only access front


// implemenattion using Linklist


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
class queue{
    node * head=nullptr;
    public:
    void push(int val){
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
    void pop(){
        if(head==nullptr){
            return;
        }
        else{
            node * temp=head;
            head=head->next;
            delete temp;
        }
    }
    int front(){
        if(head==nullptr){
            return -1;
        }
        else{
            return head->data;
        }
    }
    bool empty(){
        return head==nullptr;
    }

};
int main(){
    queue q;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        q.push(val);
    }
    while(!q.empty()){
        cout<<q.front();
        q.pop();
    }
    
}

// Circular Queue Using Linked List

// The last node's next points to the first node, making it circular.
// We keep two pointers:
// front: points to the first node.
// rear: points to the last node.

//  Behavior:
// ➕Enqueue (Insert at rear):
// Create a new node.
// Add it after rear.
// Move rear to the new node.
// Set rear->next = front to maintain the circle.

// ➖ Dequeue (Remove from front):
// Remove front node.
// Move front to front->next.
// Set rear->next = front again to keep it circular.


// The last node (rear) always points to the first node (front).
// So after last node, we loop back to start.




 #include<iostream>
 using namespace std;
 template<class T>
 class node{
    public:
    T data;
    node * next;
    node(T val){
        data=val;
        next=nullptr;
    }
};
template<class T>
class queue{
    node<T> * head=nullptr;
    // I’m creating a pointer that holds the address of a Node object, and that Node is storing int data.
  
    public:
    void push(T val){
        node<T>* newnode=new node<T>(val);
        if(head==nullptr){
            head=newnode;
            head->next=newnode;
        }
        else{
            node<T>*temp=head;
            while(temp->next!=head){
                temp=temp->next;
            }
            temp->next=newnode;
            newnode->next=head;
        }
    }
    void pop(){
        if(head==nullptr){
            return;
        }
       
        if(head->next == head){
        delete head;
        head = nullptr;
        // this conditiion hendal when element is only one
    }
        else{
            node<T>* temp=head;
            while(temp->next!=head){
                temp=temp->next;
            }
            node<T>*pre=head;
            head=head->next;
            temp->next=head;
            delete pre;
        }
    }
    bool empty(){
        return head==nullptr;
    }
    T front(){
        if(head==nullptr){
            return T();
            // T() is used to create a default-initialized value of type T
        }
        else{
            return head->data;
        }
    }
};
int main(){
    queue<int>q;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        q.push(val);
    }
   while(!q.empty()){
        cout<<q.front();
        q.pop();
    }

}

// QUEUE USING STL


// #include<queue>
// standard lib for queue

// ->push() it is used to insert at the end
// ->pop()  it is uded to delete from front
// ->front() it return value of front node
// ->empty() it return boolean ->queue is empty or not

// T.c is O(1) for this operation


// / implemation of queue using by two stack
#include<iostream>
#include<stack>
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
class queue{
    stack<int>s1;
    stack<int>s2;
    public:
    void push(int val){
        while(!s1.empty()){
            s2.push(s1.top());
            s1.pop();
        }
        s1.push(val);
        while(!s2.empty()){
            s1.push(s2.top());
            s2.pop();
        }
    }
    void pop(){
        s1.pop();
    }
    bool empty(){
        return s1.empty();
    }
    int front(){
        return s1.top();
    }
};
int main(){
    queue q;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        q.push(val);
    }
    while(!q.empty()){
        cout<<q.front();
        q.pop();
    }
}








  
