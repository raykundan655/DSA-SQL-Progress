// It is use for acyclic graph(no cycle)
// sorting in graph does not mean  sort the data it's mean prevent the order

// Topological sort is an ordering of nodes in a Directed Acyclic Graph (DAG) such that:
// For every directed edge u → v, node u comes before v in the ordering.


// Core Idea
// In Topological Sort using DFS:
// We add a node ONLY AFTER all its dependencies are done

// 0 → 1
// 0 → 2
// 1 → 3
// 2 → 3

// Start from 0:

// Step 1:
// Go to 1
// Go to 3
// 3 has no child → push 3

// Step 2:
// Back to 1
// push 1

// Step 3:
// Back to 0 → go to 2
// 2 → push 2

// Step 4:
// Back to 0
// push 0


// [3, 1, 2, 0]
// Reverse:
// 0 2 1 3


// BEST ALGO KHANS ALGO 
// ----------------------------------

// MOST OPTIMIZED WAY TO DO TOPOLOGICAL SORTING is Kahn’s Algorithm

// It is a way to do topological sorting using BFS

// Always do:
// Task with NO dependency first
// Eg: 
// 0 → 1
// 1 depends on 0

// What is INDEGREE? (MOST IMPORTANT)
// Indegree = how many dependencies a node has(number of incoming edges)


// 0 → 1
// 0 → 2
// 1 → 3
// 2 → 3

// Step 1: Count indegree
// Let’s count:
// Node 0 → no one points to it → indegree = 0
// Node 1 → from 0 → indegree = 1
// Node 2 → from 0 → indegree = 1
// Node 3 → from 1 and 2 → indegree = 2

// indegree = [0, 1, 1, 2]

// Step 2: Find nodes with indegree = 0
// These have no dependency
// queue = [0]

// step 3

// Start processing
// Take 0
// answer = [0]
// Now remove 0 from graph
// Means reduce indegree of its neighbors

// Neighbors of 0:

// 1, 2
// Update:

// indegree[1]--
// indegree[2]--

// if(indegree[i]==0)
// Push them into queue

// queue = [1, 2]
// Take 1
// answer = [0, 1]

// Neighbors:   3

// Update:
// indegree[3]--

// like that ....





#include<bits/stdc++.h>
using namespace std;

class graph{
    int V;
    bool dir;
    vector<int>*ptr;
    public:
    graph(int v,bool dir){
        V=v;
        this->dir=dir;
        ptr=new vector<int>[V];
    }

    void add(int u,int v){
        if(u>=V || v>=V) return;
        if(dir){
            ptr[u].push_back(v);
        }
        else{
            ptr[u].push_back(v);
            ptr[v].push_back(u);
        }
    }

    void print(){
        for(int i=0;i<V;i++){
            cout<<i<<"->";
            for(auto ele:ptr[i]){
                cout<<ele<<"->";
            }
            cout<<endl;
        }
    }

    void bfs(){
        vector<bool>vist(V,false);
        for(int i=0;i<V;i++){
            if(vist[i]!=true)  bfshelper(i,vist);
        }

    }

    void bfshelper(int node,vector<bool>&vist){

        vist[node]=true;
        queue<int>q;
        q.push(node);

        while(!q.empty()){
            int val=q.front();
            q.pop();
            cout<<val<<" ";

            for(auto ele:ptr[val]){
                if(vist[ele]!=true){
                    vist[ele]=true;
                    q.push(ele);
                }
            }
        }

    }

    void dfs(){
        vector<bool>vist(V,false);
        for(int i=0;i<V;i++){
            if(vist[i]!=true){
                dfshelper(i,vist);
            }
        }
    }

    void dfshelper(int node,vector<bool>&vist){
        vist[node]=true;
        cout<<node<<" ";

        for(auto ele :ptr[node]){
            if(vist[ele]!=true){
                dfshelper(ele,vist);
            }
        }
    }


    bool detectcycle(){
        bool dirr=false;
        vector<bool>vist(V,false);
        if(dir==true){
            vector<bool>path(V,false);

            for(int i=0;i<V;i++){
                if(vist[i]!=true){
                    if(cycledtectionDirected(i,vist,path)){
                        dirr=true;
                        break;
                    }
                }
            }
            

           

        }
        else{
            for(int i=0;i<V;i++){
                if(vist[i]!=true){
                    if(cycledetectionUDirected(i,-1,vist)) {
                    dirr=true;
                    break;
                    }
                }
            }
            

        }

        return dirr;
    }

    bool cycledetectionUDirected(int node,int parent ,vector<bool>&vist){
        vist[node]=true;

        for(auto ele:ptr[node]){
            if(vist[ele]!=true){
                if(cycledetectionUDirected(ele,node,vist)) return true;
            }
            else{
                if(ele!=parent) return true;
            }
        }

        return false;

    }

    bool cycledtectionDirected(int node,vector<bool>&vist,vector<bool>&path){

        path[node]=true;
        vist[node]=true;

        for(auto ele:ptr[node]){
            if(vist[ele]!=true){
                if(cycledtectionDirected(ele,vist,path)) return true;
            }
            else{
                if(path[ele]==true) return true;
            }
        }

        path[node]=false;
        return false;

    }


    // TOPOLOGICAL SORTING

    void topologicalSorting(){
        vector<bool>vist(V,false);
        vector<int>stack;
        
        for(int i=0;i<V;i++){
            if(!vist[i]){
            helperSorting(i,vist,stack);

            }

        }

        reverse(stack.begin(),stack.end());
        cout<<"Topological Sorting by DFS: ";

        for(int i=0;i<stack.size();i++){
            cout<<stack[i]<<" ";
        }

}

    void helperSorting(int node ,vector<bool>&vist,vector<int>&stack){
        vist[node]=true;

        for(auto ele:ptr[node]){
            if(vist[ele]!=true){
                helperSorting(ele,vist,stack);
            }
        }

        stack.push_back(node);
    }


// best algoooooo
    // TOPOLOGICAL SORTING BY KHANAS ALGO

    void topo(){
        vector<int>indegree(V,0);
        for(int i=0;i<V;i++){
            for(auto ele:ptr[i]){
                indegree[ele]++;
            }
        }

        queue<int>q;

        for(int i=0;i<V;i++){
            if(indegree[i]==0){
                q.push(i);
            }
        }

        vector<int>ans;

        while(!q.empty()){
            int front=q.front();
            q.pop();
            ans.push_back(front);
            // now this node in remove from graph means  so now there neighbour indegree in decrease

            for(auto ele:ptr[front]){
                indegree[ele]--;
                if(indegree[ele]==0) q.push(ele);
            }
        }

        // print topological sorting by khans algo
        
        cout << "Topological Sorting by Kahn's Algo: ";
            for(auto x : ans){
                cout << x << " ";
            }
    }



};


int main(){

   
    graph g(6, true);

   
    g.add(5, 2);
    g.add(5, 0);
    g.add(4, 0);
    g.add(4, 1);
    g.add(2, 3);
    g.add(3, 1);

    cout << "Graph:\n";
    g.print();

    cout << "\nCycle Detection: ";
    if(g.detectcycle()){
        cout << "Cycle Present\n";
    } else {
        cout << "No Cycle\n";

        
        cout << "\n";
        g.topologicalSorting();   
        cout << "\n";
        g.topo();                 
    }

    return 0;
}