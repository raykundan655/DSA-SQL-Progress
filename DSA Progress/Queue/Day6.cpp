// 1295. Find Numbers with Even Number of Digits

class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int count=0;
        for(int i=0;i<nums.size();i++){
            string str=to_string(nums[i]);
            if(str.size()%2==0){
                count++;
            }
        }
        return count;
       
    }
};

// 1365. How Many Numbers Are Smaller Than the Current Number

class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
          int size=nums.size();
        
    vector<int>ans;
        int count;
        for(int i=0;i<size;i++){
            count=0;
            for(int j=0;j<size;j++){
                
                if(nums[j]<nums[i]){
                    count++;
                }
            }
            ans.push_back(count);
           
          }
          return ans;
        
    }
};

// 1480. Running Sum of 1d Array

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
    //     vector<int>vec;
    //     for(int i=0;i<nums.size();i++){
    //         int sum=0;
    //         for(int j=0;j<=i;j++){
    //             sum+=nums[j];
    //         }
    //         vec.push_back(sum);
    //     }
    //     return vec;
    // }

    // optimized
    for(int i=1;i<nums.size();i++){
        nums[i]=nums[i]+nums[i-1];
    }
    return nums;
    }
};

// 1108. Defanging an IP Address

class Solution {
public:
    string defangIPaddr(string address) {
        // size_t can represent larger positive values than int.
        size_t pos=0;
        string rep="[.]";

// string::npos is a constant in C++ that represents “no position” or “not found” when searching within a string.
        while((pos=address.find(".",pos))!=string::npos){
            // string& replace (size_t pos, size_t len, const string& str);

            address.replace(pos,1,rep);
            pos+=rep.size();
        }
        return address;

    }
};

// 1752. Check if Array Is Sorted and Rotated

class Solution {
public:
    bool check(vector<int>& nums) {
        int k=0;
        for(int i=0;i<nums.size();i++){
                bool flag=true;
                for(int j=0;j<nums.size()-1;j++){
                    if(nums[j]>nums[j+1]){
                        flag=false;
                    }
                }

                if(flag==false){
                    int num=nums[0];
                    for(int i=0;i<nums.size()-1;i++){
                        nums[i]=nums[i+1];
                    }
                    nums[nums.size()-1]=num;
                }

                if(flag==true){
                    return true;
                }


        }
        return false;


    }
};

// 1394. Find Lucky Integer in an Array

class Solution {
public:
    int findLucky(vector<int>& arr) {
      sort(arr.begin(),arr.end());
      int freq=1;
      int ind=-1;
      for(int i=1;i<arr.size();i++){
        if(arr[i-1]==arr[i]){
            freq+=1;;
        }
        else{
            if(arr[i-1]==freq){
               ind=arr[i-1];;
           
            }
             freq=1;
        }

      }

       if(arr.back() == freq) {
            ind = arr.back();
        }

      if(ind!=-1)
      return ind;
      else{
        return ind;
      }
    }
};

// 1865. Finding Pairs With a Certain Sum
// (brute force) t.c issue
class FindSumPairs {
    
public:
vector<int>&vec1;
vector<int>&vec2;
    FindSumPairs(vector<int>& nums1, vector<int>& nums2):vec1(nums1),vec2(nums2) {
        // can not intilized the reference data memeber from constructor
        
    }
    
    void add(int index, int val) {
        vec2[index]+=val;
        
    }
    
    int count(int tot) {
        int count=0;
        for(int i=0;i<vec1.size();i++){
            for(int j=0;j<vec2.size();j++){
                if(vec1[i]+vec2[j]==tot){
                    count++;
                }
            }
        }
        return count;
    }




};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */

// another approch(still issue t.c)

class FindSumPairs {
    
public:
vector<int>&vec1;
vector<int>&vec2;
    FindSumPairs(vector<int>& nums1, vector<int>& nums2):vec1(nums1),vec2(nums2) {
        // can not intilized the reference data memeber from constructor
        
    }
    
    void add(int index, int val) {
        vec2[index]+=val;
        
    }
    
    int count(int tot) {
        unordered_map<int, int> freq;
        for (int num : vec2) {
            freq[num]++;
        }

        int count = 0;
        for (int i = 0; i < vec1.size(); i++) {
            int need = tot - vec1[i];
            count += freq[need];
        }
        return count;
    }
    




};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */


// correct approch (think again)
class FindSumPairs {
public:
    vector<int> numsA,numsB;
    unordered_map<int,int> cnt;
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        numsA=nums1;
        numsB=nums2;
        for(auto j:numsB)   cnt[j]++;
    }
    
    void add(int index, int val) {
        cnt[numsB[index]]--;
        numsB[index]+=val;
        cnt[numsB[index]]++;
    }
    
    int count(int tot) {
        int ans=0;
        for(auto k:numsA)   ans+=cnt[tot-k];
        return ans;
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */
