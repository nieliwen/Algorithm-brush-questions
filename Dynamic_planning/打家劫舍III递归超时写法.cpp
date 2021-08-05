/*
输入: [3,2,3,null,3,null,1]

     3
    / \
   2   3
    \   \ 
     3   1

输出: 7 
解释:?小偷一晚能够盗取的最高金额 = 3 + 3 + 1 = 7.
*/ 

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
    int g(TreeNode* root){
        if(!root) return 0;
        if(!root->left && !root->right) return root->val;
        return o(root->left)+o(root->right)+root->val;
    }
    int o(TreeNode* root){
        if(!root) return 0;
        return max(g(root->left),o(root->left))+max(g(root->right),o(root->right));
    }
    int rob(TreeNode* root) {
        //g()选该节点o()不选该节点
        return g(root)>o(root)?g(root):o(root);
    }
}; 
