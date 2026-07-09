class Solution {
public:
    vector<vector<int>> ans;
    vector<int> temp;

    void backtrack(vector<int>& candidates, int target, int index) {
        if (target == 0) {
            ans.push_back(temp);
            return;
        }

        if (index == candidates.size() || target < 0)
            return;

        // Include current candidate
        temp.push_back(candidates[index]);
        backtrack(candidates, target - candidates[index], index);
        temp.pop_back();

        // Exclude current candidate
        backtrack(candidates, target, index + 1);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backtrack(candidates, target, 0);
        return ans;
    }
};