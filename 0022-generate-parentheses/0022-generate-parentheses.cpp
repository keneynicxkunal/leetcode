class Solution {
public:

    void solve(string curr, int open, int close, int n,
               vector<string>& ans) {

        // Jab n pairs complete ho gaye
        if (curr.length() == 2 * n) {
            ans.push_back(curr);
            return;
        }

        // Opening bracket lagao
        if (open < n) {
            solve(curr + "(", open + 1, close, n, ans);
        }

        // Closing bracket tabhi lagao
        // jab close < open
        if (close < open) {
            solve(curr + ")", open, close + 1, n, ans);
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> ans;

        solve("", 0, 0, n, ans);

        return ans;
    }
};