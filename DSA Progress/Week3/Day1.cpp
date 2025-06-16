
// Stack behaviour
// push(),pop(),top() all time complexity is O(1)
// we assume it like bucket
// insertion of element is done by top
// deletion of element is done by top 
// stack can be implemented by linkedlist,vector,array,dynamic array,stl


// A stack is a linear data structure that follows the Last In, First Out (LIFO) principle. 
// This means that the last element added (pushed) to the stack is the first one to be removed (popped).

// Key Operations:
// Push: Add an element to the top of the stack.
// Pop: Remove the top element from the stack.
// Peek/Top: View the top element without removing it.
// isEmpty: Check whether the stack is empty.

// Applications:
// Undo operations in editors
// Function call management (call stack)
// Expression evaluation (like postfix or prefix)
// Syntax parsing
// Backtracking algorithms (like solving mazes or recursion)


// NOTE
// stack as a data structure and 
// ✅ stack as a memory region are different concepts, though they share the same LIFO principle. 

// Stack as Memory (Call Stack)
// A special memory region managed by the system.
// Used by your program to store:
// Function calls
// Local variables
// Function parameters
// Return addresses

// Stack as a Data Structure
// A logical structure used in programming.
// Follows LIFO (Last-In, First-Out) order.
// Implemented using:
// Arrays (fixed size)
// Linked lists (dynamic size)


// stack implemantion by using vector
#include<iostream>
#include<vector>
using namespace std;
class stack{
    vector<int>vec1;
    public:
    void push(int val){
        vec1.push_back(val);
    }
    void pop(){
        vec1.pop_back();
    }
    int top(){
        int last=vec1.size()-1;
        return vec1[last];
    }
    bool isempty(){
        return vec1.size()==0;
    }
};
int main(){
    stack s1;
    s1.push(50);
    s1.push(60);
    s1.push(70);
    // the element enter last ->last element will come first
    while(!s1.isempty()){
        cout<<s1.top()<<endl;
        s1.pop();
    }

}


// // make generic stack
#include<iostream>
#include<vector>
using namespace std;

template<class T>
class stack{
    vector<T>vec;
    public:
    void push(T val){
        vec.push_back(val);
    }
    void pop(){
        vec.pop_back();
    }
    T top(){
        int last=vec.size()-1;
        return vec[last];
    }
    bool isempty(){
        return vec.size()==0;
    }
};
int main(){
    stack<int>s1;
    s1.push(50);
    s1.push(55);
    s1.push(60);
    while(!s1.isempty()){
        cout<<s1.top()<<endl;
        s1.pop();
    }
    stack<char>s2;
    s2.push('M');
    s2.push('A');
    s2.push('H');
    s2.push('I');

    while(!s2.isempty()){
        cout<<s2.top()<<endl;
        s2.pop();
    }

 

}


// stack implematation by using linklist

#include<iostream>
using namespace std;
class node{
    public:
    int val;
    node * next;
    node(int val){
        this->val=val;
        next=nullptr;
    }
};
class stack{
    node * head=nullptr;
    public:
    void push(int val){
        node * newnode=new node(val);
        if(head==nullptr){
            head=newnode;
        }
        else{
            newnode->next=head;
            head=newnode;
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
    int top(){
        if(head==nullptr){
            return -1;
        }
        else{
            return head->val;
        }
    }
    bool isempty(){
        return head==nullptr;
    }
};
int main(){
    stack s1;
    s1.push(20);
    s1.push(30);
    s1.push(40);
    while(!s1.isempty()){
        cout<<s1.top()<<endl;
        s1.pop();
    }

}

// generic stack by using linklist
#include<iostream>
using namespace std;

template<class T>
class node{
    public:
    T val;
    node * next;
    node(int val){
        this->val=val;
        next=nullptr;
    }
};
template<class T>
class stack{
node<T> * head=nullptr;
// Create a pointer to a node that stores a value of type T."

public:
void push(T val){
     node<T> * newnode=new node<T>(val);
    if(head==nullptr){
        head=newnode;
}
    else{
        newnode->next=head;
        head=newnode;
    }

}
void pop(){
    if(head==nullptr){
        return;
    }
    else{
        node<T> * temp=head;
        head=head->next;
        delete temp;
    }
}
T top(){
    if(head==nullptr){
        return -1;
    }
    else{
        return head->val;
    }
}
bool isempty(){
    return head==nullptr;
}
};
int main(){
    stack<int>s1;
    s1.push(50);
    s1.push(60);
    s1.push(70);

    while(!s1.isempty()){
        cout<<s1.top()<<endl;
        s1.pop();
    }


}

// STL container
// #include<stack>
// it's header file for stack
#include<iostream>
#include<stack>
using namespace std;
int main(){
    stack<int>obj;
    obj.push(50);
    // push operation->insertion
    obj.pop();
    // pop operation->deletion
     cout<<obj.top();
    // it give the top element 
    cout<<obj.size();
    // it give total element of stack


}
// swap(stack &s)	Swaps the contents of two stacks.


// enter the new element at the bottom of stack

#include<iostream>
using namespace std;

class node{
    public:
    int data;
    node * next;
    public:
    node(int val){
        data=val;
        next=nullptr;
    }
};
class stack{
    node * head=nullptr;
    public:
    void push(int val){
        node * newnode=new node(val);
        if(head==nullptr){
            head=newnode;
        }
        else{
            newnode->next=head;
            head=newnode;
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
    int top(){
        if(head==nullptr){
            return -1;
        }
        else{
            return head->data;
        }
    }
    bool isempty(){
        return head==nullptr;
    }
};
void pushAtBottom(stack &s,int val){
    if(s.isempty()){
        s.push(val);
        return;
    }
    int temp=s.top();
    s.pop();
    pushAtBottom(s,val);
    s.push(temp);

}
// recursion follow last in first out ->jo last function call hua hai woh pehela execute hoga ->then follow bye
int main(){
    stack s1;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        pushAtBottom(s1,val);
    }
    while(!s1.isempty()){
        cout<<s1.top()<<endl;
        s1.pop();
    }
}

//recerse the string
#include<iostream>
#include<stack>
#include<cstring>
using namespace std;
void reverse(stack<char>&s){
    stack<char>s2;
    while(!s.empty()){
        s2.push(s.top());
        s.pop();
    }
     while(!s2.empty()){
        s.push(s2.top());
        s2.pop();
    }

}
int main(){
    stack<char>s;
    string str;
    getline(cin,str);
    for(int i=0;i<str.size();i++){
        s.push(str[i]);
    }
    reverse(s);

      while(!s.empty()){
        cout<<s.top();
        s.pop();
    }

}


