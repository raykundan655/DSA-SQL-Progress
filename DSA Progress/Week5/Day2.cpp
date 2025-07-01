// Find height of tree
// max distance from root leaf node 
#include<iostream>
using namespace std;
class node{
    public:
    node * left;
    node * right;
    int data;
    node (int val){
        data=val;
        left=right=nullptr;
    }
};

node *  BuildBinaryTree(){
      int val;
      cin>>val;
      if(val==-1){
        return nullptr;
      }
      node * newnode=new node(val);
      newnode->left=BuildBinaryTree();
      newnode->right=BuildBinaryTree();
      return newnode;

}
void preorder(node * root){
    if(root==nullptr){
        return;
    }
    cout<<root->data;
    preorder(root->left);
    preorder(root->right);
}

int maxHeight(node * root){
    if(root==nullptr){
        return 0;
    }
    int leftHeight=maxHeight(root->left);
    // calculate the height of left subtree
    int rightHeight=maxHeight(root->right);
    // calculate the height of right subtree
    int curr=max(leftHeight,rightHeight)+1;
    // max height b/w left and right
    return curr;

}

int main(){
    node * root=BuildBinaryTree();
    cout<<maxHeight(root);
}


// Count total number of node
#include<iostream>
using namespace std;
class node{
    public:
    node * left;
    node * right;
    int data;
    node(int val){
        data=val;
        left=right=nullptr;
    }
};
class Tree{
    node* root=nullptr;
    public:
    void insert(){
        root=BuildBinaryTree();
    }

    node *BuildBinaryTree(){
        int val;
        cin>>val;
        if(val==-1){
            return nullptr;
        }
        node * newnode=new node(val);
        newnode->left=BuildBinaryTree();
        newnode->right=BuildBinaryTree();
        return newnode;
    }

    void countNode(){
        int number=count(root);
        cout<<number;
    }

     int count(node * root){
        if(root==nullptr){
            return 0;
        }
        int coun=count(root->left);
       // no of node in left subtree 
       int coun1=count(root->right);
       // no of node in right subtree

       return coun+coun1+1;
       
    }

    void inorderR(){
        inorder(root);
    }
    void inorder(node * root){
        if(root==nullptr){
            return;
        }
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
};
int main(){
    Tree t1;
    t1.insert();
    t1.inorderR();
    cout<<endl<<"count of node: ";
    t1.countNode();
}


// / Sum of all node 

#include<iostream>
using namespace std;
class node{
    public:
    node * left,*right;
    int data;
    node(int val){
        data=val;
        left=right=nullptr;
    }
};
class Tree{
    node * root=nullptr;
    
   node * BuildBinaryTree(){
           int val;
           cin>>val;
           if(val==-1){
            return nullptr;
           }
           node * newnode=new node(val);
           newnode->left=BuildBinaryTree();
           newnode->right=BuildBinaryTree();
           return newnode;
   }
   void postorder(node * root){
    if(root==nullptr){
         return ;
                 }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data;
   }
   int sum(node * root){
        if(root==nullptr){
            return 0;
        }
        int left=sum(root->left);
        int right=sum(root->right);
        return left+right+root->data;
   }
   public:
   void insert(){
    root=BuildBinaryTree();
   }
   void postorderR(){
    postorder(root);
   }
   void sumNode(){
       cout<<sum(root);
   }


};
int main(){
    Tree t1;
    t1.insert();
    t1.postorderR();
    cout<<endl<<"sum of nodes: ";
    t1.sumNode();
}

// findind subtree inside other tree(confusing little bit)
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
    node * root=nullptr;

    node * BuildBinaryTree(){
        int val;
        cin>>val;
        if(val==-1){
            return nullptr;
        }
        node * newnode=new node(val);
        newnode->left=BuildBinaryTree();
        newnode->right=BuildBinaryTree();
        return newnode;
    }

 
    bool identical(node * root,node * root1){
        if(root==nullptr && root1==nullptr){
            return true;
        }
        if (root == nullptr || root1 == nullptr){
           return false;
        }

        if(root->data!=root1->data){
        return false;
        }
        
         return  identical(root->left,root1->left) &&  identical(root->right,root1->right);
        
    }



    bool findSubtree(node * root,node * root1){
        if(root==nullptr && root1==nullptr){
            return true;
        }
       else if(root==nullptr || root1==nullptr){
            return false;
        }
        if(root->data==root1->data){
               return identical(root,root1);
        }
        else{
         return   findSubtree(root->left,root1) ||
                 findSubtree(root->right,root1);
        }
    }

    public:
    void insert() {
        root = BuildBinaryTree();
    }
       void levelorder(){
        if(root==nullptr){
            return;
        }
        queue<node *>q;
       q.push(root);
       while(!q.empty()){
        node * curr=q.front();
        q.pop();
        cout<<curr->data<<" ";
        if(curr->left!=nullptr){
        q.push(curr->left);
        }
        if(curr->right!=nullptr){
        q.push(curr->right);
       }
    }

    }
      node* getRoot() {
        return root;
    }
      bool isSubtree(Tree& otherTree) {
        return findSubtree(otherTree.getRoot(), root);
    }

};
int main(){
     Tree mainTree, subTree;
    mainTree.insert();
    subTree.insert();
    mainTree.levelorder();
    subTree.levelorder();
    if (mainTree.isSubtree(subTree)) {
        cout << "Yes";
    } else {
        cout << "No";
    }
        

}
