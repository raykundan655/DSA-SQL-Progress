// max and min in bst
#include<iostream>
using namespace std;
class node{
    public:
    int data;
    node * left,*right;
    node(int val){
        data=val;
        left=right=nullptr;
    }
};
class Tree{
    node *root=nullptr;
    public:
    void insert(int val){
        root=BST(root,val);
    }

    node * BST(node *root,int val){
        if(root==nullptr){
            return new node(val);
        }
        if(val<root->data){
            root->left=BST(root->left,val);
        }
        else{
            root->right=BST(root->right,val);
        }
        return root;
    }

    void findmin(){
        cout<<min(root)<<" ";
    }

    int min(node *root){
           if(root->left==nullptr){
            return root->data;
           }
         return  min(root->left);
    }

    void findmax(){
        cout<<max(root)<<" ";
    }

    int max(node *root){
           if(root->right==nullptr){
            return root->data;
           }
         return  max(root->right);
    }

    void inorder(){
        inorderR(root);
    }

    // left node ->root node ->right node;
    void inorderR(node * root){
        if(root==nullptr){
            return;
        }
        inorderR(root->left);
        cout<<root->data<<" ";
        inorderR(root->right);

    }

    void preorder(){
        preorderR(root);
    }

    // root node ->left node ->right node
    void preorderR(node * root){
        if(root==nullptr){
            return;
        }
        cout<<root->data<<" ";
        preorderR(root->left);
        preorderR(root->right);
    }

    void postorder(){
        postorderR(root);
    }

    // left node ->right node ->root node 
    void postorderR(node * root){

        if(root==nullptr){
            return;
        }
        postorderR(root->left);
        postorderR(root->right);
        cout<<root->data<<" ";
    }

};

int main(){
    Tree t1;
    
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        t1.insert(val);
    }

    t1.findmax();
    t1.findmin();
cout<<endl;
    // traversal
    t1.inorder();
    cout<<endl;
    t1.preorder();
    cout<<endl;
    t1.postorder();
}


// QUESTION OF BINARY TREE 
// // Ragul wants to write a program that performs a specific operation on a binary tree. 
// The program should take an array of elements as input and construct a binary tree. Once the tree is constructed, 
// the program should reverse the alternate levels of the binary tree. Finally, 
// it should print the in-order traversal of the modified tree.

// SUMMARY
// Build a binary tree from a given array (assume complete binary tree).
// Reverse the alternate levels of the binary tree.
// Print the in-order traversal of the modified tree.



#include<iostream>
using namespace std;
#include<queue>

class node{
    public:
    int data;
    node *left,*right;

    node(int val){
    left=right=nullptr;
        data=val;
    }
};

class Tree{
    public:
    node * root=nullptr;
   
    void  BuildBinaryTree(int arr[],int size){
        for (int i=0;i<size;i++){
            int val=arr[i];
            if(root==nullptr){
                root=new node(val);
                continue;
            }
            queue<node *>q1;
            q1.push(root);
            while(!q1.empty()){
                node * curr=q1.front();
                q1.pop();
                if(curr->left==nullptr){
                    curr->left=new node(val);
                    break;
                }
                else{
                    q1.push(curr->left);
                }
                if(curr->right==nullptr){
                    curr->right=new node(val);
                    break;
                }
                else{
                    q1.push(curr->right);
                }
            }
        }
    }

    void reverseTheNode(){
        if(root==nullptr){
            return;
        }
        queue<node *>q;
        q.push(root);

        int rev=false;
        while(!q.empty()){
            int size=q.size();
            for(int i=0;i<size;i++){
                node * curr=q.front();
                q.pop();
                if(rev && curr->left!=nullptr && curr->right!=nullptr){
                    swap(curr->left->data,curr->right->data);
                }
                if(curr->left!=nullptr){
                q.push(curr->left);
                }
                if(curr->right!=nullptr){
                q.push(curr->right);
                }

            }
            rev = !rev;
        }
    }

    void inorder(){
        inorderR(root);
    }

    void inorderR(node * root){
        if(root==nullptr){
            return;
        }
        inorderR(root->left);
        cout<<root->data<<" ";
        inorderR(root->right);
    }


};

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    Tree t1;
    t1.BuildBinaryTree(arr,size);
    t1.reverseTheNode();
    t1.inorder();

}


