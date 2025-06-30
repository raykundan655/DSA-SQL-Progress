// Binary Tree
// A Binary Tree is a hierarchical data structure in which each node has at most two children, referred to as:
// Left child
// Right child
// Example:
//         A
//        / \
//       B   C
//      / \   \
//     D   E   F
// A is the root.
// B and C are children of A.
// D and E are children of B.
// F is the right child of C.


// A Hierarchical Data Structure is a way of organizing data in a tree-like structure, where:
// One element is at the top (called the root).
// Each element (called a node) may link to one or more child elements (called children).
// Each child has only one parent (except the root, which has none).
// This structure represents relationships like:

// Parent → Child

// Basic Terminologies
// Term	                     Description
// Node	                     Basic unit of a tree containing data
// Root	                     Topmost node
// Leaf Node	                 Node with no children
// Parent	                   A node having child nodes
// Child	                     Node under a parent
// Subtree	                   Any node along with its descendants
// Height	                   Longest path from node to a leaf
// Depth	                     Distance from root to that node
// Level	                     Number of edges from the root

// Why Use Binary Trees?
// Fast insertion and searching (in Binary Search Trees).
// Hierarchical data representation.
// Used in expression parsing, file systems, AI, and more

// Types of Binary Trees

// Type                  	      Description
// Full Binary Tree	            Every node has 0 or 2 children
// Perfect Binary Tree	          All levels are full
// Complete Binary Tree	         All levels full, except possibly last (filled left to right)
// Skewed Binary Tree	           All nodes have only left or right child
// Balanced Binary Tree	        Height difference between left and right subtree is minimal
// Binary Search Tree (BST)	    Left child < parent < right child

 // Tree Traversal Methods
// Traversal = visiting all nodes.

1. Inorder Traversal(Left → Root → Right)
// Note!!
// For BSTs, gives sorted order.
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}


// 2. Preorder (Root → Left → Right)
// Useful to copy the tree.

// 3. Postorder (Left → Right → Root)
// Useful to delete the tree.

// 4. Level Order (Breadth-First using Queue)
// void levelOrder(Node* root) {
//     if (!root) return;
//     queue<Node*> q;
//     q.push(root);

//     while (!q.empty()) {
//         Node* curr = q.front(); q.pop();
//         cout << curr->data << " ";
//         if (curr->left) q.push(curr->left);
//         if (curr->right) q.push(curr->right);
//     }
// }


// Buildind Binary Tree
#include<iostream>
#include<vector>
using namespace std;

class node{
    public:
    int data;
    node * left;
    node * right;
    node(int val){
        data=val;
        left=nullptr;
        right=nullptr;
    }
};

static int ind=-1;
// BUILD BINARY TREE FROM PREORDER DATA
node * buildingTree(vector<int>nodes){

ind++;
if(nodes[ind]==-1){
    return nullptr;
}
node * newnode=new node(nodes[ind]);
newnode->left=buildingTree(nodes);
newnode->right=buildingTree(nodes);
return newnode;

}

// preorder traversal
// root node ->left node ->right node ;

void preorder(node * root){
    if(root==nullptr){
        return;
    }
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

// inorder traversal
// left node->root node->right node 

void inorder(node * root){
    if(root==nullptr){
        return ;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);

}

// postorder traversal
// left node->right node->root

void postorder(node * root){
    if(root==nullptr){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";

}

void lavelOrder(node * root){
    if(root==nullptr){
        return;
    }
    queue<node*>q;
    q.push(root);
    while(!q.empty()){
        node * curr=q.front();
        cout<<curr->data;
        q.pop();
        if(curr->left!=nullptr){
            q.push(curr->left);
        }
        if(curr->right!=nullptr){
            q.push(curr->right);
        }
    }
}


int main(){
    vector<int>vec{1,2,4,-1,-1,5,-1,-1,3,-1,6,-1,-1};
    node* root=buildingTree(vec);
    preorder(root);
    cout<<endl;
    inorder(root);
    cout<<endl;
    postorder(root);
     cout<<endl;
     lavelOrder(root)

}

// /Creating the Binary data(another way)

#include<iostream>
#include<queue>
using namespace std;
class node{
    public:
    int data;
    node * left;
    node * right;
    node(int val){
        data=val;
        left=right=nullptr;
    }
};
node * buildTree(){
    int val;
    cin>>val;
    if(val==-1){
        return nullptr;
    }
    node * newnode=new node(val);
    newnode->left=buildTree();
    newnode->right=buildTree();
    return newnode;
}

void preorder(node * root){
    if(root==nullptr){
        return;
    }
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(node * root){
    if(root==nullptr){
        return;
    }
    inorder(root->left);
    cout<<root->data;
    inorder(root->right);
}

void postorder(node * root){
    if(root==nullptr){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data;
}
void lavelOrder(node * root){
    if(root==nullptr){
        return;
    }
    queue<node*>q;
    q.push(root);
    while(!q.empty()){
        node * curr=q.front();
        cout<<curr->data;
        q.pop();
        if(curr->left!=nullptr){
            q.push(curr->left);
        }
        if(curr->right!=nullptr){
            q.push(curr->right);
        }
    }
}

int main(){
    node * root=buildTree();

    preorder(root);
    cout<<endl;
    inorder(root);
    cout<<endl;
    postorder(root);
    cout<<endl;
    lavelOrder(root)
}










