class Solution {
public:
    TreeNode* prev = nullptr;

    void flatten(TreeNode* root) {
        if (root == nullptr)
            return;

        // Process right first
        flatten(root->right);

        // Then process left
        flatten(root->left);

        // Connect current node to previously processed node
        root->right = prev;
        root->left = nullptr;

        prev = root;
    }
};