// 700. Search in a Binary Search Tree

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
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root==nullptr){
            return nullptr;
        }
        if(root->val==val){
            return root;
        }
        if(val<root->val){
          return  searchBST(root->left,val);
        }
        else{
          return  searchBST(root->right,val);
        }
    }
};

// 701. Insert into a Binary Search Tree

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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root==nullptr){
            return new TreeNode(val);
        }
        if(val<root->val){
            root->left= insertIntoBST( root->left, val);
        }
        else{
            root->right= insertIntoBST( root->right, val);
        }
        return root;
    }
};

// 98. Validate Binary Search Tree

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
    bool isValidBST(TreeNode* root) {
        if(root==nullptr){
            return true;
        }
        if(root->left!=nullptr&&root->left->val>root->val){
            return false;
        }
        if(root->right!=nullptr&& root->right->val<root->val){
            return false;
        }
       return isValidBST(root->left) &&  isValidBST(root->right);

        
    }
};
// ISSUE I'M CHECKINF IMMEDIATE NODE ONLY BEACAUSE OF THIS SOLUTION IS FAIL

// NOTE
// A Binary Search Tree (BST) must follow this rule:
// For any node:
// All values in the left subtree must be less than the node's value.
// All values in the right subtree must be greater than the node's value.
  
// But this rule must apply to all descendants, not just immediate children.

// for that
// Range Method Concept:
// For each node, we pass down the allowed range of values it can have:
// For left child: min stays the same, max = parent->val
// For right child: min = parent->val, max stays the same


// done by range method
class Solution {
public:
    bool isValidBST(TreeNode* root) {
      return check(root,LONG_MIN,LONG_MAX);
    }

// range checking method
    bool check(TreeNode * root,long min,long max){
        if(root==nullptr){
            return true;
        }
        if(root->val<=min || root->val>=max) return false;

       return check(root->left,min,root->val) && check(root->right,root->val,max);

    }
};
// eg:
//                  10                         ( -∞ , ∞ )
//            /    \
//       5              15            ( -∞ ,10 )               (10, ∞)
//                     /    \
//                12         20                       (10,15)          (15, ∞)


// 226. Invert Binary Tree
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
    TreeNode* invertTree(TreeNode* root) {
        if(root==nullptr){
            return root;
        }
        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
            TreeNode *curr=q.front();
            q.pop();
           
        //    invert a binary tree, you must swap even when only one child exists.
                swap(curr->left,curr->right);
                // we are swaping left and right subtree
                // Inverting a binary tree means swapping the left and right child of every node in the tree.
            
            if(curr->left){
                q.push(curr->left);
            }
            if(curr->right){
                q.push(curr->right);
            }
        }
        return root;
    }
};
