// unweighted

// # cycle detection by using dfs
// # If you visit a node that is already visited and it is NOT your parent, then cycle exists. explain me this

// #include<bits/stdc++.h>
// using namespace std;

// class graph{
// vector<int>*ptr;
// int V;
// bool dir;
// public:
// graph(int v,bool dir){
//     ptr=new vector<int>[v];
//     V=v;
//     this->dir=dir;
// }

// void add(int u,int v){
//     if(dir==false){
//         ptr[u].push_back(v);
//         ptr[v].push_back(u);
//     }
//     else{
//         ptr[u].push_back(v);
//     }
// }

// void dfs(){
//     vector<bool>visted(V,false);
//     for(int i=0;i<V;i++){
//         if(!visted[i]){
//             helper(i,visted);
//         }
//     }
// }

// void helper(int u,vector<bool>&vist){
//     queue<int>q;
//     q.push(u);
//     vist[u] = true;

//     while(!q.empty()){
//         int val=q.front();
//         cout<<val;
//         q.pop();
//         for(auto ele:ptr[val]){
//             if(!vist[ele]){
//                 vist[ele]=true;
//                 q.push(ele);
//             }
//         }
//     }
// }

// bool detect(){
//     vector<bool>vist(V,false);
    
//     for(int i=0;i<V;i++){
//         if(vist[i]!=true){
//             if(cycledtection(vist,-1,i)){
//                 return true;
//             }
//         }
//     }

//     return false;
// }

// bool cycledtection(vector<bool>&vist,int par,int node){
//         vist[node]=true;

//         for(auto ele:ptr[node]){
//             if(!vist[ele]){
//                  if(cycledtection(vist,node,ele)) return true;
//             }
//             else{
//                 if(ele!=par){
//                     return true;
//                 }
//             }
//         }

//         return false;

// }


// };

// int main() {
//     graph g(5, false); 

//     // Add edges
//     g.add(0, 1);
//     g.add(1, 2);
//     g.add(2, 3);
//     g.add(3, 4);
//     g.add(4, 1); // this creates a cycle

    
//     cout << "Traversal: ";
//     g.dfs();
//     cout << endl;

//     // Cycle detection
//     if(g.detect()){
//         cout << "Cycle exists";
//     } else {
//         cout << "No cycle";
//     }

//     return 0;
// }




// Detection of cycle in weighted graph

// Use 2 arrays:
// visited[] → node visited or not
// recStack[] → node currently in recursion path

// Key Logic:
// If you reach a node that is already in recStack → Cycle found

#include<bits/stdc++.h>
using namespace std;

class graph{
    vector<int> *ptr;
    int V;
    bool dir;
    public:
    graph(int v,bool dir){
        V=v;
        ptr=new vector<int>[v];
        this->dir=dir;
    }

    void add(int u,int v){
        if(dir!=true){
            ptr[u].push_back(v);
            ptr[v].push_back(u);
        }
        else{
            ptr[u].push_back(v);
        }
    }

    void print(){
        for(int i=0;i<V;i++){
            cout<<i<<"->";
            for(auto ele:ptr[i]){
                cout<<ele<<" ->";
            }
            cout<<endl;
        }
    }

    void bfs(){
        vector<bool>vist(V,false);
        for(int i=0;i<V;i++){
            if(vist[i]!=true){
                helper(i,vist);
            }
        }
    }

    void helper(int node,vector<bool>&vist){

        queue<int>q;
        vist[node]=true;
        q.push(node);

        while(q.size()>0){
            int front=q.front();
            q.pop();
            cout<<front<<" ";

            for(auto ele:ptr[front]){
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
                helperdfs(i,vist);
            }
        }
    }

    void helperdfs(int node,vector<bool>&vist){
        vist[node]=true;
        cout<<node<<" ";

        for(auto ele:ptr[node]){
            if(vist[ele]!=true){
                helperdfs(ele,vist);
            }
        }
    }


    bool cycledetectionUW(){
        vector<bool>vist(V,false);

        for(int i=0;i<V;i++){
            if(vist[i]!=true){
                if(unweightedgraph(i,-1,vist)){
                    return true;
                }
            }
        }

        return false;
    }

    bool unweightedgraph(int node,int par,vector<bool>&vist){
        vist[node]=true;

        for(auto ele:ptr[node]){
            if(vist[ele]!=true){
                if(unweightedgraph(ele,node,vist)){
                    return true;
                }
            }
            else{
                if(ele!=par){
                    return true;
                }
            }
        }

        return false;

    }


    // cycle detction in weighted graph

    bool cycledetctionW(){
        vector<bool>vist(V,false);
        vector<bool>path(V,false);

        for(int i=0;i<V;i++){
            if(vist[i]!=true){
                if(cycledetectionweighted(vist,path,i)) return true;
            }
        }

        return false;
    }

    bool cycledetectionweighted(vector<bool>&vist,vector<bool>&path,int node){
            vist[node]=true;
            path[node]=true;

            for(auto ele:ptr[node]){
                if(vist[ele]!=true){
                    if(cycledetectionweighted(vist,path,ele)) return true;
                }
                else if(path[ele]){
                    return true;
                }
            }

            path[node]=false;
            return false;
    }


};


int main() {


    graph g(5, true);   

    // Add edges
    g.add(0, 1);
    g.add(1, 2);
    g.add(2, 3);
    g.add(3, 1); //  cycle here
    g.add(3, 4);

    cout << "Graph:\n";
    g.print();

    cout << "\nDFS Traversal: ";
    g.dfs();

    cout << "\nBFS Traversal: ";
    g.bfs();

    cout << "\n\nCycle Detection (Directed Graph): ";
    if(g.cycledetctionW()) {
        cout << "Cycle exists";
    } else {
        cout << "No cycle";
    }

    return 0;
}



