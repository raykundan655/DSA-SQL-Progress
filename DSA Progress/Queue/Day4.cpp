// 232. Implement Queue using Stacks
class MyQueue {
    stack<int>s;
    stack<int>s1;
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        while(!s.empty()){
            s1.push(s.top());
            s.pop();
        }
        s.push(x);
        while(!s1.empty()){
            s.push(s1.top());
            s1.pop();
        }
    }
    
    int pop() {
        if(!s.empty()){
            int tt=s.top();
            s.pop();
            return tt;
        }
        return -1;
    }
    
    int peek() {
        if(!s.empty()){
            return s.top();
        }
        return -1;
    }
    
    bool empty() {
        return s.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */


// 225. Implement Stack using Queues

class MyStack {
    queue<int>q1;
    queue<int>q2;
public:
    MyStack() {
        
    }
    
    void push(int x) {
        while(!q1.empty()){
            q2.push(q1.front());
            q1.pop();
        }
        q1.push(x);
        while(!q2.empty()){
            q1.push(q2.front());
            q2.pop();
        }
    }
    
    int pop() {
        if(!q1.empty()){
            int tt=q1.front();
            q1.pop();
            return tt;
        }
        return -1;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

