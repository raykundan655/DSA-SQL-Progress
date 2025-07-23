// 973. K Closest Points to Origin

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& point, int k) {
        priority_queue<pair<double,vector<int>>,vector<pair<double,vector<int>>>,greater<>>p;
      
      for(int i=0;i<point.size();i++){
        int first=point[i][0];
        int second=point[i][1];
        double res=sqrt(((0-first)*(0-first))+((0-second)*(0-second)));
        p.push({res,{first,second}});
      }

    vector<vector<int>>vec;
      for(int i=0;i<k;i++){
        vec.push_back(p.top().second);
        p.pop();
      }
      return vec;

    }
};

// 373. Find K Pairs with Smallest Sums

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        priority_queue<pair<int,vector<int>>,vector<pair<int,vector<int>>>,greater<>>p;

        for(int i=0;i<nums1.size();i++){
            for(int j=0;j<nums2.size();j++){
                int sum=nums1[i]+nums2[j];
                p.push({sum,{nums1[i],nums2[j]}});
            }
        }

        vector<vector<int>>vec;
    for(int i=0;i<k;i++){
        vec.push_back(p.top().second);
        p.pop();
    }
    return vec;
    }
};

// Note memeory limit exceed

// 451. Sort Characters By Frequency

class Solution {
public:
    string frequencySort(string s) {
        sort(s.begin(),s.end());
        priority_queue<pair<int,char>,vector<pair<int,char>>,less<>>p;
        int size=1;
        for(int i=1;i<s.size();i++){
            if(s[i]==s[i-1]){
                size++;
            }
            else{
                p.push({size,s[i-1]});
                size=1;
            }
        }
        p.push({size,s[s.size()-1]});
        string str="";
        while(!p.empty()){
            int n=p.top().first;
           char ch = p.top().second;
            p.pop();

             while (n--) {
                str += ch;
            }
        }
        return str;
    }
};

