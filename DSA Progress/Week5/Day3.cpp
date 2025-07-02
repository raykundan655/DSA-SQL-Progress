// creating BinaryTree by lavelorder traversal

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
class tree{
    node *root=nullptr;
    public:
    
    void BinaryTree(){
        int val;
        cin>>val;
        if(val==-1){
            return;
        }
        root=new node(val);
        queue<node *>q;
        q.push(root);
        while(!q.empty()){
            node *curr=q.front();
            q.pop();
             cout << "Enter left child of " << curr->data << ": ";
            cin>>val;
            if(val!=-1){
                curr->left=new node(val);
                q.push(curr->left);
            }

            cout << "Enter right child of " << curr->data << ": ";
            cin>>val;
            if(val!=-1){
                curr->right=new node(val);
                q.push(curr->right);
            }

        }
    }

    // 2nd way
    void insert(int val){
        node * newnode=new node(val);
        if(root==nullptr){
            root=newnode;
            return;
        }
        queue<node *>q;
        q.push(root);
        while(!q.empty()){
            node * curr=q.front();
            q.pop();
            if(curr->left==nullptr){
                curr->left=newnode;
                break;
            }
            else{
                q.push(curr->left);
            }
            if(curr->right==nullptr){
                curr->right=newnode;
                break;
            }
            else{
                q.push(curr->right);
            }
        }

    }

    void preorder(){
        preorderR(root);
    }
    void preorderR(node * root){
        if(root==nullptr){
            return;
        }
        cout<<root->data<<" ";
        preorderR(root->left);
        preorderR(root->right);
    }

    
};
int main(){
    tree t;
    t.BinaryTree();

    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        t.insert(val);
    }
    t.preorder();
}
// find min and max val node from binary Tree
#include<iostream>
#include<algorithm>
#include<climits>
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

// finding max and min by this is not good practice in tree
// int maxxx=INT_MIN;
// void maxx(node * root){
//     if(root==nullptr){
//         return;
//     }
//     if(maxxx<root->data){
//        maxxx=root->data;
//     }
//     maxx(root->left);
//     maxx(root->right);
// }
// int minnn=INT_MAX;
// void minn(node *root){
//     if(root==nullptr){
//         return;
//     }
//     if(minnn>root->data){
//         minnn=root->data;
//     }
//     minn(root->left);
//     minn(root->right);
// }

// done by recussion and best method 

int maxx(node * root){
    if(root==nullptr){
        return INT_MIN;
    }
    int leftval=maxx(root->left);
    int rightval=maxx(root->right);

    return max(root->data,max(leftval,rightval));
}

int minn(node *root){
    if(root==nullptr){
        return INT_MAX;
    }
   int leftval=minn(root->left);
   int rightval=minn(root->right);
   return min(root->data,min(leftval,rightval));
}


int main(){
    node *root=BuildBinaryTree();
    maxx(root);
    // minn(root);
    // cout<<maxxx<<endl;
    // cout<<minnn;

    cout<<maxx(root);
    cout<<minn(root);
}

// Binary Search Tree
// A Binary Search Tree is a type of binary tree where each node has at most two children, and it follows a special property:
// BST Property:
// For every node:
// All values in the left subtree are less than the node value.
// All values in the right subtree are greater than the node value.

//        50
//       /  \
//     30    70
//    / \    / \
//  20  40  60  80

// Left child of 50 is 30 → 30 < 50 ✅
// Right child of 50 is 70 → 70 > 50 ✅
// Left of 30 is 20 → 20 < 30 ✅
// Right of 30 is 40 → 40 > 30 ✅
// And so on…

// creation bst
#include<iostream>
#include<queue>
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
class tree{
    node * root=nullptr;
    public:

    void BST(int val){
        root=createBST(val,root);
    }
   node * createBST(int val,node * root){
       
       if(root==nullptr){
        return new node(val);
       }
       if(val<root->data){
        root->left=createBST(val,root->left);
       }
       else{
        root->right=createBST(val,root->right);
       }
       return root;
   }

   void preorder(){
          preorderR(root);
   }
   void preorderR(node * root){
    if(root==nullptr){
        return ;
    }
    cout<<root->data<<" ";
    preorderR(root->left);
    preorderR(root->right);

   }

   void inorder(){
    inorderR(root);
   }

   void inorderR(node * root){
    if(root==nullptr){
        return ;
    }
    inorderR(root->left);
    cout<<root->data<<" ";
    inorderR(root->right);
   }

   void postorder(){
    postorderR(root);
   }

   void postorderR(node * root){
    if(root==nullptr){
        return;
    }
    postorderR(root->left);
    postorderR(root->right);
    cout<<root->data<<" ";
   }

   void levelorder(){
    if(root==nullptr){
        return;
    }
    queue<node *>q;
    q.push(root);
    while(!q.empty()){
        node *curr=q.front();
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

};
int main(){
    tree t;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;   
        }
        t.BST(val);
    }
    t.preorder();
    cout<<endl;
    t.inorder();
    cout<<endl;
    t.postorder();
    cout<<endl;
    t.levelorder();
}

// finding key in BST
#include<iostream>
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
class tree{
    public:
 node *root=nullptr;

  void create(int val){
    root=BST(val,root);
  }

  node * BST(int val,node * root){
    if(root==nullptr){
        return new node(val);
    }
    if(val<root->data){
        root->left=BST(val,root->left);
    }
    else{
        root->right=BST(val,root->right);
    }
    return root;
  }

  bool search(int key,node *root){
     if(root == nullptr) return false;  //base condition

      if(root->data==key){
        return true;
      }
      if(root->data>key){
        return search(key,root->left);
      }
      else{
        return search(key,root->right);
      }
  }

};
int main(){
    tree t;
    while(true){
        int val;
        cin>>val;
        if(val==-1){
            break;
        }
        t.create(val);
    }
    int key;
    cout<<"enter the key:";
    cin>>key;
    cout<<t.search(key,t.root);
}



