// 1544. Make The String Great
class Solution {
public:
    string makeGood(string s) {
        stack<char>ss;
        for(int i=0;i<s.size();i++){
            if(!ss.empty()){
                char to=ss.top();
                if((abs(to-s[i]))==32) {
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
        string ans="";
        while(!ss.empty()){
            ans+=ss.top();
            ss.pop();

        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};

// 1021. Remove Outermost Parentheses

class Solution {
public:
    string removeOuterParentheses(string s) {
       stack<char>ss;
       string ans="";
       int depth=0; 
        // depth zero reperesent outer one
       for(int i=0;i<s.size();i++){
        if(s[i]=='('){
            if(depth>=1){
                ans+=s[i];
            }
            depth++;
            ss.push(s[i]);
        }
        else if(s[i]==')'){
            ss.pop();
            depth--;
            if(depth>=1){
                ans+=s[i];
            }
        }
       }
       return ans;
    }
};

// 1003. Check If Word Is Valid After Substitutions

class Solution {
public:
    bool isValid(string s) {
        stack<char>ss;
        for(char ch:s){
            ss.push(ch);
            if(ss.size()>=3){
                char third=ss.top(); ss.pop();
                char sec=ss.top(); ss.pop();
                char first=ss.top(); ss.pop();
                if(first=='a' && sec=='b' && third=='c'){
                    continue;
                }
                else{
                    ss.push(first);
                    ss.push(sec);
                    ss.push(third);
                }
            }
        }
        if(ss.size()>0){
            return false;
        }
        else{
            return true;
        }
    }
};

// 1598. Crawler Log Folder

class Solution {
public:
    int minOperations(vector<string>& logs) {
        stack<string>ss;
        for(int i=0;i<logs.size();i++){
            if(logs[i]=="../"){
                if(!ss.empty()){
                ss.pop();
                }
            }
            else if(logs[i]=="./"){
                continue;
            }
            else{
                ss.push(logs[i]);
            }
        }
        return ss.size();
        // return how many ../ operation needed to come in main folder->no of file inside the stack reperesent no of operation needed to come out because for coming from each folder we need  one time this ../ 
    }
};

// 1614. Maximum Nesting Depth of the Parentheses
class Solution {
public:
    int maxDepth(string s) {
        stack<char>ss;
        int maxx=0;
        int depth=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='('){
                 depth++;
                maxx=max(maxx,depth);
            }
            else if(s[i]==')'){
                depth--;
               
                }
            }

             return maxx;
    }
    // Think of ( as going inside a room, and ) as coming out of the room.
    // How many rooms you're inside at the same time.

        
    };


