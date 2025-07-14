// 155. Min Stack

class MinStack {
     stack<int>*mini;
     stack<int> * obj;
public:
 MinStack() {
         obj=new stack<int>();
         mini=new stack<int>();
    }
    
    void push(int val) {
      obj->push(val);
      if( mini->empty() || val<=mini->top()){
        mini->push(val);
      }
    }
    
    void pop() {
        if(obj->top()==mini->top()){
        mini->pop();
        }
        obj->pop();
    }
    
    int top() {
        return obj->top();
    }
    
    int getMin() {
        return mini->top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 **/

// 496. Next Greater Element I

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int>vec;
        for(int i=0;i<nums1.size();i++){
            for(int j=0;j<nums2.size();j++){
                if(nums1[i]==nums2[j]){
                    int maxx=nums2[j];

                    for(int k=j+1;k<nums2.size();k++){
                        if(nums2[k]>maxx){
                            maxx=nums2[k];
                            break;
                            
                        }
                    }
                    if(maxx==nums2[j]){
                        vec.push_back(-1);
                    }
                    else{
                        vec.push_back(maxx);
                    }
                    break;
                }
            }
        }
        return vec;
    }
};

// optimized
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
     unordered_map<int, int> nmap; 
      // it store next greater element
     stack<int>ss;
      // it store greater element
     vector<int>vec;
     for(int i=nums2.size()-1;i>=0;i--){
        while(!ss.empty() && ss.top()<=nums2[i]){
            ss.pop();
        }
        nmap[nums2[i]]=(ss.empty())?-1:ss.top();

        ss.push(nums2[i]);
     }
     for(auto nu:nums1){
        vec.push_back(nmap[nu]);
     }
     return vec;
    }
};

// 503. Next Greater Element II
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& num) {
       stack<int> ss;
       vector<int>vec;
         int maxx;
       for(int i=num.size()-1;i>=0;i--){
              maxx=-1;
            for(int j=0;j<i;j++){
               if(num[i]<num[j]) {
                maxx=num[j];
                break;
               }
                
                }
           
            stack<int> sss = ss; 
            while(!sss.empty()){
                if(sss.top()>num[i]){
                 maxx=sss.top();
                  break;
                }
                  sss.pop();
            }
         
           vec.push_back(maxx);
             ss.push(num[i]);


       }
       reverse(vec.begin(),vec.end());
       return vec;

    }
};

// 739. Daily Temperatures
// brute force
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temp) {
        vector<int>vec;
        stack<int>s;
        for(int i=temp.size()-1;i>=0;i--){
           int day=0;
           if(s.empty()){
            vec.push_back(day);
           }
           else{
            stack<int>ss=s;
            bool flag=false;
            while(!ss.empty()){
                if(temp[i]<ss.top()){
                    day++;
                    vec.push_back(day);
                    flag=true;
                    break;
                }
                day++;
                ss.pop();
            }
            if(!flag){
                vec.push_back(0);
            }

           }
           s.push(temp[i]);
        }
        reverse(vec.begin(),vec.end());
        return vec;
    }
};

