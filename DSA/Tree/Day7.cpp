// 102. Binary Tree Level Order Traversal

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
vector<vector<int>>vec;
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root==nullptr){
            return vec;
        }

        queue<TreeNode*>q;
         q.push(root);

        while(!q.empty()){

            int size=q.size();

            vector<int>label;

           for(int i=0;i<size;i++){
//  for (int i = 0; i < q.size(); i++)	❌ Dangerous – q.size() changes during loop, leading to logic bugs or infinite loops
            TreeNode * curr=q.front();

            q.pop();

            label.push_back(curr->val);

            if(curr->left!=nullptr){
                q.push(curr->left);
            }

            if(curr->right!=nullptr){
                q.push(curr->right);
            }

           }
           vec.push_back(label);
        }
        return vec;
    }
    
};

// 107. Binary Tree Level Order Traversal II

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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>>vec;
        
        if(root==nullptr){
            return vec;
        }

        queue<TreeNode*>q;

        q.push(root);

        while(!q.empty()){
            int size=q.size();
            vector<int>label;
            for(int i=0;i<size;i++){

                TreeNode * curr=q.front();
                q.pop();
                label.push_back(curr->val);
                if(curr->left!=nullptr){
                    q.push(curr->left);
                }

                 if(curr->right!=nullptr){
                    q.push(curr->right);
                }

            }
            vec.push_back(label);

        }
        reverse(vec.begin(),vec.end());
        return vec;

    }
};

// 103. Binary Tree Zigzag Level Order Traversal
// Given the root of a binary tree,
// return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

// Note
// (BRUTE FORCE ->I'M modifying the actual tree node values here. That’s not what zigzag traversal requires.
// 📌 Zigzag traversal is about the order in which values are collected, not changing node values.)  IT'S WRONG


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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>vec;

        if(root==nullptr){
            return vec;
        }

        queue<TreeNode*>q;
        
        q.push(root);

        bool rev=true;

        while(!q.empty()){
            int size=q.size();
            vector<int>label;

            for(int i=0;i<size;i++){
                 TreeNode * curr=q.front();
                 q.pop();

                 label.push_back(curr->val);

                 if(curr->left!=nullptr && curr->right!=nullptr && rev){
                    swap(curr->left->val,curr->right->val);
                 }

                 if(curr->left!=nullptr){
                    q.push(curr->left);
                    }

                  if(curr->right!=nullptr){
                    q.push(curr->right);

                 }

              }
              rev=!rev;

             vec.push_back(label) ;

        }

        return vec;

    }
};


// CORRECT APPROACH
  //     1
  //    / \
  //   2   3
  //  / \   \
  // 4   5   6

// [
//   [1],
  // [3, 2],  //right to left
//   [4, 5, 6]
// ]



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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>vec;

        if(root==nullptr){
            return vec;
        }

        queue<TreeNode*>q;
        
        q.push(root);

        bool rightToleft=false; //when we are going right to left then doing reverse

        while(!q.empty()){
            int size=q.size();
            vector<int>label;

            for(int i=0;i<size;i++){
                 TreeNode * curr=q.front();
                 q.pop();

                 label.push_back(curr->val);
                
                if(curr->left!=nullptr){
                    q.push(curr->left);
                    }

                  if(curr->right!=nullptr){
                    q.push(curr->right);

                 }

              }
             if(rightToleft){
                reverse(label.begin(),label.end());
             }

             rightToleft=!rightToleft;

             vec.push_back(label) ;

        }

        return vec;

    }
};

// 111. Minimum Depth of Binary Tree
// problem
 // 1
 //    \
 //     2

 // int left=minDepth(root->left);

 // int right=minDepth(root->right);

 //   return 1+min(left,right);
// if we go through only by this thought

// Expected minimum depth = 2 (path: 1 -> 2)
// left = minDepth(nullptr) = 0
// right = minDepth(2) = 1
// return 1 + min(0, 1) = 1 ❌ Incorrect




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
    int minDepth(TreeNode* root) {
        if(root==nullptr){
            return 0;
        }
        if(root->left==nullptr){
           int right=minDepth(root->right);
            return 1+right;
        }
        if(root->right==nullptr){
            int  left=minDepth(root->left);
            return 1+left;

        }
        if(root->right!=nullptr && root->left!=nullptr){
        int left=minDepth(root->left);

        int right=minDepth(root->right);

        return 1+min(left,right);
        }
        return 0 //it's for compiler statisfiction
        
    }
};


