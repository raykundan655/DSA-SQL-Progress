// graph is collection of nodes and vertices/
// imagine every node as city and edge as highway that connect two city it can be possible that city is not connected by other city 

// type of graph  based on edge 
// i.directed/uni-directed  ii.undirected/bidirectional
// based on weight
//i. weighted graph  ii. unweighted graph

//storing a graph (How we represent a graph inside memory (in code) so we can use it in algorithms.)
// i. adjacency list 
// ii. adjacency matrix
// iii. edge list


// Adjacency list (most use)
// It is a data structure used to store a graph
// For every node, we store a list of its neighbors (connected nodes)

// A data structure where each index represents a node, and
// the value at that index stores all its neighbors

// -> before make adjacency list we should to know
// how many nodes we have  ii.which type of graph it is


// undirected graph(unweighted)/directed  graph (unweighted)
// #include<bits/stdc++.h>
// using namespace std;

// class graph{
//     vector<int> * ptr;
//     int v;
//     bool dir;
//     public:
//     graph(int v,bool dir){
//         ptr=new vector<int>[v];  //v nodes are there 
//         this->dir=dir;
//         this->v=v;

//     }

//     void add(int u,int v){
//         if(u>=this->v || v>=this->v) return; //node number should under v
//         if(dir==false){
//             ptr[u].push_back(v);
//             ptr[v].push_back(u);
//         }
//         else{ //directed graph
//             ptr[u].push_back(v);
//         }
//     }

//     void print(){
//        for(int i=0;i<v;i++){
//         cout<<i<<"->"<<" ";
//         for(auto ele:ptr[i]){
//             cout<<ele<<" ";
//         }
//         cout<<endl;

//        }
//     }

//     ~graph(){
//     delete[] ptr;
//         }
// };


// int main(){
//     graph g(5,false);

//     while(true){
//         int v,u;
//         cin>>u>>v;
//         if(u==-1 && v==-1) break;

//         g.add(u,v);
//     }

//     g.print();
    
// }



// Undirected graph (weighted) / Directed graph(weighted)

// #include<bits/stdc++.h>
// using namespace std;

// class graph{
//     vector<vector<pair<int,int>>>*ptr;
//     int V;
//     bool dir;
//     public:

//     graph(int v,bool dir){
//         ptr=new vector<vector<pair<int,int>>>(v);
//         V=v;
//         this->dir=dir;
//     }

//     void add(int u,int v,int cost){
//         if(u>=V || v>=V) return;

//         if(dir==false){
//             // *ptr = the actual vector object
//             (*ptr)[u].push_back({v,cost});
//             (*ptr)[v].push_back({u,cost});
//         }
//         else{
//              (*ptr)[u].push_back({v,cost});
//         }

//     }

//     void print(){
//         for(int i=0;i<V;i++){
//             cout<<i<<"->";
//             for(auto ele:(*ptr)[i]){
//                 cout<<"{"<<ele.first<<" "<<ele.second<<"}";
//                 cout<<"->";
//             }
//             cout<<endl;
//         }
//     }



    
// };

// int main(){
//     int vert;
//     cout<<"enter no of node ";
//     cin>>vert;

//     graph g(vert,false);

//     for(int i=0;i<vert;i++){
//         int u,v,cost;
//         cin>>u>>v>>cost;
//         g.add(u,v,cost);
//     }

//     g.print();

// }



// Adjucency matrix

// it is a 2D matrix (V × V) used to represent a graph.

// V = number of vertices
// matrix[i][j] tells whether there is an edge from i → j(u->v)

// unweighted direted/undireted

// #include<bits/stdc++.h>
// using namespace std;


// class graph{
// vector<vector<int>>*ptr;
// int V;
// bool dir;
// public:

// graph(int v,bool dir){
//     V=v;
//     ptr=new vector<vector<int>>(v,vector<int>(v));
//     this->dir=dir;
// }

// void add(int u,int v){
//     if(u>=V || v>=V) return;

//     if(dir==false){
//         (*ptr)[u][v]=1;
//         (*ptr)[v][u]=1;
//     }
//     else{
//         (*ptr)[u][v]=1;
//     }
// }

// void print(){
//     for(int i=0;i<V;i++){
//         cout<<i<<"->";
//         for(int j=0;j<V;j++){
//             if((*ptr)[i][j]==1){
//                 cout<<j<<"->";
//             }
//         }
//         cout<<endl;

//     }
// }

// };

// int main(){
//     int v;
//     cout<<"enter no of vertex ";
//     cin>>v;

//     graph g(v,false);

//     for(int i=0;i<v;i++){
//         int u,v;
//         cin>>u>>v;
//         g.add(u,v);
//     }

//     g.print();
// }


// weighted graph ->just store cost instant of 1

// #include<bits/stdc++.h>
// using namespace std;


// class graph{
// vector<vector<int>>*ptr;
// int V;
// bool dir;
// public:

// graph(int v,bool dir){
//     V=v;
//     ptr=new vector<vector<int>>(v,vector<int>(v,INT_MIN));
//     this->dir=dir;
// }

// void add(int u,int v,int cost){
//     if(u>=V || v>=V) return;

//     if(dir==false){
//         (*ptr)[u][v]=cost;
//         (*ptr)[v][u]=cost;
//     }
//     else{
//         (*ptr)[u][v]=cost;
//     }
// }

// void print(){
//     for(int i=0;i<V;i++){
//         cout<<i<<"->";
//         for(int j=0;j<V;j++){
//             if((*ptr)[i][j]!=INT_MIN){
//                 cout<<j<<"("<<(*ptr)[i][j]<<")"<<"->";
//             }
//         }
//         cout<<endl;

//     }
// }

// };

// int main(){
//     int v;
//     cout<<"enter no of vertex ";
//     cin>>v;

//     graph g(v,false);

//     for(int i=0;i<v;i++){
//         int u,v,cost;
//         cin>>u>>v>>cost;
//         g.add(u,v,cost);
//     }

//     g.print();
// }




// EDGE LIST(we use this when we want to perform operation on edges)
// Instead of storing neighbors or a matrix, we just store all edges directly
// Edge List stores every edge of the graph as a pair (u, v)
// (or (u, v, w) if weighted)

// NOTE 
// An edge list represents a graph by storing all its edges as pairs of nodes like (u, v), 
// where in an undirected graph each edge is stored only once because it already represents both directions, 
// while in a directed graph each edge is stored exactly as it exists, so if both u → v and v → u are present, both are stored separately.

// #include<bits/stdc++.h>
// using namespace std;

// class graph{
//     vector<pair<int,int>>vec;
//     bool dir;
//     public:

//     graph( bool dir){
//         this->dir=dir;
//     }

//     void add(int u,int v){
        
//         vec.push_back({u,v});
        
//     }

//     void print(){
//         for(int i=0;i<vec.size();i++){
//             cout<<vec[i].first<<" "<<vec[i].second<<endl;
//         }
//     }

// };

// int main(){
//     graph g(false);

//     while(true){
//         int u,v;
//         cin>>u>>v;
//         if(u==-1 && v==-1) break;
//         g.add(u,v);
//     }

//     g.print();
// }