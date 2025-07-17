// Heap:
// complete binary Tree that comes with heap order property

// Heap order 

// max heap
// parent node always greater then child

// min heap
// parent node always smaller then child

// heap implement as a form of array->beacuse it make easy to access the child and parent node

// WHEN INSERTION OF NODE IN ARRAY START WITH 1st INDEX 
// THEN:

// left child=2*i 
// right child=2*i+1
// parent =i/2

// IF IT START FROM 0th INDEX 
// THEN:

// left child=2*i+1
// right child=2*i+2
// parent=(i-1)/2


// just for basic building Tree part is not necessary
#include<iostream>
#include<queue>
using namespace std;

class node{
    public:
    int data;
    node *left,*right;
    node(int val){
        data=val;
        left=right=nullptr;
    }
};

class Tree{
    public:
    node * root=nullptr;

    void BuildBinaryTree(){
        while(true){
            int val;
            cin>>val;
            if(val==-1){
                break;
            }
           if(root==nullptr){
            root=new node(val);
            continue;
           }
           queue<node*>q;
           q.push(root);
           while(!q.empty()){
            node *curr=q.front();
            q.pop();
            if(curr->left==nullptr){
                curr->left=new node(val);
                break;
            }
            else{
                q.push(curr->left);
            }

            if(curr->right==nullptr){
                curr->right=new node(val);
                break;
            }
            else{
                q.push(curr->right);
            }

           }

            
        }
    }
    void display(vector<int>&vec){
        if(root==nullptr){
            return;
        }
        queue<node*>q;
        q.push(root);
        while(!q.empty()){
            node *curr=q.front();
            q.pop();
           vec.push_back(curr->data);
            if(curr->left!=nullptr){
                q.push(curr->left);
            }
            if(curr->right!=nullptr){
                q.push(curr->right);
            }
        }

    }
};

class heap{
    public:
    int arr[100];
    int size=0;

    // insert the element at the end of array
    // take it to its correct position by comparing with parent ->depend upon min/max heap

    void insert(int val){
      // zero index that why i assign first then move the size
       int index=size;
        size=size+1;
        arr[index]=val;

        while(index>0){
            int p=(index-1)/2;
            // follwing max heap->parent node always greater ->p means parent
            if(arr[p]<arr[index]){
                swap(arr[p],arr[index]);
                index=p;
               // that node may be become the child of some other node so we have to check there also ->it statosy the property or not

            }
            else{
                return;
            }
        }
}

void display(){
    for(int i=0;i<size;i++){
        cout<<arr[i]<<" ";
    }
}


};

int main(){
    Tree t1;
    vector<int>vec;
    t1.BuildBinaryTree();
    t1.display(vec);
    heap h1;
    for(int i=0;i<vec.size();i++){
        h1.insert(vec[i]);
    }
    h1.display();

}


// Tree part is for understanding only in previous question
#include<iostream>
using namespace std;

class heap{

    int arr[100];
    int size=0;
    public:
    
    void insert(int val){
        int ind=size;
        arr[ind]=val;
        size=size+1;

        // max heap
        while(ind>0){
            int parent=(ind-1)/2;
            if(arr[parent]<arr[ind]){
                swap(arr[parent],arr[ind]);
                ind=parent;
                // that node may be become the child of some other node so we have to check there also ->it statosy the property or not
            }
            else{
                break;
            }
        }


    }

    void display(){
        for(int i=0;i<size;i++){
            cout<<arr[i]<<" ";
        }
    }
};
int main(){
heap h1;

 while(true){
int data;
cin>>data;
if(data==-1){
    break;
}
h1.insert(data);

}

h1.display();

}


// heap by using vector

#include<iostream>
#include<vector>
using namespace std;

void insert(vector<int>&vec,int val){

    vec.push_back(val);
    
    int ind=vec.size()-1;
      

    // min heap ->parent always smaller then child 
    while(ind>0){
        int par=(ind-1)/2;
        if(vec[par]>vec[ind]){
            swap(vec[par],vec[ind]);
            ind=par;
        }
        else{
            break;
        }

    }
}

int main(){
vector<int>vec;
while(true){
int data;
cin>>data;
if(data==-1){
    break;
}
insert(vec,data);

}

for(int i=0;i<vec.size();i++){
    cout<<vec[i]<<" ";
}

}



//  Delation in heap
// IN HEAP WE ONLY TALK ABOUT DELATION OF ROOT ONLY->WE CAN ONLY DELETE ROOT OF HEAP

// STEP
// swap last node value with root
// remove the last node
// propogate root node to its correct position->root ko compare kara ga ush ke child se and jo 
// max/min(base on heap property) hai ush se swap kar denga and this process will continue until it reach it's correct postion


#include<iostream>
using namespace std;

class heap{
    int arr[100];
    int size=0;
    public:

    void insert(int val){
        int ind=size;
        arr[ind]=val;
        size=size+1;
        while(ind>0){
            int parent=(ind-1)/2;
            if(arr[parent]<arr[ind]){
                swap(arr[parent],arr[ind]);
                ind=parent;
            }
            else{
                break;
            }
        }

    }

// PROBLEM:
// If the left child is greater, you swap and move down to the left — without checking if right child is even greater.
// This leads to incorrect placement and breaks heap property in some cases.
    // void deleteNode(){
    //     if(size==0){
    //         cout<<"there is no node to delete ";
    //         return;
    //     }
    //     arr[0]=arr[size];
    //     size--;

    //     int ind=0; //this repersent root node 

    //     while(ind<size){
    //         int leftchild=ind*2+1;
    //         int rightchild=ind*2+2;
            
    //         if(leftchild<size && arr[leftchild]>arr[ind]){
    //             swap(arr[leftchild],arr[ind]);
    //             ind=leftchild;
    //         }
    //         else if(rightchild<size && arr[rightchild]>arr[ind]){
    //             swap(arr[rightchild],arr[ind]);
    //             ind=rightchild;
    //         }
    //         else{
    //             return;
    //         }

    //     }
    // }



// deletion on the basis of max heap property

    void deleteNode(){
        if(size==0){
            cout<<"no element to delete ";
            return;
        }
        arr[0]=arr[size-1] ; //replace last node with first

        size--; //delete last node

        int ind=0 ; //it pointing the new root

        while(ind<size){
            int largest=ind; // initial it suppose root at correct position
            int leftchild=ind*2+1;
            int rightchild=ind*2+2;

            if(leftchild<size && arr[leftchild]>arr[largest]){
                largest=leftchild; //left child is greater then largest
            }
// Why not <= size?
// Because size itself is not a valid index in a 0-based array.
// Using <= size would allow leftchild == size, which means you're trying to access arr[size], which is:
// Out of bounds

            if(rightchild<size && arr[rightchild]>arr[largest]){
                largest=rightchild;
            }

            // largest store the ind of child that is greater then root

            if(largest!=ind){
                swap(arr[largest],arr[ind]);
                ind=largest;
                // now ind become that node where it swap ->now it again check it is on correct position or not
            }
            else{
                break; //means it is on correct pos
            }
        }

    }

    void display(){
        for(int i=0;i<size;i++){
            cout<<arr[i]<<" ";
        }
    }

};

int main(){
    heap h1;

while(true){
int data;
cin>>data;
if(data==-1){
    break;
}
h1.insert(data);

}
h1.deleteNode();

h1.display();

}


//Delation with the help of heapify function

#include<iostream>
using namespace std;

class heap{
    int data[100];
    int size=0;

    public:

// Heapify work on top to bottom approch
// It means that the heapify algorithm starts from a node (usually a parent) and goes downward,
// comparing it with its children, and pushing it down the tree if needed — until the heap property is satisfied.

// How:
// You start at a node (often the root or some internal node).
// You compare it with its children.
// If the node violates the heap property, you swap it with the larger child (in a max-heap).
// Then, you continue this process at the new child index.
// This continues down the tree — hence, top to bottom


    void heapify(int size,int ind){
        int largest=ind;
        int leftchild=2*ind+1;
        int rightchild=2*ind+2;

        if(leftchild<size && data[leftchild]>data[largest]){
            largest=leftchild;
        }
        if(rightchild<size && data[rightchild]>data[largest]){
            largest=rightchild;
        }

        if(largest!=ind){
            swap(data[largest],data[ind]);
            heapify(size,largest);
        }
    }


    // INSERTION->BUTTOM->TOP APPROCH
    // Add the element at the end of the array (which represents the heap).

    // HOW:
    // The heap may now violate the heap property, so:
    // Compare the inserted element with its parent.
    // If it's greater than the parent → swap them.
    // Repeat this until:
    // The element is not greater than its parent, or
    // It becomes the root.
    // This is called SIFT-UP or BUBBLE-UP, and it moves bottom to top.


   void insert(int val){
        int ind=size;
        size++;
        data[ind]=val;
        // Sift up to maintain max-heap
        // NOTE
        // insertion done ->Bottom to top ↑->	Fix heap property upward
        // heapify work with only top to bottom approch

       while (ind > 0) {
    int parent = (ind - 1) / 2;
    if (data[parent] < data[ind]) {
        swap(data[parent], data[ind]);
        ind = parent;
    } else {
        break;
    }
}


    }

    void display(){
        for(int i=0;i<size;i++){
            cout<<data[i]<<" ";
        }

    }

    void deleteNode(){
        data[0]=data[size-1];

        size--;

        heapify(size,0);
    }
};
int main(){
    heap h1;

    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        h1.insert(val);
    }

    h1.display();
    h1.deleteNode();
    cout<<endl;
    h1.display();

}



