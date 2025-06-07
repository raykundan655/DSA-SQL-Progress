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
