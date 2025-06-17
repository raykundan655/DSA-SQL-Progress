// 1047. Remove All Adjacent Duplicates In String
class Solution {
public:
    string removeDuplicates(string s) {
        stack<char>ss;
        for(int i=0;i<s.size();i++){
            if(!ss.empty()){
                char ch=ss.top();
                if(ch==s[i]){
                    ss.pop();
                }
                else{
                    ss.push(s[i]);
                }
            }
            else{
                ss.push(s[i]);
            }
        }
        string arr="";
        while(!ss.empty()){
            arr+=ss.top();
            ss.pop();
        }
        reverse(arr.begin(),arr.end());
        return arr;
    }
};

// 844. Backspace String Compare

class Solution {
public:
    bool backspaceCompare(string s, string t) {
        stack<char>ss;
        stack<char>st;
        for(int i=0;i<s.size();i++){
            if(s[i]=='#'){
                if(!ss.empty()){
                    ss.pop();
                }
            }
            else{
                ss.push(s[i]);
            }
        }
    

    for(int i=0;i<t.size();i++){
            if(t[i]=='#'){
                if(!st.empty()){
                    st.pop();
                }
            }
            else{
                st.push(t[i]);
            }
        }

        string arr="";
        string arr1="";
        while(!ss.empty()){
            arr+=ss.top();
            ss.pop();
        }
         while(!st.empty()){
            arr1+=st.top();
            st.pop();
        }
        reverse(arr.begin(), arr.end());
        reverse(arr1.begin(), arr1.end());



        return arr==arr1;

    }


};

// 682. Baseball Game
class Solution {
public:
    int calPoints(vector<string>& op) {
        stack<int>ss;
        for(int i=0;i<op.size();i++){
          
          if(op[i]=="C"){
                if(!ss.empty()){
                    ss.pop();
                }
            }
            else if(op[i]=="D"){
                if(!ss.empty()){
                int t=ss.top();
                    ss.push(t*2);
                }
            }
            else if(op[i]=="+"){
                 if (ss.size() >= 2) {
               int top1=ss.top();
               ss.pop();
             int  top2=ss.top();
               ss.pop();
               ss.push(top2);
               ss.push(top1);
               ss.push(top1+top2);
                 }
            }
            else{
                ss.push(stoi(op[i]));
            }
        }
    int sum=0;
    while(!ss.empty()){
        sum+=ss.top();
        ss.pop();
    }
    return sum;

    }
};



// 150. Evaluate Reverse Polish Notation

class Solution {
public:
    int evalRPN(vector<string>& t) {
        stack<int>s;
        for(int i=0;i<t.size();i++){
            if(t[i]=="+"){
              int  top1=s.top();
                s.pop();
              int  top2=s.top();
                s.pop();
                s.push(top1+top2);
            }
          else  if(t[i]=="*"){
               int top1=s.top();
                s.pop();
               int top2=s.top();
                s.pop();
                s.push(top2*top1);
            }
           else if(t[i]=="/"){
             int   top1=s.top();
                s.pop();
              int  top2=s.top();
                s.pop();
                s.push(top2/top1);
            }
            else if(t[i]=="-"){
             int   top1=s.top();
                s.pop();
              int  top2=s.top();
                s.pop();
                s.push(top2-top1);
            }
            else{
                s.push(stoi(t[i]));
            }

        }
        return s.top();
    }
};


