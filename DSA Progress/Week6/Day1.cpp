// 100. Same Tree

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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p==nullptr && q==nullptr){
            // both root become null then it's mean same
            return  true;
        }
        else if(p==nullptr || q==nullptr){
            // onr of then are become null but still other have node then not match
            return false;
        }
        if(p->val!=q->val){
            return false ;
        }
      return  isSameTree(p->left,q->left) &&
            isSameTree(p->right,q->right);


    }
};

// 101. Symmetric Tree

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
    bool isSymmetric(TreeNode* root) {
        if(root==nullptr){
            return true;
        }
        if(root->left==nullptr && root->right==nullptr){
            return true;
        }
        else if(root->left==nullptr || root->right==nullptr){
            return false;
        }

        return ischeck(root->left,root->right);
    }

    bool ischeck(TreeNode * r,TreeNode * p ){
       

        if(r==nullptr && p==nullptr){
            return true;
        }
        else if(r==nullptr || p==nullptr ){
            return false;
        }
         if(r->val!=p->val){
            return false;
        }
       
       return ischeck(r->left,p->right) && ischeck(r->right,p->left);

    }
};

// 104. Maximum Depth of Binary Tree

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
    int maxDepth(TreeNode* root) {
        if(root==nullptr){
            return 0;
        }
        int left=maxDepth(root->left);
        int right=maxDepth(root->right);
        return 1+max(left,right);
    }
};

// 144. Binary Tree Preorder Traversal

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
vector<int>vec;
    vector<int> preorderTraversal(TreeNode* root) {
        preorder(root);
        return vec;
      
    }
    void preorder(TreeNode * root){
        if(root==nullptr){
            return;
        }
        vec.push_back(root->val);
        preorder(root->left);
        preorder(root->right);

    }
};

// 94. Binary Tree Inorder Traversal

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
vector<int>vec;
    vector<int> inorderTraversal(TreeNode* root) {
        inorder(root);
        return vec;
        
    }
    void inorder(TreeNode * root){
        if(root==nullptr){
            return;
        }
        inorder(root->left);
        vec.push_back(root->val);
        inorder(root->right);

    }
};



// 145. Binary Tree Postorder Traversal

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
vector<int>vec;
    vector<int> postorderTraversal(TreeNode* root) {
        postorder(root);
        return vec;
    }
    void postorder(TreeNode *root){
        if(root==nullptr){
            return;
        }
        postorder(root->left);
        postorder(root->right);
        vec.push_back(root->val);
    }
};
