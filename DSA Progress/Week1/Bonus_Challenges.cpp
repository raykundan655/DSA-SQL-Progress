// 54. Spiral Matrix  
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& mat) {
        vector<int>vec;
        int sr=0,sc=0;
        int er=mat.size()-1;
        int ec=mat[0].size()-1;
        while(sr<=er && sc<=ec){
            for(int i=sc;i<=ec;i++){
                vec.push_back(mat[sr][i]);
            }
            sr++;
            for(int j=sr;j<=er;j++){
                vec.push_back(mat[j][ec]);
            }
            ec--;
          if(sr <= er) {
            // if condition prevent that no repetation
            for(int k=ec;k>=sc;k--){
                vec.push_back(mat[er][k]);
            }
            er--;
          }
          if(sc <= ec) {
            for(int l=er;l>=sr;l--){
                vec.push_back(mat[l][sc]);

            }
            sc++;
          }
        }
        return vec;
    }
};

// 443. String Compression

class Solution {
public:
    int compress(vector<char>& chars) {
        if(chars.size()==1) return 1;
        if(chars.size()==0) return 0;
    string arr="";
    
  int  count=1;
    for(int i=1;i<chars.size();i++){
     if(chars[i]==chars[i-1]){
    
        count++;
     }
       
     else {
        arr=arr+chars[i-1];
        if(count>1){
       arr+=to_string(count);
        }
        count=1;
    
     }
    }
    arr+=chars.back();
    if(count>1){
       arr+=to_string(count);
        }

    for(int i=0;i<arr.size();i++){
        chars[i]=arr[i];
    }
    return arr.size();
    }
    

};

// Bonus topic 
// // Sliding window
// Sliding Window is a technique used to efficiently solve problems involving subarrays or substrings (i.e., continuous elements), especially when you're:
// Looking for the maximum, minimum, sum, average, or a pattern of elements in a window (range) of size k


// Types of Sliding Window:
// 1. Fixed Size Window:
// Window size k is constant.
// You slide the window 1 step at a time.

// 2. Variable Size Window:
// Window size changes dynamically (e.g., expand/shrink based on conditions).
// Common in substring problems.


//     1. Fixed Size Window:
// Window size = 3
// String = "abcdef"

// Step 1: [a b c]
// Step 2:   [b c d]
// Step 3:     [c d e]
// Step 4:       [d e f]
//  window size is fixed =3
// removing one element and adding every timr through this we check all possibilty

// int maxSum(vector<int>& nums, int k) {
//     int sum = 0;
    
//     // Step 1: Add first k elements
//     for(int i = 0; i < k; i++) {
//         sum += nums[i];
//     }
    

//     int maxSum = sum;

//     // Step 2: Slide the window
//     for(int i = k; i < nums.size(); i++) {
//         sum = sum - nums[i - k] + nums[i];
//         // find max sum
//         maxSum = max(maxSum, sum);
//     }

//     return maxSum;
// }

//2 Variable Size Sliding Window
// We make a window using two variables:
// start: beginning of the window
// end: end of the window
// The size of the window can grow or shrink.

// Find the smallest subarray with sum <= target
// nums = [2, 3, 1, 2, 4, 3], target = 8


// dry run
// Step	Window	Sum	Action	                         minLength
// 1	     [1]	1	Too small, move end              	∞
// 2	    [1,2]	3	Still small, move end	            ∞
// 3	  [1,2,3]	6	Still small, move end	            ∞
// 4	  [1,2,3,4]	10	✅ Big enough → try shrinking	     4
// 5     [2,3,4]	9	Still big → try shrinking again	     3
// 6        [3,4]	7	❌ Too small → stop shrinking	       3
// 7	 [3,4,5]	12	✅ Again valid → try shrinking again	3
// 8      [4,5]	9	Still valid → shrink more	            2
// 9       [5]	5	❌ Too small	                             2


// class Solution {
// public:
//     int minSubArrayLen(int target, vector<int>& nums) {
//         int sum = 0;
//         int start = 0;
//         int minLen = INT_MAX;

//         for (int end = 0; end < nums.size(); end++) {
//             sum += nums[end]; // grow window

//             // shrink the window while sum is enough
//             while (sum >= target) {
//                 minLen = min(minLen, end - start + 1);
//                 sum -= nums[start];
//                 start++;
//             }
//         }

//         return (minLen == INT_MAX) ? 0 : minLen;
//     }
// };



// 3. Longest Substring Without Repeating Characters 
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size()==1){
            return 1;
        }
      int st=0;
      int end=0;
      int len=0;
      for(int i=end;i<s.size();i++){
        while(true){
          bool  flag=true;
            for(int j=end-1;j>=st;j--){
                if(s[j]==s[i]){
                    len=max(len,end-st);
                    st++;
                    flag=false;
                    break;
                }

            }
            if(flag){
                break;
                
            }

        }
        end++;
      }
      return max(len,end-st);
        
    }
};


// 643. Maximum Average Subarray I

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
      double sum=0;
      for(int i=0;i<k;i++){
        sum+=nums[i];
      }  
      double maxs=sum;
      for(int i=k;i<nums.size();i++){
        sum=sum-nums[i-k]+nums[i];
        maxs=max(sum,maxs);
      }
      return maxs/k;

    }
};







