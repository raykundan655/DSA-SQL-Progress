// 215. Kth Largest Element in an Array

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int,vector<int>,greater<int>>minheap;
        
        for(auto num:nums){
            minheap.push(num);
            if(minheap.size()>k){  //fixed k size box->that contain only k element ->top node is kth highest node and (k-1)th node greater node then kth
                minheap.pop();
            }
        }
        return minheap.top();
    }
};


// 1337. The K Weakest Rows in a Matrix

class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        vector<pair<int,int>>order;
      
        for(int i=0;i<mat.size();i++){
            int size=0;
            for(int j=0;j<mat[i].size();j++){
                if(mat[i][j]==1){
                    size++;
                }
            }
            order.push_back({i,size});
        }

// in C++, when you pass a lambda function as the third argument to std::sort, you're telling it how to compare two elements, and that changes the default sorting behavior.

        sort(order.begin(),order.end(),[](pair<int,int>&a,pair<int,int>&b){
              if (a.second != b.second)
               return a.second < b.second;
             return a.first < b.first; // tie-breaker by index

        }
        );

        // [] is part of a lambda function in C++
        // A lambda in C++ is a short, inline function — useful especially for sorting, callbacks, etc.
        // syntex
//         [capture_list](parameters) -> return_type {
//     // function body
// }

// [] is the capture list. It tells the lambda which variables from the outside scope it is allowed to access.
// Capture List	Meaning
// []	Capture nothing (like in your sort)
// [x]	Capture x by value (copy)
// [&x]	Capture x by reference
// [=]	Capture all used outside variables by value
// [&]	Capture all used outside variables by reference



       vector<int>s;
       for(int i=0;i<k;i++){
        s.push_back(order[i].first);
       }
       return s;

    }
};


// By using heap
class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>minheap;
        
        //  greater<> means:
        // "Let the compiler figure out the type I want to compare."

         for(int i=0;i<mat.size();i++){
            int size=0;
            for(int j=0;j<mat[i].size();j++){
                if(mat[i][j]==1){
                    size++;
                }
            }
            minheap.push({size,i});
            // it sort first on the basis of size of solider in case of tie it arrange on the basis of row
        }

        vector<int>res;
        for(int i=0;i<k;i++){
            res.push_back(minheap.top().second);
            minheap.pop();
        }
        return res;
    }
};


// 347. Top K Frequent Elements

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        priority_queue<pair<int,int>,vector<pair<int,int>>,less<>>maxheap;
        int size=1;
        for(int j=1;j<nums.size();j++){
            if(nums[j]==nums[j-1]){
                size++;
            }
            else{
                maxheap.push({size,nums[j-1]});
                size=0;
            }

        }
        
         maxheap.push({size,nums[nums.size()-1]});

         vector<int>vec;
         for(int i=0;i<k;i++){
            vec.push_back(maxheap.top().second);
            maxheap.pop();
         }
         return vec;

    }
};


// To use istringstream and related functionality in C++, you need the <sstream> header.
  // Note(input String stream)
        // istringstream stands for input string stream.-> turns a string into an input stream.


        // string sentence = "this is a test";
        // A string in C++ is just a sequence of characters. It can contain letters, digits, punctuation, or anything else.
        // This is just plain text stored in a variable named sentence. You can access it like any string, print it, etc. But it doesn’t have a built-in way to easily split it into words.

        // istringstream iss(sentence);
        // This creates an input string stream object named iss, using the content of the string sentence

        // Think of istringstream like a fake input system: it lets you read from a string as if you're reading from cin (keyboard).
        // So now, you can extract data from sentence word by word, like you would extract input from the user.

// VIMP
// Jis type ke variable me aap >> se input lete ho, wohi cheez stream se nikali jaati hai.
// iss >> variable works based on the type of the variable on the right-hand side.

// Variable Type	    What it extracts from the stream
// string	            Extracts a word (up to space/tab/newline)
// int	                Extracts a number
// char	             Extracts a single character
// float / double	        Extracts a decimal number



// 692. Top K Frequent Words
// Input: words = ["i","love","leetcode","i","love","coding"], k = 2
// Output: ["i","love"]
// Explanation: "i" and "love" are the two most frequent words.
// Note that "i" comes before "love" due to a lower alphabetical order.

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {

        unordered_map<string, int> freq;

       for(auto &word:words){
        freq[word]++;
       } 

      // custom comp
       auto cmp=[](pair<string,int>a,pair<string,int>b){
        if(a.second==b.second){
            return a.first<b.first;   // min-heap: reverse lexicographical order
        }
        else{
            return a.second>b.second; // min-heap: less freq has higher priority
        }
       };
    //    We store the comparator in auto cmp = ... so we can reuse it, pass it to STL containers, or initialize objects like priority_queue that require a custom comparison logic.


// Step 3: Use min-heap of size k
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);
// auto cmp
// That lambda creates an unnamed object type, and there's no way to directly name its type like: priority_queue<..., MyCustomLambda>
// instead, decltype(cmp)->(Declared Type of an Expression) says:
// "Get the type of the cmp variable and use that here."

// 🔹 pq(cmp)
// This passes the lambda cmp to the constructor of the priority queue.
// The STL needs this to internally compare elements using your custom logic.

    
      for (auto &entry : freq) {
            pq.push({entry.first, entry.second});
            if (pq.size() > k) {
                pq.pop();  // remove lowest priority
            }
        }

        vector<string> result;
        while (!pq.empty()) {
            result.push_back(pq.top().first);
            pq.pop();
        }
        reverse(result.begin(), result.end());
        return result;

    }

};

