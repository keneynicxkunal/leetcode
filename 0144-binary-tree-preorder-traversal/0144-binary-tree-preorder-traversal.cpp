class Solution {
public:
    vector<int> ans;

    void preorder(TreeNode* root) {
        if (root == nullptr)
            return;

        // 1. Root
        ans.push_back(root->val);

        // 2. Left
        preorder(root->left);

        // 3. Right
        preorder(root->right);
    }

    vector<int> preorderTraversal(TreeNode* root) {
        preorder(root);
        return ans;
    }
};