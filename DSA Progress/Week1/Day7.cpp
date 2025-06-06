// 1832. Check if the Sentence Is Pangram
// eng alphabet should be appear in sentence atleast once 
class Solution {
public:
    bool checkIfPangram(string sentence) {
        int arr[26]={0};
      // this array will be track the appearance in the sentance
        for(int i=0;i<sentence.length();i++){
            char ch=sentence[i];
            if(arr[ch-'a']!=1){
                arr[ch-'a']=1;
            }
        }
        bool val=true;
        for(int i=0;i<26;i++){
            if(arr[i]==0){
                val=false;
                break;
            }
        }
        return val;
    }
};


28 Find the Index of the First Occurrence in a String
// new logic i learn today
class Solution {
public:
    int strStr(string haystack, string needle) {

      for(int i=0;i<haystack.length();i++){
        if(haystack.substr(i,needle.length())==needle){
          // this fatching the substring from haystack and comparing with 2nd string again and again
              return i;
        }
      }
return -1;
    }
}
// we can do this by find method of str very easly but this one is very nice

// 128. Longest Consecutive Sequence

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
         if(nums.empty())return 0;
       
        sort(nums.begin(),nums.end());
      // sort the elemnet
      
        int count=1;
        int maxc=1;
        for(int i=1;i<nums.size();i++){
            if(nums[i]-1==nums[i-1]){
              // checking previous one is consecutive not
                count++;
            }
            else if(nums[i]==nums[i-1]){
                continue;
            }
           else{
            count=1;
           }
           maxc=max(maxc,count);
          // take largest consecutive
        }
        return maxc;
    }
};

// 125. Valid Palindrome
class Solution {
public:
    bool isPalindrome(string s) {
       string rev="";
       for(int i=0;i<s.size();i++){
        if(isalnum(s[i])){
        char ch=tolower(s[i]);
        rev+=ch;
       }
       }
        string cle=rev;
      // this is used to store clean data
       reverse(rev.begin(),rev.end());
      
       if(rev==cle){
        return true;
       }
       else{
        return false;
       }
    }
};



// 11. Container With Most Water
// array give the height of verticle line in x axis you have to find the max area cover by two vwrticlw line
// area=height*length
class Solution {
public:
    int maxArea(vector<int>& hh) {
        int st=0;
       
        int end=hh.size()-1;
        int maxc=-1;
    
        while(st<=end){
            int length=end-st;
          // doing length maxima
            int height=min(hh[st],hh[end]);
           int area=length*height;
            maxc=max(maxc,area);
            if(hh[st] < hh[end]){
                     st++;
                 } else {
                    end--;
                  }
          // doing height max
        }
        return maxc;
        
 }
};
