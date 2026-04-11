// #graph is not about all node is connected some times some nodes will be not connected or they are sepereate 
// eg main citys are conncted with each other but but some city present at the corner those are not connected by other


// if it is not mention that graph is singal connected graph then we do like this

#include<bits/stdc++.h>
using namespace std;

class graph{
vector<int>*ptr;
int V;
bool dir;
public:
graph(int v,bool dir){
    ptr=new vector<int>[v];
    V=v;
    this->dir=dir;
}

void add(int u,int v){
    if(dir==false){
        ptr[u].push_back(v);
        ptr[v].push_back(u);
    }
    else{
        ptr[u].push_back(v);
    }
}

void dfs(){
    vector<bool>visted(V,false);
    for(int i=0;i<V;i++){
        if(!visted[i]){
            helper(i,visted);
        }
    }
}

void helper(int u,vector<bool>&vist){
    queue<int>q;
    q.push(u);
    vist[u] = true;

    while(!q.empty()){
        int val=q.front();
        cout<<val;
        q.pop();
        for(auto ele:ptr[val]){
            if(!vist[ele]){
                vist[ele]=true;
                q.push(ele);
            }
        }
    }
}


};

int main() {
    // int V = 7;          
    // graph g(V, false); 

   
    // g.add(0, 1);
    // g.add(0, 2);
    // g.add(1, 3);
    // g.add(4, 5); // separate component
    // g.add(5, 6);

    int v,e;
    cout<<"enter the no of node and edge";
    cin>>v>>e;

    graph g(v,false);

    for(int i=0;i<e;i++){
        int u,vv;
        cin>>u>>vv;
        g.add(u,vv);
    }


    cout << "Traversal of graph:\n";
    g.dfs();

    return 0;
}