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
    //f是不选这个节点，g是选这个节点
    map<TreeNode*,int> f;
    map<TreeNode*,int> g;
    int dfs(TreeNode* root){
        if(!root) return 0;
        dfs(root->left);
        dfs(root->right);
        g[root]=f[root->right]+f[root->left]+root->val;
        f[root]=max(g[root->right],f[root->right])+max(g[root->left],f[root->left]);
        return max(f[root],g[root]);
    }
    int rob(TreeNode* root) {
        return dfs(root);
    }
};

/*
优化了哈希表写法

struct SubtreeStatus {
    int selected;
    int notSelected;
};

class Solution {
public:
    SubtreeStatus dfs(TreeNode* node) {
        if (!node) {
            return {0, 0};
        }
        auto l = dfs(node->left);
        auto r = dfs(node->right);
        int selected = node->val + l.notSelected + r.notSelected;
        int notSelected = max(l.selected, l.notSelected) + max(r.selected, r.notSelected);
        return {selected, notSelected};
    }

    int rob(TreeNode* root) {
        auto rootStatus = dfs(root);
        return max(rootStatus.selected, rootStatus.notSelected);
    }
};
*/ 
