// 110. Balanced Binary Tree

// BRUTE FORCE 

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:

// For every node in the tree, the absolute difference between the height of the left and right subtrees is not more than 1.
bool flag=true;
    bool isBalanced(TreeNode* root) {
          int num=Balanced(root);
          return flag;
    }

    int Balanced(TreeNode * root){

        if(root==nullptr){
        return 0;
     }
     int left=Balanced(root->left);
     int right=Balanced(root->right);

     if(abs(left-right)>1){
        flag= false;
     }
     
     return 1+max(left,right);

    }
};

// 617. Merge Two Binary Trees(logic building)

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if(root1==nullptr){
            return root2;
        }
        if(root2==nullptr){
            return root1;
        }

        TreeNode * merge=new TreeNode(root1->val+root2->val);

        merge->left=mergeTrees(root1->left,root2->left);

        merge->right=mergeTrees(root1->right,root2->right);

        return merge;
       
    }
};

// 543. Diameter of Binary Tree

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int dim=0;
        finddimention(root,dim);
        // calculate highest distance b/w left and right height of each node 
        // and return max height
        return dim;
    }
    int finddimention(TreeNode * root,int &dim){
        if(root==nullptr){
            return 0;
        }
        int left=finddimention(root->left,dim);
        int right=finddimention(root->right,dim);
        dim=max(dim,(left+right));
        return 1+max(left,right);
    }
};

