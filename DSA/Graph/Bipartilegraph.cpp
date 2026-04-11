// You can divide all nodes into 2 separate groups
// And no edge connects nodes of the same group
// Group A = {0, 2}
// Group B = {1, 3}

// valid
// 0 — 1   (A → B) 
// 2 — 3   (A → B)

// invalid
// 0 — 2    (A → A)
// edge should not be present  b/w same group element


// Best way to check bipartite graph is using coloring approach
// Assign opposite color to neighbour
// If you are not able to assign colors such that
// no two adjacent nodes have same color,
// then the graph is NOT bipartite

// If all nodes can be colored using only 2 colors
// without any conflict, then the graph is bipartite



#include<bits/stdc++.h>
using namespace std;

class graph{
    vector<int>*ptr;
    int V;
    bool dir;

    public:
    graph(int v,bool dir){
        this->dir=dir;
        V=v;
        ptr=new vector<int>[v];
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

    bool bipartile(){
        vector<int>color(V,-1);

        for(int i=0;i<V;i++){
            if(color[i]==-1){
                if(check(i,color)==false){
                    return false;
                }
            }
        }
        return true;


    }

    bool check(int node ,vector<int>&color){
        color[node]=0;
        queue<int>q;
        q.push(node);

        while(!q.empty()){
            int front=q.front();
            q.pop();
            for(auto ele:ptr[front]){
                if(color[ele]==-1){
                    if(color[front]==0){
                        color[ele]=1;
                        q.push(ele);

                    }
                    else{
                        color[ele]=0;
                        q.push(ele);
                    }
                }
                else{
                    if(color[front]==color[ele])return false;
                }
            }
        }

        return true;


    }





};


int main() {

    
    graph g(4, false);

    g.add(0, 1);
    g.add(1, 2);
    g.add(2, 3);
    g.add(3, 0); // even cycle → bipartite

    cout << "Graph:\n";
    g.print();

    cout << "\nChecking Bipartite:\n";
    if(g.bipartile()){
        cout << "Graph is Bipartite";
    }
    else{
        cout << "Graph is NOT Bipartite";
    }

    return 0;
}