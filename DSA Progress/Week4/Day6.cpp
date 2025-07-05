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

