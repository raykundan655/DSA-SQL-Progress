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


// 414. Third Maximum Number 

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        sort(nums.begin(),nums.end());
         int j=0;
         for(int i=1;i<nums.size();i++){
            if(nums[i]!=nums[j]){
                j++;
                nums[j]=nums[i];
            }
         }
        //  finding unique element only work when array is sorted
         vector<int>vec;
         for(int i=0;i<j+1;i++){
            vec.push_back(nums[i]);
         }
         sort(vec.begin(),vec.end(),greater<int>());
        // greater<int>() this function work for sort in decending order
         if(vec.size()>=3){
            return vec[2];
         }
        else{
            return vec[0];
        }
        
    }
};


// 2nd way is best way to find unique element

class Solution {
public:
    int thirdMax(vector<int>& nums) {
       set<int>s(nums.begin(),nums.end());
       // set only store unique element
        // it automatically arrange in asending order
         vector<int>vec(s.begin(),s.end());
         
         sort(vec.begin(),vec.end(),greater<int>());
         if(vec.size()>=3){
            return vec[2];
         }
        else{
            return vec[0];
        }
        
    }
};


// 1122. Relative Sort Array
// brute force
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        vector<int>vec;
        for(int i=0;i<arr2.size();i++){
            for(int j=0;j<arr1.size();j++){
                if(arr2[i]==arr1[j]){
                    vec.push_back(arr1[j]);
                }
            }
        }
        vector<int>vec1;
         for(int i=0;i<arr1.size();i++){
            int flag=0;
            for(int j=0;j<vec.size();j++){
                if(arr1[i]==vec[j]){
                   flag=1;
                }
            }
            if(flag==0){
                vec1.push_back(arr1[i]);
            }
        }
        sort(vec1.begin(),vec1.end());
        for(int i=0;i<vec1.size();i++){
            vec.push_back(vec1[i]);
        }
        return vec;

    }
};


// optimised

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
 map<int,int>freq;
        for(int i=0;i<arr1.size();i++){
            freq[arr1[i]]++;
            // freq[5] 
            // 5 is key it's value is 0 but freq[5]++->freq[5]=freq[5]+1
            // it count the frequency of each element
        }
        vector<int>result;

        for(auto num:arr2){
            while(freq[num]>0){
                result.push_back(num);
                freq[num]--;
            }
        }
        //  C++, a map automatically stores its keys in sorted (ascending) order by default.
        for (auto [num, count] : freq) {
            while (count-- > 0) {
                result.push_back(num);
            }
        }
        return result;



    }
};

// 1299. Replace Elements with Greatest Element on Right Side
class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        if(arr.size()==1){
            vector<int>vec;
            vec.push_back(-1);
            return vec;
        }
        for(int i=0;i<arr.size()-1;i++){
            int maxN=arr[i+1];
            for(int j=i+2;j<arr.size();j++){
                maxN=max(maxN,arr[j]);
            }
            arr[i]=maxN;
        }
        arr[arr.size()-1]=-1;
        return arr;
    }
};

// 905. Sort Array By Parity

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int j=0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]%2==0){
               swap(nums[j],nums[i]);
                j++;
            }
        }
        return nums;
    }
};



// Find Pivot Index (Easy, #724)


class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        
        int st=0;
        int end=nums.size()-1;

        while(st<=end){
            int suml=0;
            int sumr=0;
            
                for(int i=st+1;i<=end;i++){
                    sumr+=nums[i];
                }
               if(st>0){
                for(int i=st-1;i>=0;i--){
                    suml+=nums[i];
                }
               }
               else{
                suml=0;
               }
               if(sumr==suml){
                return st;
               }

               st++;
            
                
            }
            return -1;
        }

    
};
