// 378. Kth Smallest Element in a Sorted Matrix

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<int,vector<int>,greater<int>>p;

        for(int i=0;i<matrix.size();i++){
            for(int j=0;j<matrix[i].size();j++){
                p.push(matrix[i][j]);
            }
        }

        for(int i=0;i<k-1;i++){
            p.pop();
        }
        return p.top();

    }
};

// 1387. Sort Integers by The Power Value

class Solution {
public:
    int getKth(int lo, int hi, int k) {

// The comparator tells the STL which one comes first.
// If comp(a, b) returns true, then a comes before b.
// std::sort(v.begin(), v.end(), [](int a, int b) {
//     return a < b; // true means a comes before b
// });
// eg
// a	b	a < b	Meaning
// 3	5	true	✅ a (3) comes before b (5)
// 7	2	false	❌ a (7) does not come before b (2) → so b (2) comes before a (7)

// 🚫BUT — priority_queue is different:
// Because it’s a heap, not a sorted list.
// It uses the comparator to maintain the heap property, and it applies it in reverse internally.


        auto cmp=[](pair<int,int>a,pair<int,int>b){
            if(a.first!=b.first)  return a.first>b.first;
            else return a.second>b.second;
        };
        priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(cmp)>p(cmp);

        for(int i=lo;i<=hi;i++){
            int val=i;
            int size=0;
            while(val!=1){
                if(val%2==0){
                    val=val/2;
                    size++;
                }
                else{
                    val=val*3+1;
                    size++;
                }
            }
            p.push({size,i});
        }

        while(k>1){
            p.pop();
            k--;
        }
        return p.top().second;
        
    }
};


// Practice question ->no realtion of heap
// 167. Two Sum II - Input Array Is Sorted

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int>vec;
        int first=0;
        int sec=numbers.size()-1;
        while(first<=sec){
            if(numbers[first]+numbers[sec]<target){
                first++;
            }
            else if(numbers[first]+numbers[sec]>target){
                sec--;
            }
            else{
                vec.push_back(first+1 );
                vec.push_back(sec+1 );

                return vec;
            }
        }
        return vec;
    }
};
