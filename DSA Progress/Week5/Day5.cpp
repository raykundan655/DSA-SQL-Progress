//  Delation of node from BST

#include<iostream>
using namespace std;
class node{
    public:
    node *left,*right;
    int data;
    node(int val){
        data=val;
        left=right=nullptr;
    }
};

class Tree{
    node *root=nullptr;
    public:

    void BuildBinaryTree(int val){
             
        root=BuildTree(root,val);
    }

   node * BuildTree(node * root,int val){
        if(root==nullptr){
            return new node(val);
        }
        if(val<root->data){
            root->left=BuildTree(root->left,val);
        }
        else{
            root->right=BuildTree(root->right,val);
        }
        return root;
}

     node * findmin(node * root){
        if(root->left==nullptr){
            return root ;
        }
        findmin(root->left);
     }

    void deleteNode(int key){

        root=deleteR(root,key);

    }


    node * deleteR(node *root,int key){

        if(root==nullptr){
            return nullptr;
        }

        if(key<root->data){
            // checking the node  that we want to delete is present in left or right
            root->left=deleteR(root->left,key);
        }
        else if(key>root->data){
            root->right=deleteR(root->right,key);

        }
        else{
            // if it is not in left and right then current node is deleted node

            if(root->left==nullptr){
                node *temp=root->right;
                delete root;
                return temp;
            }
            else if(root->right==nullptr){
                node *temp=root->left;
                delete root;
                return temp;
            }
            else{
                node *temp=findmin(root->right);
                root->data=temp->data;
                root->right=deleteR(root->right,temp->data);
            }
        }
        return root;
    }

    void preorder(){
        preorderR(root);
    }

    void preorderR(node *root){
        if(root==nullptr){
            return;
        }
        cout<<root->data<<" ";
        preorderR(root->left);
        preorderR(root->right);
    }


};

int main(){
    Tree t;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
    
      t.BuildBinaryTree(val);

    }
    t.preorder();
    int key;
    cout<<"enter the key"<<endl;
    cin>>key;
    t.deleteNode(key);
    t.preorder();
}


// Complete Binary tree
// A complete binary tree is a type of tree where:

// Each level is filled completely from left to right,
// Except maybe the last level, which is also filled from left to right only.

   //      1
   //    /   \
   //   2     3
   //  / \   /
   // 4   5 6
// Always fill left to right, and don’t skip any spot in between.

 #include<iostream>
#include<queue>
using namespace std;

class node{
    public:
    int data;
    node *left,*right;
    public:
    node(int val){
        data=val;
        left=right=nullptr;
    }

};

class Tree{

node * root=nullptr;
public:

void lavelorder(int val){
    
    if(root==nullptr){
        root=new node(val);
        return;
    }

    queue<node*>q;
    q.push(root);
    while(!q.empty()){
        node * curr=q.front();
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
    Tree t;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        t.lavelorder(val);
    }
    t.inorder();
}


// delete node from Binary tree
//delete from binary tree
// 👣 Step-by-Step:
// Find the node to delete (target node).
// We need the deepest rightmost node of the entire tree — starting from the root, not from the node we want to delete.
// Replace the target node's data with the deepest node's data.
// Delete the deepest node.

#include<iostream>
using namespace std;
#include<queue>

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
    node *root=nullptr;
    public:

    void lavelorder(int val){
    
    if(root==nullptr){
        root=new node(val);
        return;
    }

    queue<node*>q;
    q.push(root);
    while(!q.empty()){
        node * curr=q.front();
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

    node * findright(node *root){
    queue<node*> q;
    q.push(root);
    node* curr;
    while (!q.empty()) {
        curr = q.front();
        q.pop();
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    return curr;  

    }

     void deleteNode(int key){
        if(root==nullptr) return ;

        queue<node *>q;
        q.push(root);
        node *last;
        while(!q.empty()){
            last=q.front();
     // store the node that is key
            q.pop();
            if(last->data==key){
                break;
            }
            if(last->left!=nullptr){
                q.push(last->left);
            }
            if(last->right!=nullptr){
                q.push(last->right);
            }
        }

        node *rightmost=findright(root);
            // find right most node of tree

        last->data=rightmost->data;
            // replace with rightmost node 

        deleterightmost(rightmost);
            delete rightmost node


     }

    void deleterightmost(node *target){
      
        queue<node *>q;
        q.push(root);
        while(!q.empty()){
            node *curr=q.front();
            q.pop();
            if(curr->left){
                if(curr->left==target){
                    delete curr->left;
                     curr->left = nullptr;
                    return;
                }
                else{
                    q.push(curr->left);
                }
            }
            if(curr->right){
                if(curr->right==target){
                    delete curr->right;
                    curr->right = nullptr;
                      return;
                }
                else{
                    q.push(curr->right);
                }
            }

        }


    }

    void inorder(){
        inorderR(root);

    }

    void inorderR(node * root){
        if(root==nullptr) return;
        inorderR(root->left);
        cout<<root->data<<" ";
         inorderR(root->right);

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
        t1.lavelorder(val);
    }
    int key;
    cin>>key;
    t1.deleteNode(key);
    cout<<endl;
    t1.inorder();

}
