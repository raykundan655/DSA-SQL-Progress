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

