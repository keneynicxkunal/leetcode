class Solution {
public:
    vector<vector<int>> ans;

    void backtrack(vector<int>& nums, vector<int>& subset, int index) {
        ans.push_back(subset);

        for (int i = index; i < nums.size(); i++) {
            subset.push_back(nums[i]);          // Choose
            backtrack(nums, subset, i + 1);     // Explore
            subset.pop_back();                  // Backtrack
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> subset;
        backtrack(nums, subset, 0);
        return ans;
    }
};