// Problem with Dijkstra 
// It fails when negative weights exist

// It can work for SOME negative edge cases
// But here is the real issue
// It is NOT guaranteed to work for ALL cases


// Bellman-Ford 
// Bellman-Ford is a shortest path algorithm used to 
// find the minimum distance from a source node to all other nodes in a graph, 
// even when negative edge weights are present.
// Key Idea:
// Relax all edges V−1 times (because the longest shortest path can have at most V−1 edges).

// Works with negative weights
// Can also detect negative cycles 

// 0 → 1 = 4  
// 0 → 2 = 5  
// 1 → 2 = -3  

// Step 1: Initialize dist vector
// dist[0] = 0
// dist[1] = ∞
// dist[2] = ∞

// Step 2: Relax edges (V-1 = 2 times)
// Iteration 1

// Check all edges:
// 0 → 1
// 0 + 4 = 4 → update dist[1] = 4

// 0 → 2
// 0 + 5 = 5 → dist[2] = 5

// 1 → 2
// 4 + (-3) = 1 → dist[2] = 1 ✅ better

// After iteration 1:
// [0, 4, 1]

// Iteration 2

// Check again:
// 0 → 1 → no change
// 0 → 2 → no change
// 1 → 2 → no change
// Stable now

// Step 3: Negative Cycle Check
// Run one more time:
// If anything updates → negative cycle


#include<bits/stdc++.h>
using namespace std;

class graph{
vector<vector<pair<int,int>>>*ptr;
int V;
bool dir;
public:

graph(int v,bool dir){
this->dir=dir;
V=v;
ptr=new vector<vector<pair<int,int>>>(V);
}

void add(int u,int v,int weight){
    if(dir){
        (*ptr)[u].push_back({v,weight});
    }
    else{
        (*ptr)[u].push_back({v,weight});
        (*ptr)[v].push_back({u,weight});

    }
}

void print(){
    for(int i=0;i<V;i++){
        cout<<i<<"->";
        for(auto ele:(*ptr)[i]){
            cout<<ele.first<<" "<<ele.second<<"->";
        }
        cout<<endl;
    }
}

void BellmanFord(int src){
    vector<int>dist(V,INT_MAX);
    findSortestPath(dist,src);

    for(int i=0;i<V;i++){
        cout<<i<<"->"<<dist[i];
        cout<<endl;
    }
}

void findSortestPath(vector<int>&dist,int src){
   dist[src]=0;

// we relax edges V−1 times because the longest possible shortest 
// path in a graph with V nodes can have at most V−1 edges.

   for(int i=0;i<V-1;i++){
    for(int u=0;u<V;u++){
        for(auto neigh:(*ptr)[u]){
            if(dist[u]!=INT_MAX && dist[neigh.first]>dist[u]+neigh.second){
                dist[neigh.first]=dist[u]+neigh.second;
            }
        }
    }
   }
   
// After this we again iterate over all neigh if it get updated means cycle

   // Step 2: Negative cycle check
    for(int u = 0; u < V; u++){
        for(auto neigh : (*ptr)[u]){
            if(dist[u] != INT_MAX && 
               dist[neigh.first] > dist[u] + neigh.second){
                
                cout << "Negative Cycle Detected!\n";
                return;
            }
        }
    }
   

    
}


};

int main() {
graph g(5, true);



g.add(0, 1, 2);
g.add(0, 2, 4);
g.add(0, 3, 1);  

g.add(1, 3, 3);
g.add(1, 4, 5);
g.add(2, 4, 1);
g.add(3, 2, 2);
g.add(3, 4, 6);

cout << "Graph:\n";
g.print();

cout << "\nShortest distances from source 0:\n";
g.BellmanFord(0);   

return 0;

}
