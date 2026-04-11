// Dijkstra’s Algorithm
// It is used to find the shortest path from a source node to all other nodes in a graph.

// Conditions:
// Graph must have non-negative weights
// Works for directed + undirected graphs

// eg 
// Think of Google Maps:
// You are at point A
// You want shortest distance to all locations

// Dijkstra helps you always pick the closest unexplored location first

// A --2--> B
// A --4--> C
// B --1--> D
// C --3--> D

// From A, what is the shortest distance to all nodes?

// Imagine:
// You are standing at A

// You have 2 choices:
// Go to B (cost 2)
// Go to C (cost 4)

// Obviously, you go to B first because it's cheaper
// ⭐CORE IDEA (MOST IMPORTANT)
// Always go to the nearest node first
// This is the entire logic of Dijkstra

// Step-by-Step Working
// Let’s solve the example:

// Step 1: Initialize distance vector
// dist[A] = 0  dist of node from own is zero, and for rest we image we can't reach infinity
// dist[B] = ∞
// dist[C] = ∞
// dist[D] = ∞



// Step 2: Start from A
// From A:
// B → 2
// C → 4

// Edge relaxation = updating the shortest known distance to a node using an edge.
// Update:
// dist[B] = 2
// dist[C] = 4

// Step 3: Pick nearest node
// B (distance = 2) is smallest

// Step 4: Explore B

// From B:
// D = 2 + 1 = 3
// this called edge relaxtation

// Update:
// dist[D] = 3
// Step 5: Next nearest node
// Now:

// C = 4
// D = 3

// Pick D (3)

// Step 6: Explore D
// No better path → skip

// Step 7: Next node C
// From C:
// D = 4 + 3 = 7  (already have 3, so ignore)

// Final Answer
// A = 0
// B = 2
// C = 4
// D = 3


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

void Dijkstrasalgo(int src){
    vector<int>dist(V,INT_MAX);
    findSortestPath(dist,src);

    for(int i=0;i<V;i++){
        cout<<i<<"->"<<dist[i];
        cout<<endl;
    }
}

void findSortestPath(vector<int>&dist,int src){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
    q.push({0,src});
    dist[src]=0;

    while(!q.empty()){
        int node=q.top().second;
        int dis=q.top().first;
        q.pop();
        for(auto neigh:(*ptr)[node]){ //dist jo ush tak hai +dist woha se v tak pahuchna ka hai
            if(dist[neigh.first]>dis+neigh.second){
                dist[neigh.first]=dis+neigh.second;
                q.push({dist[neigh.first],neigh.first});
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
    g.Dijkstrasalgo(0);

    return 0;
}