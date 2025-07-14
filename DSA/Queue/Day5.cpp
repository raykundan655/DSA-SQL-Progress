// 1701. Average Waiting Time
class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& cust) {
        deque<int>q;
        double waitt=0.0;
        for(int i=0;i<cust.size();i++){
             int arrival = cust[i][0];
            int process = cust[i][1];

                if( q.empty()||cust[i][0]>q.front()){
                    double pre=cust[i][0]+cust[i][1];
                    double wait=pre-arrival;
                    waitt+=wait;
                    q.push_front(pre);
                }
                else{
                    double pre=cust[i][1]+q.front();
                    double wait=pre-cust[i][0];
                      waitt+=wait;
                    q.push_front(pre);
                }
            
        }
        return waitt/cust.size();
    }
};

// 1823. Find the Winner of the Circular Game

class Solution {
public:
    int findTheWinner(int n, int k) {
        queue<int>q;
        for(int i=1;i<=n;i++){
            q.push(i);
        }
        while(q.size()>1){
            for(int i=1;i<k;i++){
                q.push(q.front());
                q.pop();
                // k-1  element go back in circle from starting
            }
            q.pop();
            // kth element are pop
        }

    // return the winner
        return q.front();

    }
};

// 238. Product of Array Except Self
// brute force(issue tc)
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int>pre;
        vector<int>vec;
        for(int i=0;i<nums.size();i++){
            int pro=1;
            for(int j=i+1;j<nums.size();j++){
                pro*=nums[j];
            }
            if(!pre.empty()){
                for(int k=0;k<pre.size();k++){
                    pro*=pre[k];
                }
            }
            vec.push_back(pro);
            pre.push_back(nums[i]);
        }
        return vec;
    }
      
};

// sol'n
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int>left(nums.size());
        vector<int>right(nums.size());
       int pre=1;
       for(int i=0;i<nums.size();i++){
            left[i]=pre;
            // storing the product of left side element 
            pre*=nums[i];
            
       }
       int suff=1;
       for(int j=nums.size()-1;j>=0;j--){
           right[j]=suff;
        //    storing  product right side  element 
           suff*=nums[j];
       }

    //    element=right*right 

       vector<int>result;
       for(int i=0;i<left.size();i++){
        result.push_back(left[i]*right[i]);
       }
       return result;
       
    }
      
};

// 387. First Unique Character in a String

class Solution {
public:
    int firstUniqChar(string s) {
        map<char,int>freq;
        for(int i=0;i<s.length();i++){
            freq[s[i]]++;
        }
        for(int i=0;i<s.length();i++){
            if(freq[s[i]]==1){
                return i;
            }
        }
        return -1;
    }
};

// You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        // transpose of matrix
        for(int i=0;i<matrix.size();i++){
            for(int j=i+1;j<matrix.size();j++){
               swap( matrix[i][j],matrix[j][i]);
            }
        }
       
    // reverse of row
    for(int i=0;i<matrix.size();i++){
        reverse(matrix[i].begin(),matrix[i].end());
    }

    for(int i=0;i<matrix.size();i++){
            for(int j=0;j<matrix.size();j++){
              cout<<matrix[i][j];
            }
        }

    }
    
};


// for rotate 180 degree
class Solution {
public:
    void rotate180(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // Step 1: Reverse each row
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }

        // Step 2: Reverse the order of rows (top to bottom)
        reverse(matrix.begin(), matrix.end());
    }
};
// input
    // {1, 2, 3},
    // {4, 5, 6},
    // {7, 8, 9}
// / Output matrix:
// [9 8 7]
// [6 5 4]
// [3 2 1]


// 1684. Count the Number of Consistent Strings

class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int count=0;
        for(int i=0;i<words.size();i++){
            int flag=false;
            for(int j=0;j<words[i].size();j++){
                flag=true;  
                for(int k=0;k<allowed.size();k++){
                    if(words[i][j]==allowed[k]){
                        flag=false;
                        break;
                    }
                 }

                if(flag){
                    break;
                }
                // agar ek bhi char matching nahi hai to break yeah word count nahi hoga


            }
            if(!flag){
                count++;
            } 
            // yeah string ushi char se bana hai to count kar liya
        }
        return count;
    }
};


