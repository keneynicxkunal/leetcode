class Solution {
public:
    bool isMirror(TreeNode* left, TreeNode* right) {
        // Both are NULL
        if (left == nullptr && right == nullptr)
            return true;

        // Only one is NULL
        if (left == nullptr || right == nullptr)
            return false;

        // Values must be equal
        if (left->val != right->val)
            return false;

        // Mirror comparison
        return isMirror(left->left, right->right) &&
               isMirror(left->right, right->left);
    }

    bool isSymmetric(TreeNode* root) {
        return isMirror(root->left, root->right);
    }
};