// Graph Traversal-> visiting all nodes of a graph in some order

// Two Main Types of Traversal
// 1. BFS (Breadth First Search)
// Level-wise traversal

// 2. DFS (Depth First Search)
// Go deep first, then backtrack

// BFS (Breadth First Search)->lavel by lavel(neighbour by neighbour)

// #include<bits/stdc++.h>
// using namespace std;

// class graph{
//     vector<int> *ptr;
//     int V;
//     bool dir;
//     public:

//     graph(int v,bool dir){
//         ptr=new vector<int>[v];
//         V=v;
//         this->dir=dir;
//     }

//     void add(int u,int v){
//         if(u>=V || v>=V) return;
//         if(dir==false){
//             ptr[u].push_back(v);
//             ptr[v].push_back(u);
//         }
//         else{
//             ptr[u].push_back(v);
//         }
//     }

//     void print(){
//         for(int i=0;i<V;i++){
//             cout<<i<<"->";
//             for(auto ele:ptr[i]){
//                 cout<<ele<<"->";
//             }
//             cout<<endl;
//         }
//     }

//     void bfs(){
//         queue<int>q;
//         vector<bool>visted(V,false);

//         q.push(0);
//         visted[0]=true;

//         while(!q.empty()){
//             int val=q.front();
//             q.pop();

//             cout<<val<<" ";

//             for(int i=0;i<ptr[val].size();i++){
//                 int neigh=ptr[val][i];
//                 if(!visted[neigh]){
//                     visted[neigh]=true;
//                     q.push(neigh);
//                 }
//             }


//         }
//     }
// };

// int main(){
//     int node,edge;
//     cout<<"No node and edges:";
//     cin>>node>>edge;

//     graph g(node,false);

//     for(int i=0;i<edge;i++){
//         int u, v;
//         cin >> u >> v;
//         g.add(u,v);
//     }

//     g.print();
//     cout<<endl<<"this is bfs ";
//     g.bfs();
    



// }


//DFS
// DFS is a traversal algorithm that explores nodes
// by going as deep as possible along each branch before backtracking.

// Break the Definition
// 1. “Start from a node”
// pick any node (like 0)

// 2. “Explore as far as possible”
// keep going deeper: 0 → 1 → 3 → 2

// 3. “Before backtracking”
// when no path left:
// go back
// try another path

// One-Line Memory Trick
// DFS = Go deep → hit dead end → come back → repeat




// #include<bits/stdc++.h>
// using namespace std;

// class graph{
//     vector<int>*ptr;
//     int V;
//     bool dir;
//     public:

//     graph(int v,bool dir){
//         ptr=new vector<int>[v];
//         V=v;
//         this->dir=dir;
//     }

//          void add(int u,int v){
//             if(u>=V || v>=V) return;
//             if(dir==false){
//                 ptr[u].push_back(v);
//                 ptr[v].push_back(u);
//             }
//             else{
//                 ptr[u].push_back(v);
//             }
//         }

//         void print(){
//             for(int i=0;i<V;i++){
//                 cout<<i<<"->";
//                 for(auto ele:ptr[i]){
//                     cout<<ele<<"->";
//                 }
//                 cout<<endl;
//             }
//         }

//         void dfshelper(){
//             vector<bool>visted(V,false);
//             dfs(visted,0);
//         }

//         // In DFS, the base condition is implicit, not written as a separate if at the top.

//         void dfs(vector<bool>&visted,int node){
//             visted[node]=true;
//             cout<<node<<" ";

//             for(int i=0;i<ptr[node].size();i++){
//                 int neigh=ptr[node][i];
//                 if(!visted[neigh]){ //act as base condition
//                     dfs(visted,neigh);
//                 }
//             }
//         }

   


// };

// int main(){
//     int node, edge;
//     cout << "Enter nodes and edges: ";
//     cin >> node >> edge;

//     graph g(node,false);

//     cout << "Enter edges:\n";
//     for(int i=0;i<edge;i++){
//         int u,v;
//         cin >> u >> v;
//         g.add(u,v);
//     }

//     cout << "\nAdjacency List:\n";
//     g.print();

//     cout << "\nDFS Traversal: ";
//     g.dfshelper();

//     return 0;
// }



