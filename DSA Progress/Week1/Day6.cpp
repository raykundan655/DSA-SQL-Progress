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
// this question can also done by swaping last and start untile start<=last

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

// i face problem in compare the char of first string with other string  at same time 


// 75. Sort Colors
// we can not use sort function of algorithm
// because of that i use bubble sort

class Solution {
public:
    void sortColors(vector<int>& nums) {
        for(int i=0;i<nums.size()-1;i++){
            for(int j=0;j<nums.size()-1-i;j++){
                if(nums[j]>=nums[j+1]){
                    swap(nums[j],nums[j+1]);
                }
            }
        }
        for(int i=0;i<nums.size();i++){
            cout<<nums[i]<<" ";
        }
    }
};


// 169. Majority Element

// brute force

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int majSize=nums.size()/2;
        int ind;
        for(int i=0;i<nums.size();i++){
            int count=1;
            for(int j=i+1;j<nums.size();j++){
                if(nums[i]==nums[j]){
                    count++;
                }
            }
            if(count>majSize){
                ind=i;
            }
        }
        return nums[ind];
    }
}

// issue is that with large input it give invalid ans

// optimized
class Solution {
public:
    int majorityElement(vector<int>& nums) {
   int majSize=nums.size()/2;
        sort(nums.begin(),nums.end());
        int count=1;
        for(int i=1;i<nums.size();i++){
           if(nums[i]==nums[i-1]){
            count++;
           }
           else{
            count=1;
           }

           if(count>majSize){
           return nums[i];
           }
          
        }
// 


// 189. Rotate Array
// brute force
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();

      int st=0;
    while(k--){
        int nu=nums[nums.size()-1];
        for(int i=nums.size()-1;i>0;i--){
            nums[i]=nums[i-1];
        }
        nums[0]=nu;
    
    }
    for(int i=0;i<nums.size();i++){
        cout<<nums[i]<<" ";
    }
        
    }
};
// time  exceede for large input

// optimized
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();

      reverse(nums.begin(),nums.end());
        // reverse all element
      reverse(nums.begin(),nums.begin()+k);
        // reverse the k element
       reverse(nums.begin()+k,nums.end());
    // reverse other
    
    for(int i=0;i<nums.size();i++){
        cout<<nums[i]<<" ";
    }
        
    }
};


// 88. Merge Sorted Array
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
     
      
      for(int i=0;i<n;i++){
       nums1[m+i]=nums2[i];
      }
      sort(nums1.begin(),nums1.end());
      for(int i=0;i<nums1.size();i++){
        cout<<nums1[i]<<" ";
      }

        
    }
};

// in nums1 vector already space given for nums2 element as zero we have to put nums2 element in place of zero then sort
// and this thing i missed after sometime i relised


// 287. Find the Duplicate Number
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        sort(nums.begin(),nums.end());
      int count=1;
        for(int i=1;i<nums.size();i++){
            // If the current number equals the previous one, it means a duplicate is found, so count is incremented.If not, it resets count to 1.
            if(nums[i-1]==nums[i]){
                count++;
            }
            else{
                count=1;
            }
            if(count==2){
                return nums[i];
            }
        }
        return nums[0];
    }
};

