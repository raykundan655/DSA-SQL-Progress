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

