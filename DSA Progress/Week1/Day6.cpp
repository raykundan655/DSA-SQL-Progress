// Practice question
// Reverse String (Easy, #344)
class Solution {
public:
    void reverseString(vector<char>& s) {
        reverse(s.begin(),s.end());
        for(int i=0;i<s.size();i++){
            cout<<s[i];
        }
    }
};

// 242. Valid Anagram
class Solution {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(),s.end());
        sort(t.begin(),t.end());
        if(s==t){
            return true;
        }
        else{
            return false;
          
        }

    }
};

// An anagram is a word or phrase formed by rearranging the letters of another word or phrase, using all the original letters exactly once.


// 14. Longest Common Prefix

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty())return "";
    
    string pre="";
       for(int i=0;i<strs[0].size();i++){
        char ch=strs[0][i];
        // comapre one by one through all words
        for(int j=1;j<strs.size();j++){
            if(ch!=strs[j][i]){
                return pre;
            }
        }
        pre+=ch;
       }
       return pre;
      
        }

