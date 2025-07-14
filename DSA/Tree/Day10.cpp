// 199. Binary Tree Right Side View 
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int>vec;
        if(root==nullptr){
            return vec;
        }
        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
            int size=q.size();
            for(int i=0;i<size;i++){
                TreeNode*curr=q.front();
                q.pop();
                if(i==size-1){
                    vec.push_back(curr->val);
                }
                if(curr->left!=nullptr){
                    q.push(curr->left);
                }
                if(curr->right!=nullptr){
                    q.push(curr->right);
                }
            }
        }
        return vec;
    }
};

// 235. Lowest Common Ancestor of a Binary Search Tree

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(p->val>q->val){
            swap(p,q);
            // swap th pointer now q pointing greater element and p pointing smaller one
        }
        if(q->val<root->val){
            // if q val is less then root means both node in left
           return lowestCommonAncestor(root->left,p,q);
        }
        else if(p->val>root->val){
            // if p val is greater then root it's mean both value in right
           return lowestCommonAncestor(root->right,p,q);
        }
        else{
            // return root where q val is not less then root or p val not greater it's mean it is lca that sepereta both
            return root;
        }
 }


     
};


// defination
// the Lowest Common Ancestor (LCA) of two nodes p and q is the lowest (i.e., deepest) node in the tree where the path to p and the path to q split — meaning one goes to the left subtree and the other goes to the right subtree from that node.

// How to Identify the LCA in a BST:
//At each node (root), you check:
// If both p and q are less → go left
// If both are greater → go right
// Otherwise → 🎯 this node splits the path → this is the LCA


// 872. Leaf-Similar Trees
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
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int>vec1,vec2;
        check(root1,vec1);
        check(root2,vec2);
        return vec1==vec2;
       
    }

    void check(TreeNode * root,vector<int>&vec){
        if(root ==nullptr){
            return;
        }
        if(root->left==nullptr && root->right==nullptr){
            vec.push_back(root->val);
        }
        check(root->left,vec);
        check(root->right,vec);
    }
};

// 513. Find Bottom Left Tree Value

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
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*>q;
        q.push(root);
        int val=0;
        while(!q.empty()){
            int size=q.size();
            for(int i=0;i<size;i++){
            TreeNode *curr=q.front();
            q.pop();
            if(i==0){
                val=curr->val;
            }
            if(curr->left!=nullptr){
                q.push(curr->left);
            }
            if(curr->right!=nullptr){
                q.push(curr->right);
            }


            }

        }
        return val;
    }
};
