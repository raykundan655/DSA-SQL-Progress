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
