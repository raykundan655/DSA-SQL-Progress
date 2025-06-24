/ creating the stack by using two queue

#include<iostream>
#include<queue>
using namespace std;

class stack{
    queue<int>q1;
    queue<int>q2;
    public:
    void push(int val){
        while(!q1.empty()){
            q2.push(q1.front());
            q1.pop();
        }
        q1.push(val);
        while(!q2.empty()){
            q1.push(q2.front());
            q2.pop();
        }
    }
    void pop(){
        q1.pop();
    }
    int top(){
        return q1.front();
    }
    bool empty(){
        return q1.empty();
    }
};

int main(){
stack s1;
while(true){
    int val;
    cin>>val;
    if(val==-1){
        break;
    }
    s1.push(val);
}
while(!s1.empty()){
    cout<<s1.top();
    s1.pop();
}


}

// / find first non repeating char
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
void nonrepreating(string str){
queue<char>q1;
char arr[26]={0};
for(int i=0;i<str.size();i++){
    arr[str[i]-'a']++;
    q1.push(str[i]);
}
while(!q1.empty() && arr[q1.front()-'a']>1){
    q1.pop();
    
}
if(q1.empty()){
    cout<<"there is all repeating char";
}
else{
    cout<<q1.front()<<"first non repeating char";
}

}
int main(){
    string input;
    getline(cin,input);
    nonrepreating(input);
}


// / queue half
// make two of queue and bring the element like firstQueue front <-secondQueue second

#include<iostream>
using namespace std;
#include<queue>

void equalhalf(queue<int>&q){
    int size=q.size();
    queue<int>half;
    for(int i=0;i<size/2;i++){
        half.push(q.front());
        q.pop();
    }
    while(!half.empty()){
        q.push(half.front());
        half.pop();
        q.push(q.front());
        q.pop();
    }

}
int main(){
    queue<int>org;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        org.push(val);
    }
    equalhalf(org);
    while(!org.empty())
    {
        cout<<org.front();
        org.pop();
    }
}

// reverse the queue

#include<iostream>
#include<queue>
#include<stack>
using namespace std;
void reverse(queue<int>&org){
    stack<int>st;
    while(!org.empty()){
        st.push(org.front());
        org.pop();
    }
    while(!st.empty()){
        org.push(st.top());
        st.pop();
    }

}
int main(){
    queue<int>org;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        org.push(val);
    }
    reverse(org);
    while(!org.empty()){
        cout<<org.front();
        org.pop();
    }
}



// / Double ended queue

// A Double-Ended Queue (Deque) is a linear data structure 
// that allows insertion and deletion of elements from both front and rear ends.

// Implementation Options:
// Array (static size, fast access but limited space)
// Linked List (dynamic size, flexible, no limit)

// function            use 
// push_back(x)	Inserts x at the end
// push_front(x)	Inserts x at the front
// pop_back()	    Removes element from the end
// pop_front()	    Removes element from the front
// front()      	Returns the first element
// back()	        Returns the last element
// size()	        Returns the number of elements
// empty()    	    Checks if the deque is empty
// clear()	        Removes all elements
// insert(pos, val)	Inserts val at the given position
// erase(pos)	    Erases the element at the given position



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
class deque{
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
    void pop_front(){
        if(head==nullptr){
            return;
        }
        else{
            node * temp=head;
            head=head->next;
            temp->next=nullptr;
            delete temp;
        }
    }
    void pop_back(){
        if(head==nullptr){
            return;
        }
     if(head->next == nullptr) { // Only one node
        delete head;
        head = nullptr;
           }
        else{
            node * temp=head;
            while(temp->next->next!=nullptr){
                temp=temp->next;
            }
            node * ptr=temp->next;
            temp->next=nullptr;
            delete ptr;
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
    int back(){
        if(head==nullptr){
            return -1;
        }
        else{
            node * temp=head;
            while(temp->next!=nullptr){
                temp=temp->next;
            }
            return temp->data;
        }
    }
    bool empty(){
        return head==nullptr;
    }
    int size(){
        int n=0;
        if(head==nullptr){
            return -1;
        }
        node * temp=head;
        while(temp!=nullptr){
            temp=temp->next;
            n++;
        }
        return n;
    }

};
int main(){
    deque d1;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;

        }
        d1.push_back(val);

    }
    while(!d1.empty()){
        cout<<d1.back();
        d1.pop_back();
    }
}


// STL container
// It is defined in the header:
// #include <deque>


// Functions of std::deque
// push_back(x)	Inserts x at the end
// push_front(x)	Inserts x at the front
// pop_back()	    Removes element from the end
// pop_front()	    Removes element from the front
// front()      	Returns the first element
// back()	        Returns the last element
// size()	        Returns the number of elements
// empty()    	    Checks if the deque is empty
// clear()	        Removes all elements
// insert(pos, val)	Inserts val at the given position
// erase(pos)	    Erases the element at the given position







