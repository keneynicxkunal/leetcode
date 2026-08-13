/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 *
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

    TreeNode* build(vector<int>& nums, int left, int right) {
        // No elements
        if (left > right)
            return nullptr;

        // Middle element becomes root
        int mid = left + (right - left) / 2;

        TreeNode* root = new TreeNode(nums[mid]);

        // Left half -> left subtree
        root->left = build(nums, left, mid - 1);

        // Right half -> right subtree
        root->right = build(nums, mid + 1, right);

        return root;
    }

    TreeNode* sortedListToBST(ListNode* head) {
        vector<int> nums;

        // Linked list -> array
        while (head != nullptr) {
            nums.push_back(head->val);
            head = head->next;
        }

        // Array -> height-balanced BST
        return build(nums, 0, nums.size() - 1);
    }
};