/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right)
 *         : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:

    vector<TreeNode*> solve(int l, int r) {

        vector<TreeNode*> result;

        // Empty subtree
        if (l > r) {
            result.push_back(nullptr);
            return result;
        }

        // Try every value as root
        for (int root = l; root <= r; root++) {

            // All possible left subtrees
            vector<TreeNode*> leftTrees = solve(l, root - 1);

            // All possible right subtrees
            vector<TreeNode*> rightTrees = solve(root + 1, r);

            // Combine every left subtree with every right subtree
            for (TreeNode* left : leftTrees) {
                for (TreeNode* right : rightTrees) {

                    TreeNode* node = new TreeNode(root);

                    node->left = left;
                    node->right = right;

                    result.push_back(node);
                }
            }
        }

        return result;
    }

    vector<TreeNode*> generateTrees(int n) {
        return solve(1, n);
    }
};