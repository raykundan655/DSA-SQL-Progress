// 933. Number of Recent Calls

class RecentCounter {
    int counter=-3000;
    queue<int>q;
public:
    RecentCounter() {
        
    }
    
    int ping(int t) {
        // t represent timestemp(// element represent time )
        q.push(t);
        int limit=counter+t;
        // this condition means i need time of past 3000 sec
        // t=3001 
        // 3002-3000=2
        // include only that start from 2 sec 
      // jo limit se kam ho ush ko include nahi kara ga
        
        
            while(!q.empty() && q.front()<limit){
                q.pop();
            }
        
        return q.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

// 1700. Number of Students Unable to Eat Lunch
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        queue<int>q1;
        stack<int>s;
        for(int i=0;i<students.size();i++){
            q1.push(students[i]);
        }
        for(int j=sandwiches.size()-1;j>=0;j--){
            s.push(sandwiches[j]);
        }
           
           int count=0;
      // agar woh top sandwitch jo hai woh kisi student ko nahi chahiya hoga to->it will increase everytime jab jab nahi chahiya if yeah size equal to ho gaya jitna student hai queue me it's mean kisi ko nahi chahiya
      
        while(!s.empty()&& !q1.empty()){
            if(!q1.empty()&&q1.front()==s.top()){
                
                q1.pop();
                s.pop();
                count=0;
              // jaisa hi mil gaya ki kisi ko chahiya phir yeah zero se start ho jaye ga ->ki  naya top sandwitch  may be kisi aur ko chahiya hoga
            }
            else{
                // if(!q1.empty()){
                count++;
                q1.push(q1.front());
                q1.pop();
                // }
            }

            if(count==q1.size()){
                break;
            }
        }

        return q1.size();
      
        

    }
};

// 950. Reveal Cards In Increasing Order(confusing)
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        sort(deck.begin(),deck.end());
        vector<int>vec;
        deque<int>q;
        for(int i=deck.size()-1;i>=0;i--){
            if(!q.empty()){
                q.push_front(q.back());
                q.pop_back();

            }
            q.push_front(deck[i]);
        }
        while(!q.empty()){
            vec.push_back(q.front());
              q.pop_front();
        }
        return vec;

    }
};

// 622. Design Circular Queue

class MyCircularQueue {
    deque<int>q;
 
    int cap;
public:
    MyCircularQueue(int k) {
        
        cap=k;
    }
    
    bool enQueue(int value) {
        
        if(q.size()<cap){
            q.push_back(value);
         
            return true;
        }
        return false;
       
    }
    
    bool deQueue() {
        if(!q.empty()){
            q.pop_front();
            
            return true;
        }
       return false;

    }
    
    int Front() {
        if(!q.empty()) return q.front();
        return -1;
    }
    
    int Rear() {
       if(!q.empty()) return q.back();
       return -1;
    }
    
    bool isEmpty() {
        return q.empty();
    }
    
    bool isFull() {
      return q.size()==cap;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */

// 641. Design Circular Deque

class MyCircularDeque {
    int cap;
    deque<int>q;
public:
    MyCircularDeque(int k) {
        cap=k;
    }
    
    bool insertFront(int value) {
        if(q.size()<cap){
            q.push_front(value);
            return true;
        }
        return false;
    }
    
    bool insertLast(int value) {
        if(q.size()<cap){
            q.push_back(value);
            return true;
        }
        return false;
    }
    
    bool deleteFront() {
        if(!q.empty()){ q.pop_front();
        return true;
        }
        return false;
    }
    
    bool deleteLast() {
          if(!q.empty()){ q.pop_back();
        return true;
        }
        return false;
    }
    
    int getFront() {
         if(!q.empty()) return q.front();
         return -1;
    }
    
    int getRear() {
         if(!q.empty()) return q.back();
         return -1;
    }
    
    bool isEmpty() {
        return q.empty();
    }
    
    bool isFull() {
        return cap==q.size();
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
