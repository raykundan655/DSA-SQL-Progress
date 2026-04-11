// spanning tree->is subset of graph that include all vertices of original graph and all node are connected with  v-1 edge 

// What is MST (Minimum Spanning Tree)?

// Given:
// A connected graph With weighted edges

// Goal:
// Connect all vertices
// With minimum total weight
// Without forming any cycle

// Simple Intuition
// Think like this:
// You have cities and roads (with cost).
// You want to connect all cities with minimum total cost.
// That’s MST.

// Conditions of MST
// Must include all nodes
// Must have exactly V - 1 edges
// No cycles allowed
// Total weight must be minimum

// algo 

// It is building a tree step by step by always choosing the cheapest safe edge

// Think Like This (REAL INTUITION)
// You have:
// Some nodes already connected (your MST so far)
// Some nodes still outside

// Your job:
// “How can I connect a new node with minimum cost?”

// Step-by-Step Thinking
// 1. Start from any node
// Suppose node 0

// Now:
// Visited = {0}
// MST = empty
// 2. Look at all edges from visited nodes
// rom node 0, check:
// (0 → 1, weight 2)
// (0 → 3, weight 6)

// Put them in a “choices list”
// Pick the smallest edge

// Choose:
// (0 → 1, weight 2)

// Now:
// Visited = {0,1}
// MST = {(0-1)}

// 4. Expand from new node
// Now look at:
// edges from 0 AND 1
// Add new options:
// (1 → 2, 3)
// (1 → 4, 5)
// (1 → 3, 8)

// 5. Again pick smallest valid edge
// Choose:
// (1 → 2, weight 3)
// Now:
// Visited = {0,1,2}
// MST = {(0-1), (1-2)}
// Repeat this process

// Every time:
// Look at all edges from visited nodes
// Pick smallest edge
// Ignore if it goes to already visited node
// Add new node









#include<bits/stdc++.h>
using namespace std;

class graph{
    vector<vector<pair<int,int>>>*ptr;
    int V;
    bool dir;
    public:
    graph(int v,bool dir){
        ptr=new vector<vector<pair<int,int>>>(v);
        this->dir=dir;
        V=v;
    }

    void add(int u,int v,int cost){
        if(dir){
            (*ptr)[u].push_back({v,cost});
        }
        else{
            (*ptr)[u].push_back({v,cost});
            (*ptr)[v].push_back({u,cost});
        }
    }


    void bfs(){
        vector<bool>vist(V,false);
        for(int i=0;i<V;i++){
            if(!vist[i]){
                helperbfs(i,vist);
            }
        }
    }

    void helperbfs(int node,vector<bool>&vist){
        queue<int>q;
        vist[node]=true;
        q.push(node);

        while(!q.empty()){
            int front=q.front();
            q.pop();
            cout<<front<<" ";
            for(auto pair:(*ptr)[front]){
                if(!vist[pair.first]){
                    vist[pair.first]=true;
                    q.push(pair.first);
                }
            }
        }
    }


    void dfs(){
        vector<bool>vist(V,false);
         for(int i=0;i<V;i++){
            if(!vist[i]){
                helperdfs(i,vist);
            }
        }
    }

    void helperdfs(int node,vector<bool>&vist){
        vist[node]=true;
        cout<<node<<" ";

        for(auto pair:(*ptr)[node]){
            if(!vist[pair.first]){
                helperdfs(pair.first,vist);
            }
        }
    }



    bool cycledtection(){
        bool dirr=false;
        vector<bool>vist(V,false);
        if(dir){
            vector<bool>path(V,false);
            for(int i=0;i<V;i++){
                if(!vist[i]){
                    if(findcycleD(i,vist,path)){
                        dirr=true;
                        break;
                    }
                }
            }

        }
        else{
            for(int i=0;i<V;i++){
                if(!vist[i]){
                    if(findcycleUD(i,-1,vist)){
                        dirr=true;
                        break;
                    }
                }
            }

        }
        return dirr;
    }

    bool findcycleUD(int node,int par,vector<bool>&vist){
        vist[node]=true;

        for(auto pair:(*ptr)[node]){
            if(!vist[pair.first]){
                if(findcycleUD(pair.first,node,vist)) return true;
            }
            else{
                if(pair.first!=par) return true;
            }
        }

        return false;


    }


    bool findcycleD(int node,vector<bool>&vist,vector<bool>&path){
        vist[node]=true;
        path[node]=true;

        for(auto pair:(*ptr)[node]){
            if(!vist[pair.first]){
                if(findcycleD(pair.first,vist,path))return true;
            }
            else{
                if(path[pair.first]){
                    return true;
                }
            }
        }

        path[node]=false;
        return false;
    }


    bool bipartile(){
        vector<int>color(V,-1);
        vector<bool>vist(V,false);
        
        for(int i=0;i<V;i++){
            if(!vist[i]){
               if(!help(i,color,vist)) return false;
            }
        }

        return true;
    }

    bool help(int node,vector<int>&color,vector<bool>&vist){
            color[node]=0;
            vist[node]=true;
            queue<int>q;
            q.push(node);

            while(!q.empty()){
                int front=q.front();
                q.pop();
                for(auto pair:(*ptr)[front]){
                    if(!vist[pair.first]){
                    if(color[front]==0){
                        color[pair.first]=1;
                        q.push(pair.first);
                    }
                    else{
                        color[pair.first]=0;
                        q.push(pair.first);
                    }
                }
                else{
                    if(color[pair.first]==color[front]) return false;
                }

                }
            }

            return true;
    }


// it only happen for directed acyclic graph
    void topologicalsortingBydfs(){
        // topological sorting by dfs

        vector<int>st;
        vector<bool>vist(V,false);

         for(int i=0;i<V;i++){
            if(!vist[i]){
               helper(i,vist,st);
            }
        }

        reverse(st.begin(),st.end());

        for(int i=0;i<st.size();i++){
            cout<<st[i]<<" ";
        }

    }



    void helper(int node,vector<bool>&vist,vector<int>&st){
        vist[node]=true;

        for(auto pair:(*ptr)[node]){
            if(!vist[pair.first]){
                helper(pair.first,vist,st);
            }
        }

        st.push_back(node);
    }


    void topologicalSortingBykhansAlgo(){
        vector<int>inorder(V,0);

        for(int i=0;i<V;i++){
            for(auto pair:(*ptr)[i]){
                inorder[pair.first]++;
            }
        }

        vector<int>ans;
        queue<int>q;
        for(int i=0;i<inorder.size();i++){
            if(inorder[i]==0){
                q.push(i);
            }
        }

        while(!q.empty()){
            int front=q.front();
            q.pop();
            ans.push_back(front);

            for(auto pair:(*ptr)[front]){
                inorder[pair.first]--;
                if(inorder[pair.first]==0){
                    q.push(pair.first);
                }
            }
        }


 for(int x : ans){
    cout << x << " ";
}
        
    }

void dijkstraslgo(int src){
    vector<int>dist(V,INT_MAX);
    findpath(src,dist);

    for(int i = 0; i < V; i++){
        cout << i << " -> " << dist[i] << endl;
    }

    
}

void findpath(int src,vector<int>&dist){
    dist[src]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
    q.push({0,src});

    while(!q.empty()){
        int dis=q.top().first;
        int node=q.top().second;
        q.pop();

        if(dis > dist[node]) continue;  //optimized

        for(auto pair:(*ptr)[node]){
            if(dist[pair.first]>dis+pair.second){
                dist[pair.first] = dis + pair.second;
                q.push({dis+pair.second,pair.first});
            }
        }
    }


}

// -----------------------------------

// prism algoooo

void prismAlgo(int src){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;

    q.push({0,src});
    
    vector<bool>vist(V,false);
    int sum=0;
  


    while(!q.empty()){
        int dis=q.top().first;
        int node=q.top().second;
       
        q.pop();

        if(vist[node]) continue;

        vist[node] = true;
        sum+=dis;
       
        for(auto pair:(*ptr)[node]){
            if(!vist[pair.first]){
                q.push({pair.second,pair.first});
            }
        }
    }
   

    cout<<"total cost"<<sum;


}




};



int main(){


    graph g(5, false);

    g.add(0,1,2);
    g.add(0,3,6);
    g.add(1,2,3);
    g.add(1,3,8);
    g.add(1,4,5);
    g.add(2,4,7);

    cout<<"BFS: ";
    g.bfs();
    cout<<endl;

    cout<<"DFS: ";
    g.dfs();
    cout<<endl;

    cout<<"Cycle Detection (Undirected): ";
    cout<<(g.cycledtection() ? "Cycle Present" : "No Cycle")<<endl;

    cout<<"Bipartite Check: ";
    cout<<(g.bipartile() ? "Yes" : "No")<<endl;

    cout<<"Dijkstra (from node 0):"<<endl;
    g.dijkstraslgo(0);

    cout<<"Prim's MST:"<<endl;
    g.prismAlgo(0);

    // -----------------------------------
    // 2. Directed Graph (for Topological Sort)  Graph is DAG (Directed Acyclic Graph)
    graph dg(6, true);

    dg.add(5,2,1);
    dg.add(5,0,1);
    dg.add(4,0,1);
    dg.add(4,1,1);
    dg.add(2,3,1);
    dg.add(3,1,1);

    cout<<"Topological Sort (DFS): ";
    dg.topologicalsortingBydfs();
    cout<<endl;

    cout<<"Topological Sort (Kahn's): ";
    dg.topologicalSortingBykhansAlgo();
    cout<<endl;

    cout<<"Cycle Detection (Directed): ";
    cout<<(dg.cycledtection() ? "Cycle Present" : "No Cycle")<<endl;

    return 0;
}
