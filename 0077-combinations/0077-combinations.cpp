class Solution {
public:
    vector<vector<int>> ans;
    vector<int> current;

    void backtrack(int start, int n, int k) {
        // We have selected k numbers
        if (current.size() == k) {
            ans.push_back(current);
            return;
        }

        for (int i = start; i <= n; i++) {
            current.push_back(i);

            backtrack(i + 1, n, k);

            current.pop_back(); // backtrack
        }
    }

    vector<vector<int>> combine(int n, int k) {
        backtrack(1, n, k);
        return ans;
    }
};